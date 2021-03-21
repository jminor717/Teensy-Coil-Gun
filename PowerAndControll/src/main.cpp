/* Example for triggering the ADC with Timer using DMA instead of interrupts
    Valid for the current Teensy 3.x and 4.0.
  Timers:
    On Teensy 3.x this uses the PDB timer.
    On Teensy 4, this uses one or two of the unused QTimers.
    Setting it up:  The variables readPin must be defined for a pin that is valid for the first (or only)
    ADC.  If the processor has a second ADC and is enabled, than readPin2 must be configured to be a pin
    that is valid on the second ADC.
  DMA: using AnalogBufferDMA with two buffers, this runs in continuous mode and when one buffer fills
    an interrupt is signaled, which sets flag saying it has data, which this test application
    scans the data, and computes things like a minimum, maximum, average values and an RMS value.
    For the RMS it keeps the average from the previous set of data.









PIO has trouble resolving global libraries use absolute path to header files

C:\repos\TeensyCoilGun\PowerAndControll\.pio\libdeps\teensy40\Adafruit GFX Library\Adafruit_SPITFT.h
=>
    #include <C:\Users\jacob\.platformio\packages\framework-arduinoteensy\libraries\SPI\SPI.h>

C:\repos\TeensyCoilGun\PowerAndControll\.pio\libdeps\teensy40\Adafruit GFX Library\Adafruit_GrayOLED.h
=>
    #include <C:\repos\TeensyCoilGun\PowerAndControll\.pio\libdeps\teensy40\Adafruit BusIO\Adafruit_I2CDevice.h>
    #include <C:\repos\TeensyCoilGun\PowerAndControll\.pio\libdeps\teensy40\Adafruit BusIO\Adafruit_SPIDevice.h>
    #include <C:\Users\jacob\.platformio\packages\framework-arduinoteensy\libraries\SPI\SPI.h>

C:\repos\TeensyCoilGun\PowerAndControll\.pio\libdeps\teensy40\Adafruit BusIO\Adafruit_SPIDevice.h
=>
    #include <C:\Users\jacob\.platformio\packages\framework-arduinoteensy\libraries\SPI\SPI.h>

*/

//Power Controll
#define ADC_USE_DMA //used by AnalogBufferDMA library
#define ADC_USE_TIMER

#include <ADC.h>
#include <DMAChannel.h>
#include <AnalogBufferDMA.h>
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "CustomAnalog.hpp"
//#include <TimerOne.h>

//output pins
#define BuckPin 7
#define ACInrushRelayPin 6
#define LVCapDischargePin 22
#define HVCapDischargePin 23
#define ledPin 13
#define launchProjectilePin 9

//input pins pins
#define dischargePin 0
#define SafetyPin 1
#define enableFullPowerPin 2
#define FirePin 4
#define StableStatePin 5

//I2C pins
#define SCL0 19
#define SDA0 18

//analog inputs
const int CurrentPin = A0;     //14
const int VoltagePin = A2;     //16
const int VoltageSetPin = A6;  //20
const int HighVoltagePin = A7; //21

//buck converter constants
#define PWMFrequency 4577.64 //ideal frequency for given cpu frequency
#define LowPowerPWMFrequency 1000
#define PWMRes 15
#define PWMMaxVal 32757
//#define PWMMaxVal 1023

#define PWMMaxDuty 0.90
#define PWMMinDuty 0.10
#define voltageDividerRatio 0.02727    //0.03521 //irl measured value
#define CurrentSenseResistor_mOhm 4.8  //irl measured value
#define DividerRatio 36.67             //28.396   //inverse of voltageDividerRatio     2.4647
#define ADCMaxValV 3.2919              // 12 bit val at 4095     // 1246.1
#define ADCMaxValI 3.2872              // 10 bit val at 1023     // 311.54
#define MaximumMeasurableVoltage 101.9 //ADCMaxValV / voltageDividerRatio

#define MaxVoltLevel 3071 // 70 volts      (70 * voltageDividerRatio) * (4095 / ADCMaxValV)     2200 //50
#define voltageThreshhold 2700
//#define CurrentThreshhold 896  // 600 Amps      (600 * CurrentSenseResistor_mOhm) * (1023 / ADCMaxValI)
#define CurrentThreshhold 300

#define VoltageSampleFreq 12500
#define CurrentSampleFreq 125000

#define DebounceSafetyQueSize 10
#define DebounceFireQueSize 3
#define FireRateTimeoutUs 1000000
#define FirePinHighTimeoutUs 3000
#define SevenSegRefreshRateUs 33000

const int VInitial = 300;
int32_t PWMMax = PWMMaxVal;    //this is updated to PWMMaxVal * PWMMaxDuty  at run time
int32_t PWM50 = PWMMaxVal / 2; //this is updated to PWMMax / 2  at run time
int32_t PWMMin = 0;            //this is updated to PWMMaxVal * PWMMinDuty  at run time
int32_t MaxDutyCycle = 0;      //soft start
int32_t SoftStartDelta = 1000;
int32_t CurrentThreshholdVariable = CurrentThreshhold;
int32_t VoltageThreshholdVariable = voltageThreshhold;

const uint32_t initial_average_value = 2048;
bool DMA_ADCs_Running = false;
bool InFireSequence = false;
bool canStartFireSequence = false;
IntervalTimer FireTimeoutTimer;
IntervalTimer FirePinLowerTimer;

//extern void dumpDMA_structures(DMABaseClass *dmabc);
//elapsedMillis elapsed_sinc_last_display;

void ProcessAnalogData(AnalogBufferDMA *, bool);
void ProcessCurrentData(AnalogBufferDMA *, bool);
void ProcessIAndV(AnalogBufferDMA *, AnalogBufferDMA *);
void clampValue(int32_t &, int32_t, int32_t);

ADC *adc = new ADC(); // adc object
Adafruit_7segment matrix = Adafruit_7segment();

const uint32_t Current_buffer_size = 10;
const uint32_t Voltage_buffer_size = 1;
// Going to try two buffers here  using 2 dmaSettings and a DMAChannel
DMAMEM static volatile uint16_t __attribute__((aligned(32))) dma_Current_buff1[Current_buffer_size];
DMAMEM static volatile uint16_t __attribute__((aligned(32))) dma_Current_buff2[Current_buffer_size];
AnalogBufferDMA CurrentBuffer(dma_Current_buff1, Current_buffer_size, dma_Current_buff2, Current_buffer_size);

DMAMEM static volatile uint16_t __attribute__((aligned(32))) dma_Voltage_buff2_1[Voltage_buffer_size];
DMAMEM static volatile uint16_t __attribute__((aligned(32))) dma_Voltage_buff2_2[Voltage_buffer_size];
AnalogBufferDMA VoltageBuffer(dma_Voltage_buff2_1, Voltage_buffer_size, dma_Voltage_buff2_2, Voltage_buffer_size);

void StartDmaADC()
{
    if (!DMA_ADCs_Running)
    {                                 // Setup both ADCs
        adc->adc0->setAveraging(0);   // set number of averages
        adc->adc0->setResolution(10); // set bits of resolution

        adc->adc1->setAveraging(4);   // set number of averages
        adc->adc1->setResolution(12); // set bits of resolution

        // Start the dma operation..
        adc->adc0->startSingleRead(CurrentPin);   // call this to setup everything before the Timer starts, differential is also possible
        adc->adc0->startTimer(CurrentSampleFreq); //frequency in Hz

        adc->adc1->startSingleRead(VoltagePin);   // call this to setup everything before the Timer starts, differential is also possible
        adc->adc1->startTimer(VoltageSampleFreq); //frequency in Hz

        //setup the buck converter for full power operation
        analogWriteFrequency(BuckPin, PWMFrequency);

        PWMMin = PWMMaxVal * PWMMinDuty;
        PWMMax = PWMMaxVal * PWMMaxDuty;
        PWM50 = PWMMax / 2;
    }

    DMA_ADCs_Running = true;
}

bool hasFired = false;

void StopDmaADC()
{
    if (DMA_ADCs_Running)
    {
        // stop the dma operation..
        adc->adc0->stopTimer();
        adc->adc1->stopTimer();

        //setup the buck converter to slowly charge the cap before fiering
        analogWriteFrequency(BuckPin, LowPowerPWMFrequency);
        //hasFired = true;
        delay(500);
        analog_init();
        delay(10);
        analogReadResPerADC(10, ADC_1);
        analogReadResPerADC(12, ADC_2);
    }
    DMA_ADCs_Running = false;
}

void setup()
{

    pinMode(ledPin, OUTPUT);

    Serial.begin(9600);

    //wait for 5 seconds or or serial coms to begin
    while (!Serial && millis() < 5000)
        ;

    pinMode(BuckPin, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(ACInrushRelayPin, OUTPUT);
    pinMode(LVCapDischargePin, OUTPUT);
    pinMode(HVCapDischargePin, OUTPUT);
    pinMode(launchProjectilePin, OUTPUT);

    pinMode(enableFullPowerPin, INPUT_PULLDOWN);
    pinMode(SafetyPin, INPUT_PULLDOWN);
    pinMode(FirePin, INPUT_PULLDOWN);
    pinMode(StableStatePin, INPUT_PULLDOWN);
    pinMode(dischargePin, INPUT_PULLDOWN);

    pinMode(CurrentPin, INPUT); // Not sure this does anything for us
    pinMode(VoltagePin, INPUT);
    pinMode(VoltageSetPin, INPUT);

    Serial.println("Setup both ADCs");
    // setup a DMA Channel.
    // Now lets see the different things that RingbufferDMA setup for us before
    CurrentBuffer.init(adc, ADC_0 /*, DMAMUX_SOURCE_ADC_ETC*/);
    CurrentBuffer.userData(initial_average_value); // save away initial starting average
    VoltageBuffer.init(adc, ADC_1 /*, DMAMUX_SOURCE_ADC_ETC*/);
    VoltageBuffer.userData(initial_average_value); // save away initial starting average
    //Serial.println("After enableDMA"); Serial.flush();

    //analogReadResPerADC(10, ADC_1);
    //analogReadResPerADC(12, ADC_2);
    //analogReadResADC1(10);
    //analogReadResADC2(12);
    //analogReadRes(12);
    //delay(20);
    StartDmaADC();

    analogWriteFrequency(BuckPin, LowPowerPWMFrequency); //LowPowerPWMFrequency
    analogWriteResolution(PWMRes);
    analogWrite(BuckPin, 0);
    matrix.begin(0x70);
    matrix.setBrightness(2);

    delay(100);

    canStartFireSequence = true;
    digitalWrite(ledPin, HIGH);
    digitalWrite(ACInrushRelayPin, HIGH);
    digitalWrite(LVCapDischargePin, HIGH);
    digitalWrite(HVCapDischargePin, LOW);

    StopDmaADC();
    Serial.println("End Setup");
}

/** 
 * 32 bit integer used to hold an array of bollean values 
 * usefull for compairing multiple bollean values at once 
*/
template <size_t MaxLen>
class QuickCompBoolList
{
private:
    size_t position = 0;
    uint32_t comp = 0;

public:
    uint32_t data = 0;
    QuickCompBoolList()
    {
        for (size_t i = 0; i < MaxLen; i++)
        {
            comp = comp | (1UL << i);
        }
    }
    void push(const bool &value)
    {
        if (position >= MaxLen)
        {
            position = 0;
        }
        data ^= (-value ^ data) & (1UL << position);
        position++;
    }
    bool isAllTrue() { return data == comp; }
    bool isAllFalse() { return data == 0UL; }
};

QuickCompBoolList<DebounceSafetyQueSize> DebounceSafetyQue;
QuickCompBoolList<DebounceFireQueSize> DebounceFireQue;
QuickCompBoolList<5> DebounceDischargeQue;

uint32_t NextFeedbackCycle = micros();
uint32_t NextScreenRefresh = micros();
uint32_t NextVoltSelectMeasure = micros();
uint32_t NextVoltOutputMeasure = micros();
int64_t vSetAccumulator = 0;
int64_t vMeasureAccumulator = 0;

void fireRateTimeout()
{
    FireTimeoutTimer.end();
    canStartFireSequence = true;
    InFireSequence = false;
}

void LowerFirePin()
{
    FirePinLowerTimer.end();
    digitalWrite(launchProjectilePin, LOW);
}

void loop()
{

    while (true)
    {
        if (!InFireSequence)
        {
            DebounceSafetyQue.push(digitalReadFast(SafetyPin));
            if (DebounceSafetyQue.isAllTrue())
            { //safety off
                digitalWriteFast(LVCapDischargePin, LOW);
                uint32_t time = micros();
                int readValue = analogReadPerADC(VoltagePin - 14, ADC_2);
                vMeasureAccumulator = (0.03 * readValue) + (1.0 - 0.03) * vMeasureAccumulator;
                if (time >= NextScreenRefresh)
                {
                    NextScreenRefresh = time + 50000;
                    matrix.print(map((float)vMeasureAccumulator, 0.0, 4095.0, 0.0, MaximumMeasurableVoltage));
                    matrix.writeDisplay();
                }
                if (vMeasureAccumulator <= (VoltageThreshholdVariable * 0.85))
                {
                    if (time >= NextVoltOutputMeasure)
                    {
                        NextVoltOutputMeasure = time + 1000;
                        analogWrite(BuckPin, 600); //equates to roughly 20µs on time
                    }
                    digitalWrite(ledPin, LOW);
                    continue;
                }
                else if (vMeasureAccumulator <= (VoltageThreshholdVariable * 0.9))
                {
                    if (time >= NextVoltOutputMeasure)
                    {
                        NextVoltOutputMeasure = time + 1000;
                        analogWrite(BuckPin, 600); //equates to roughly 20µs on time
                    }
                    digitalWrite(ledPin, HIGH);
                }
                else
                {
                    analogWrite(BuckPin, 0);
                    digitalWrite(ledPin, HIGH);
                }


                if (canStartFireSequence)
                {
                    DebounceFireQue.push(digitalReadFast(FirePin));
                    if (DebounceFireQue.isAllTrue()) //begin fire sequence
                    {
                        Serial.println("^^");
                        // setup for power delivery before entering the fire sequence
                        StartDmaADC();
                        delay(1); // wait so the the dma buffers can fill

                        digitalWrite(launchProjectilePin, HIGH);
                        InFireSequence = true;
                        canStartFireSequence = false;
                        FireTimeoutTimer.begin(fireRateTimeout, FireRateTimeoutUs);
                        FirePinLowerTimer.begin(LowerFirePin, FirePinHighTimeoutUs);
                    }
                }
            }
            else
            { // safety engaged
                analogWrite(BuckPin, 0);
                DebounceDischargeQue.push(digitalReadFast(dischargePin));
                uint32_t time = micros();

                if (DebounceDischargeQue.isAllTrue())
                { //discharge engaged discharge the LV cap bank
                    digitalWrite(LVCapDischargePin, HIGH);
                    if (time >= NextVoltSelectMeasure)
                    {
                        NextVoltSelectMeasure = time + 1000;
                        int readValue = analogReadPerADC(VoltagePin - 14, ADC_2);
                        vMeasureAccumulator = (0.05 * readValue) + (1.0 - 0.05) * vMeasureAccumulator;
                    }
                    if (time >= NextScreenRefresh)
                    {
                        NextScreenRefresh = time + 50000;
                        matrix.print(map((float)vMeasureAccumulator, 0.0, 4095.0, 0.0, MaximumMeasurableVoltage));
                        matrix.writeDisplay();
                    }
                }
                else
                { //safety engaged adjust voltage set point
                    digitalWrite(LVCapDischargePin, LOW);
                    if (time >= NextVoltSelectMeasure)
                    {
                        NextVoltSelectMeasure = time + 1000;
                        int readValue = analogReadPerADC(VoltageSetPin - 14, ADC_2);
                        vSetAccumulator = (0.05 * readValue) + (1.0 - 0.05) * vSetAccumulator;
                    }
                    if (time >= NextScreenRefresh)
                    {
                        NextScreenRefresh = time + 50000;
                        VoltageThreshholdVariable = map(vSetAccumulator, 0, 4095, 0, MaxVoltLevel);
                        matrix.print(map((float)VoltageThreshholdVariable, 0.0, (double)MaxVoltLevel, 0.0, 70.0));
                        matrix.writeDisplay();
                    }
                }
            }
        }
        else
        { //in fire sequence
            if (digitalReadFast(enableFullPowerPin))
            { // gun controll indicated that the projectile is being accelerated and requires power
                uint32_t time = micros();
                if (time >= NextFeedbackCycle)
                {
                    //allow enough time for both DMA buffers to fill
                    //we dont need to worry about overflow because we are only averaging and dont need to capture every single measurement
                    NextFeedbackCycle = time + 80;
                    if (MaxDutyCycle < PWMMax)
                    {
                        MaxDutyCycle += SoftStartDelta;
                        if (MaxDutyCycle > PWMMax)
                        {
                            MaxDutyCycle = PWMMax;
                        }
                    }
                    ProcessIAndV(&CurrentBuffer, &VoltageBuffer);
                }
            }
            else
            {
                analogWrite(BuckPin, 0);
                MaxDutyCycle = PWMMin;
                if (digitalReadFast(StableStatePin))
                { //gun controll indicated that the fireing process has finised and everything has been reset
                    Serial.println("&&");
                    InFireSequence = false;
                    StopDmaADC();
                }
            }
        }
    }
    Serial.println("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH");
}

void clampValue(int32_t &val, int32_t max, int32_t min)
{
    if (val > max)
    {
        val = max;
    }
    else if (val < min)
    {
        val = min;
    }
}

void ProcessIAndV(AnalogBufferDMA *CurrentBuf, AnalogBufferDMA *VoltageBuf)
{
    uint32_t sum_values = 0;

    uint32_t average_Current; // = CurrentBuf->userData();
    uint32_t Voltage = 0;

    volatile uint16_t *IBuffer = CurrentBuf->bufferLastISRFilled();
    volatile uint16_t *end_IBuffer = IBuffer + CurrentBuf->bufferCountLastISRFilled();

    volatile uint16_t *VBuffer = VoltageBuf->bufferLastISRFilled();
    volatile uint16_t *end_VBuffer = VBuffer + VoltageBuf->bufferCountLastISRFilled();

    if ((uint32_t)VBuffer >= 0x20200000u)
        arm_dcache_delete((void *)VBuffer, sizeof(dma_Voltage_buff2_1));
    while (VBuffer < end_VBuffer)
    {
        sum_values += *VBuffer;
        VBuffer++;
    }
    Voltage = sum_values / Voltage_buffer_size;
    sum_values = 0;

    if ((uint32_t)IBuffer >= 0x20200000u)
        arm_dcache_delete((void *)IBuffer, sizeof(dma_Current_buff1));
    while (IBuffer < end_IBuffer)
    {
        sum_values += *IBuffer;
        IBuffer++;
    }
    // uint16_t max_avg = (max2_val + max_val) / 2;
    average_Current = sum_values / Current_buffer_size;

    int32_t FeedbackLoopI = CurrentThreshholdVariable - average_Current;
    int32_t iGain = 100;
    FeedbackLoopI = (FeedbackLoopI * iGain) + PWM50;

    int32_t FeedbackLoopV = VoltageThreshholdVariable - Voltage;
    int32_t VGain = 50;
    FeedbackLoopV = (FeedbackLoopV * VGain) + PWM50;

    clampValue(FeedbackLoopV, MaxDutyCycle, PWMMin);
    clampValue(FeedbackLoopI, MaxDutyCycle, PWMMin);

    //the duty cycle should be the lowest of these 2 values in order to keep either voltage or current from getting to large
    if (FeedbackLoopI >= FeedbackLoopV)
    {
        if (FeedbackLoopV == PWMMin)
        {
            FeedbackLoopV = 0;
        }
        analogWrite(BuckPin, FeedbackLoopV);
    }
    else
    {
        if (FeedbackLoopI == PWMMin)
        {
            FeedbackLoopI = 0;
        }
        analogWrite(BuckPin, FeedbackLoopI);
    }

    //Serial.print("__");
    //Serial.print(average_Current);
    CurrentBuf->userData(average_Current);
}
