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
*/

//Power Controll
#define ADC_USE_DMA //used by AnalogBufferDMA library
#define ADC_USE_TIMER


#include <ADC.h>
#include <DMAChannel.h>
#include <AnalogBufferDMA.h>
//#include <TimerOne.h>

//output pins
#define BuckPin 7
#define ACInrushRelayPin 10
#define LVCapDischargePin 11
#define HVCapDischargePin 12
#define ledPin 13
#define launchProjectilePin 1

//input pins pins
#define enableFullPowerPin 2
#define SafetyPin 3
#define FirePin 4
#define StableStatePin 5

//I2C pins
#define SCL0 19
#define SDA0 18

//buck converter constants
#define PWMFrequency 4577.64
#define PWMRes 15
#define PWMMaxVal 32757
//#define PWMMaxVal 1023

#define PWMMaxDuty 0.90
#define PWMMinDuty 0.10
#define voltageDividerRatio 0.03521
#define CurrentSenseResistor_mOhm 4.8
#define DividerRatio 28.396 //inverse of voltageDividerRatio     2.4647
#define ADCMaxValV 3.2919   // 12 bit val at 4095     // 1246.1
#define ADCMaxValI 3.2872   // 10 bit val at 1023     // 311.54

//#define voltageThreshhold 3071 // 70 volts      (70 * voltageDividerRatio) * (4095 / ADCMaxValV)     2200 //50
#define voltageThreshhold 2700
//#define CurrentThreshhold 896  // 600 Amps      (600 * CurrentSenseResistor_mOhm) * (1023 / ADCMaxValI)
#define CurrentThreshhold 300

#define VoltageSampleFreq 12500
#define CurrentSampleFreq 125000

#define DebounceSafetyQueSize 10
#define DebounceFireQueSize 3
#define FireRateTimeoutUs 1000000
#define FirePinHighTimeoutUs 3000

//#define PRINT_DEBUG_INFO
const int VInitial = 300;
int32_t PWMMax = PWMMaxVal;    //this is updated to PWMMaxVal * PWMMaxDuty  at run time
int32_t PWM50 = PWMMaxVal / 2; //this is updated to PWMMax / 2  at run time
int32_t PWMMin = 0;            //this is updated to PWMMaxVal * PWMMinDuty  at run time
int32_t MaxDutyCycle = 0;      //soft start
int32_t SoftStartDelta = 1000;
int32_t CurrentThreshholdVariable = CurrentThreshhold;

const int CurrentPin = A0;
const int VoltagePin = A2;
const int HighVoltagePin = A6;

ADC *adc = new ADC(); // adc object
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
//void print_debug_information();

// Going to try two buffers here  using 2 dmaSettings and a DMAChannel

const uint32_t Current_buffer_size = 10;
const uint32_t Voltage_buffer_size = 1;
DMAMEM static volatile uint16_t __attribute__((aligned(32))) dma_Current_buff1[Current_buffer_size];
DMAMEM static volatile uint16_t __attribute__((aligned(32))) dma_Current_buff2[Current_buffer_size];
AnalogBufferDMA CurrentBuffer(dma_Current_buff1, Current_buffer_size, dma_Current_buff2, Current_buffer_size);

#ifdef ADC_DUAL_ADCS
DMAMEM static volatile uint16_t __attribute__((aligned(32))) dma_Voltage_buff2_1[Voltage_buffer_size];
DMAMEM static volatile uint16_t __attribute__((aligned(32))) dma_Voltage_buff2_2[Voltage_buffer_size];
AnalogBufferDMA VoltageBuffer(dma_Voltage_buff2_1, Voltage_buffer_size, dma_Voltage_buff2_2, Voltage_buffer_size);
#endif
void callback()
{
}

void StartDmaADC()
{
    // Start the dma operation..
    adc->adc0->startSingleRead(CurrentPin);   // call this to setup everything before the Timer starts, differential is also possible
    adc->adc0->startTimer(CurrentSampleFreq); //frequency in Hz

    adc->adc1->startSingleRead(VoltagePin);   // call this to setup everything before the Timer starts, differential is also possible
    adc->adc1->startTimer(VoltageSampleFreq); //frequency in Hz
}

void StopDmaADC()
{
    // Start the dma operation..
    adc->adc0->stopTimer();

    adc->adc1->stopTimer(); //frequency in Hz
}

void setup()
{

    pinMode(ledPin, OUTPUT);

    Serial.begin(9600);

    IntervalTimer myTimer;

    myTimer.begin(callback, 10);

    myTimer.priority(0);

    //myTimer.update(microseconds);

    myTimer.end();

    while (!Serial && millis() < 5000)
        ;

    PWMMin = PWMMaxVal * PWMMinDuty;
    PWMMax = PWMMaxVal * PWMMaxDuty;
    PWM50 = PWMMax / 2;

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

    pinMode(CurrentPin, INPUT); // Not sure this does anything for us
    pinMode(VoltagePin, INPUT);
    pinMode(HighVoltagePin, INPUT);

    Serial.println("Setup both ADCs");
    // Setup both ADCs
    adc->adc0->setAveraging(0);   // set number of averages
    adc->adc0->setResolution(10); // set bits of resolution

    adc->adc1->setAveraging(4);   // set number of averages
    adc->adc1->setResolution(12); // set bits of resolution

    // enable DMA and interrupts
    //Serial.println("before enableDMA"); Serial.flush();

    // setup a DMA Channel.
    // Now lets see the different things that RingbufferDMA setup for us before
    CurrentBuffer.init(adc, ADC_0 /*, DMAMUX_SOURCE_ADC_ETC*/);
    CurrentBuffer.userData(initial_average_value); // save away initial starting average
    VoltageBuffer.init(adc, ADC_1 /*, DMAMUX_SOURCE_ADC_ETC*/);
    VoltageBuffer.userData(initial_average_value); // save away initial starting average
    //Serial.println("After enableDMA"); Serial.flush();

    //StartDmaADC();

    //Timer1.initialize(200);
    //Timer1.pwm(BuckPin, 0);
    analogWriteFrequency(BuckPin, PWMFrequency);
    analogWriteResolution(PWMRes);
    analogWrite(BuckPin, 0);

    //print_debug_information();

    Serial.println("End Setup");
    //elapsed_sinc_last_display = 0;
    canStartFireSequence = true;
    digitalWriteFast(ledPin, HIGH);
}

bool printCurrentOutput = false;
bool printVoltageOutput = false;
bool firstPass = true;
uint32_t Nexttime = micros() + 200;
uint32_t NexttimeTwo = micros() + 1000000;

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

void fireRateTimeout()
{
    FireTimeoutTimer.end();
    canStartFireSequence = true;
}

void LowerFirePin()
{
    FirePinLowerTimer.end();
    digitalWriteFast(launchProjectilePin, LOW);
}

void loop()
{
    while (true)
    {
        if (!InFireSequence)
        {
            DebounceSafetyQue.push(digitalReadFast(SafetyPin));
            if (DebounceSafetyQue.isAllTrue()) //safety off
            {
                if (canStartFireSequence)
                {
                    DebounceFireQue.push(digitalReadFast(FirePin));
                    if (DebounceFireQue.isAllTrue()) //begin fire sequence
                    {
                        if (!DMA_ADCs_Running) // setup for power delivery before entering the fire sequence
                        {
                            StartDmaADC();
                            DMA_ADCs_Running = true;
                            delay(1); // wait so the the dma buffers can fill
                        }
                        digitalWriteFast(launchProjectilePin, HIGH);
                        InFireSequence = true;
                        canStartFireSequence = false;
                        FireTimeoutTimer.begin(fireRateTimeout, FireRateTimeoutUs); 
                        FirePinLowerTimer.begin(LowerFirePin, FirePinHighTimeoutUs);
                    }
                }
            }
            else
            {
                uint32_t time = micros();
                if (time >= NexttimeTwo)
                {
                    NexttimeTwo = time + 1000000;
                    Serial.println("__");
                    Serial.print(analogRead(HighVoltagePin));
                }
            }
        }
        else
        {//in fire sequence
            if (digitalReadFast(enableFullPowerPin))
            {// gun controll indicated that the projectile is being accelerated and requires power
                uint32_t time = micros();
                if (time >= Nexttime)
                {
                    Nexttime = time + 80;
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
                if (DMA_ADCs_Running)
                {
                    StopDmaADC();
                    DMA_ADCs_Running = false;
                }
                MaxDutyCycle = PWMMin;
                if (digitalReadFast(StableStatePin))
                { //gun controll indicated that the fireing process has finised and everything has been reset
                    InFireSequence = false;
                }
            }
        }
    }
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

    int32_t FeedbackLoopI = (CurrentThreshholdVariable)-average_Current;
    int32_t iGain = 100;
    FeedbackLoopI = (FeedbackLoopI * iGain) + PWM50;

    int32_t FeedbackLoopV = (voltageThreshhold)-Voltage;
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

    CurrentBuf->userData(average_Current);
    Serial.print("__");
    Serial.print(Voltage);
}