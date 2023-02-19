/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F45Q10
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip software and any
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party
    license terms applicable to your use of third party software (including open source software) that
    may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
    FOR A PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
    SOFTWARE.
*/

#include "HT16K33_driver.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"
#include "mcc_generated_files/mcc.h"

typedef enum {
    SAFE,
    SEMI_AUTO,
} FireMode_t;

FireMode_t FireMode = SAFE;

uint16_t FireTimeCounter = 0;
uint8_t CoilTimeCounter = 0;

uint8_t CoilTimeout = 50 * 4;
uint16_t FireTimeout = (uint16_t)1000 * 4;

bool EnterFireSequence = false;
bool CurrentFireInput = false;
bool inFire = false;
bool ReadyForNextFire = true;
uint8_t CurrentCoil = 0;
#define NUM_COILS 2

bool UpdateDisplay = false;
int16_t NumberToDisplay = 0;

uint8_t FireDebounceCount = 0;
uint8_t FireDebounceThreshold = 30; // 3mS
uint8_t FireSettlingTo = 0;

uint8_t debounceIndex = 0;
uint8_t debounceLength = 0;
uint8_t debounceModulo = 0b1111;
uint8_t debounceTracker[16] = { 0 };
uint8_t debounceHighCount[16] = { 0 };
uint8_t debounceSettledCount[16] = { 0 };

uint8_t Get_S0(void) { return 0; }
uint8_t Get_S1(void) { return S1_in_GetValue(); }
uint8_t Get_S2(void) { return S2_in_GetValue(); }
uint8_t Get_S3(void) { return S3_in_GetValue(); }
uint8_t Get_S4(void) { return S4_in_GetValue(); }
uint8_t Get_S5(void) { return S5_in_GetValue(); }
uint8_t Get_S6(void) { return S6_in_GetValue(); }
uint8_t Get_S7(void) { return S7_in_GetValue(); }
uint8_t Get_S8(void) { return S8_in_GetValue(); }
uint8_t Get_S9(void) { return S9_in_GetValue(); }
uint8_t Get_S10(void) { return S10_in_GetValue(); }
uint8_t Get_S11(void) { return S11_in_GetValue(); }
uint8_t Get_S12(void) { return S12_in_GetValue(); }

uint8_t Get_Trigger(void) { return Trigger_in_GetValue(); }
uint8_t Get_Safety(void) { return Safety_in_GetValue(); }

bool NullSensorCallback(uint8_t value, uint8_t SensorNumber)
{
    return true;
}

bool EvenSensor(uint8_t value, uint8_t SensorNumber);
bool OddSensor(uint8_t value, uint8_t SensorNumber);
bool TriggerSettled(uint8_t value, uint8_t SensorNumber);
bool SafetySettled(uint8_t value, uint8_t SensorNumber);

void EndFireSequence();

uint8_t (*GetSensorValues[14])(void) = {
    Get_S0,
    Get_S1,
    Get_S2,
    Get_S3,
    Get_S4,
    Get_S5,
    Get_S6,
    Get_S7,
    Get_S8,
    Get_S9,
    Get_S10,
    Get_S11,
    Get_S12,
    Get_Safety
};

bool (*SensorInputCallbacks[14])(uint8_t, uint8_t) = {
    NullSensorCallback,
    OddSensor,
    EvenSensor,
    OddSensor,
    EvenSensor,
    OddSensor,
    EvenSensor,
    OddSensor,
    EvenSensor,
    OddSensor,
    EvenSensor,
    OddSensor,
    EvenSensor,
    SafetySettled
};

#define SAFETY_INDEX 13

void SetDebounceFor(uint8_t sensor)
{
    if(sensor > NUM_COILS && sensor != SAFETY_INDEX){
        return;
    }
    uint8_t ArrIndex = (debounceIndex + debounceLength) & debounceModulo;
    for (size_t i = debounceIndex; i < debounceIndex + debounceLength; i++) {
        if (debounceTracker[ArrIndex] == sensor) {
            debounceHighCount[ArrIndex] = 0;
            debounceSettledCount[ArrIndex] = 0;
            return;
        }
    }
    debounceTracker[ArrIndex] = sensor;
    debounceHighCount[ArrIndex] = 0;
    debounceSettledCount[ArrIndex] = 0;
    debounceLength++;
}

void INTERRUPT_Initialize(void)
{
    // Disable Interrupt Priority Vectors (16CXXX Compatibility Mode)
    INTCONbits.IPEN = 0;
    INTERRUPT_GlobalInterruptEnable();
    // INTCONbits.GIE = 1; // Enable global interrupts
    INTERRUPT_PeripheralInterruptEnable();
    // INTCONbits.PEIE = 1; // Enable the Peripheral Interrupts
}

void __interrupt() INTERRUPT_InterruptManager(void)
{
    if (IOCAF) { // && (bits && !(bits & (bits-1)))
        if (!(IOCAF & (IOCAF - 1))) {
            switch (IOCAF) {
            case _IOCAF_IOCAF0_MASK:
                IOCAFbits.IOCAF0 = 0;
                SetDebounceFor(1);
                return;
            case _IOCAF_IOCAF1_MASK:
                IOCAFbits.IOCAF1 = 0;
                SetDebounceFor(2);
                return;
            case _IOCAF_IOCAF2_MASK:
                IOCAFbits.IOCAF2 = 0;
                SetDebounceFor(3);
                return;
            case _IOCAF_IOCAF3_MASK:
                IOCAFbits.IOCAF3 = 0;
                SetDebounceFor(4);
                return;
            case _IOCAF_IOCAF4_MASK:
                IOCAFbits.IOCAF4 = 0;
                SetDebounceFor(5);
                return;
            case _IOCAF_IOCAF5_MASK:
                IOCAFbits.IOCAF5 = 0;
                SetDebounceFor(6);
                return;
            case _IOCAF_IOCAF6_MASK:
                IOCAFbits.IOCAF6 = 0;
                SetDebounceFor(10);
                return;
            case _IOCAF_IOCAF7_MASK:
                IOCAFbits.IOCAF7 = 0;
                SetDebounceFor(11);
                return;
            default:
                break;
            }
        }

        if (IOCAFbits.IOCAF0 == 1) { // interrupt on change for pin IOCAF0
            IOCAFbits.IOCAF0 = 0;
            SetDebounceFor(1);
        }
        if (IOCAFbits.IOCAF1 == 1) { // interrupt on change for pin IOCAF1
            IOCAFbits.IOCAF1 = 0;
            SetDebounceFor(2);
        }
        if (IOCAFbits.IOCAF2 == 1) { // interrupt on change for pin IOCAF2
            IOCAFbits.IOCAF2 = 0;
            SetDebounceFor(3);
        }
        if (IOCAFbits.IOCAF3 == 1) { // interrupt on change for pin IOCAF3
            IOCAFbits.IOCAF3 = 0;
            SetDebounceFor(4);
        }
        if (IOCAFbits.IOCAF4 == 1) { // interrupt on change for pin IOCAF4
            IOCAFbits.IOCAF4 = 0;
            SetDebounceFor(5);
        }
        if (IOCAFbits.IOCAF5 == 1) { // interrupt on change for pin IOCAF5
            IOCAFbits.IOCAF5 = 0;
            SetDebounceFor(6);
        }
        IOCAF = 0;
    }

    if (IOCCF) {
        if (!(IOCCF & (IOCCF - 1))) {
            switch (IOCCF) {
            case _IOCCF_IOCCF0_MASK:
                IOCCFbits.IOCCF0 = 0;
                SetDebounceFor(12);
                return;
            case _IOCCF_IOCCF6_MASK:
                IOCCFbits.IOCCF6 = 0;
                if (FireMode != SAFE) {
                    TMR1_StartTimer();
                    FireDebounceCount = 0;
                }
                return;
            case _IOCCF_IOCCF7_MASK:
                IOCCFbits.IOCCF7 = 0;
                SetDebounceFor(SAFETY_INDEX);
                return;
            default:
                break;
            }
        }

        if (IOCCFbits.IOCCF0 == 1) { // interrupt on change for pin IOCCF0
            IOCCFbits.IOCCF0 = 0;
            SetDebounceFor(12);
        }
        if (IOCCFbits.IOCCF6 == 1) { // interrupt on change for pin IOCCF1
            IOCCFbits.IOCCF6 = 0;
            if (FireMode != SAFE) {
                TMR1_StartTimer();
                FireDebounceCount = 0;
            }
        }
        if (IOCCFbits.IOCCF7 == 1) { // interrupt on change for pin IOCCF1
            IOCCFbits.IOCCF7 = 0;
            SetDebounceFor(SAFETY_INDEX);
        }
        IOCCF = 0;
    }

    if (IOCEF) {
        if (!(IOCEF & (IOCEF - 1))) {
            switch (IOCEF) {
            case _IOCEF_IOCEF0_MASK:
                IOCEFbits.IOCEF0 = 0;
                SetDebounceFor(7);
                return;
            case _IOCEF_IOCEF1_MASK:
                IOCEFbits.IOCEF1 = 0;
                SetDebounceFor(8);
                return;
            case _IOCEF_IOCEF2_MASK:
                IOCEFbits.IOCEF2 = 0;
                SetDebounceFor(9);
                return;
            default:
                break;
            }
        }

        if (IOCEFbits.IOCEF0 == 1) { // interrupt on change for pin IOCCF0
            IOCEFbits.IOCEF0 = 0;
            SetDebounceFor(7);
        }
        if (IOCEFbits.IOCEF1 == 1) { // interrupt on change for pin IOCCF1
            IOCEFbits.IOCEF1 = 0;
            SetDebounceFor(8);
        }
        if (IOCEFbits.IOCEF2 == 1) { // interrupt on change for pin IOCCF2
            IOCEFbits.IOCEF2 = 0;
            SetDebounceFor(9);
        }
        IOCEF = 0;
    }

    if (PIE0bits.TMR0IE == 1 && PIR0bits.TMR0IF == 1) {
        PIR0bits.TMR0IF = 0;
        FireTimeCounter++;
        CoilTimeCounter++;
        if (FireTimeCounter > FireTimeout) {
            // ready to fire again
            FireTimeCounter = 0;
            CoilTimeCounter = 0;
            Fire_Start_SetLow();
            C1_H_SetLow();
            C2_H_SetLow();
            C1_L_SetHigh();
            C2_L_SetHigh();
            TMR0_StopTimer();
            ReadyForNextFire = true;
            UpdateDisplay = true;
            NumberToDisplay = 0x0000;
        }
        if (CoilTimeCounter > CoilTimeout && inFire) {
            EndFireSequence();
            UpdateDisplay = true;
            NumberToDisplay = CoilTimeCounter;
        }
    }

    // timer 1 interrupt
    if (PIE4bits.TMR1IE == 1 && PIR4bits.TMR1IF == 1) {
        PIR4bits.TMR1IF = 0;
        TMR1_Reload();
        if (FireSettlingTo == Trigger_in_GetValue()) {
            FireDebounceCount++;
        } else {
            FireSettlingTo = Trigger_in_GetValue();
            FireDebounceCount = 0;
        }
        if (FireDebounceCount > FireDebounceThreshold) {
            TMR1_StopTimer();
            if (FireSettlingTo && ReadyForNextFire) {
                // fire
                EnterFireSequence = true;
            }
        }
    }

    // timer 6 interrupt
    if (PIE4bits.TMR6IE == 1 && PIR4bits.TMR6IF == 1) {
        // clear the TMR6 interrupt flag
        PIR4bits.TMR6IF = 0;
    }
}

void StartFireSequence()
{
    HT16K33_DisplayIntBinary(0b1111);
    TMR0_StartTimer();
    inFire = true;
    ReadyForNextFire = false;
    Fire_Start_SetHigh();
    C1_L_SetLow();
    C2_H_SetLow();
    C2_L_SetLow();
    __delay_us(1);
    C1_H_SetHigh();

}

void EndFireSequence()
{
    inFire = false;
    Fire_Start_SetLow();
    C1_L_SetLow();
    C2_L_SetLow();
    C1_H_SetLow();
    C2_H_SetLow();
}

const uint8_t PORTASensorMask = _PORTA_RA0_MASK | _PORTA_RA1_MASK | _PORTA_RA2_MASK | _PORTA_RA3_MASK | _PORTA_RA4_MASK | _PORTA_RA5_MASK;
const uint8_t PORTESensorMask = _PORTE_RE0_MASK | _PORTE_RE1_MASK | _PORTE_RE2_MASK;
const uint8_t PORTCSensorMask = _PORTC_RC0_MASK | _PORTC_RC1_MASK;

bool OnlyOneSensorHigh()
{
    uint16_t sensorData = (uint16_t)((uint8_t)PORTA & PORTASensorMask)
        + (uint16_t)(((uint8_t)PORTE & PORTESensorMask) << 6)
        + (uint16_t)(((uint8_t)PORTC & PORTCSensorMask) << 9);
    return (sensorData && !(sensorData & (sensorData - 1)));
}

bool EvenSensor(uint8_t value, uint8_t SensorNumber)
{
    Fire_Start_SetLow();
    if (value && inFire && OnlyOneSensorHigh() && SensorNumber == CurrentCoil + 1 && SensorNumber < NUM_COILS ) {
        CurrentCoil = SensorNumber;
        CoilTimeCounter = 0;
        C1_L_SetLow();
        C2_H_SetLow();
        __delay_us(1);
        // Nop();
        C2_L_SetHigh();
        C1_H_SetHigh();
    } else if (value) { // if (value && OnlyOneSensorHigh())
        // the wrong sensor or more than one sensor was triggered
        EndFireSequence();
        UpdateDisplay = true;
        NumberToDisplay = 6900 + SensorNumber;
    } else {
        // sensor set Low
    }
    return true;
}
bool OddSensor(uint8_t value, uint8_t SensorNumber)
{
    Fire_Start_SetLow();
    if (value && inFire && OnlyOneSensorHigh() && SensorNumber == CurrentCoil + 1 && SensorNumber < NUM_COILS) {
        // everything is in the correct state
        CurrentCoil = SensorNumber;
        CoilTimeCounter = 0;
        C2_L_SetLow();
        C1_H_SetLow();
        __delay_us(1);
        // Nop();
        C1_L_SetHigh();
        C2_H_SetHigh();
    } else if (value) { // if (value && OnlyOneSensorHigh())
        // the wrong sensor or more than one sensor was triggered
        EndFireSequence();
        UpdateDisplay = true;
        NumberToDisplay = 6900 + SensorNumber;
    } else {
        // sensor set Low
    }
    return true;
}

bool SafetySettled(uint8_t value, uint8_t SensorNumber)
{
    if (value) {
        FireMode = SAFE;
    } else {
        FireMode = SEMI_AUTO;
    }

    FireDebounceCount = 0;
    Fire_Start_SetLow();
    C1_H_SetLow();
    C2_H_SetLow();
    C1_L_SetHigh();
    C2_L_SetHigh();
    return true;
}

/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    INTERRUPT_Initialize();

    TMR0_StopTimer();

    HT16K33_sendCMD(HT16K33_ON);
    HT16K33_sendCMD(HT16K33_DISPLAYON);
    HT16K33_sendCMD(HT16K33_BRIGHTNESS | 2);

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    // INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    // INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    //

    // Disable the Peripheral Interrupts
    // INTERRUPT_PeripheralInterruptDisable();

    HT16K33_DisplayInt(0000);

    C1_L_SetHigh();
    C2_L_SetHigh();

    uint8_t HighCycles = 0b11;

    SetDebounceFor(SAFETY_INDEX);

    while (1) {
        if (debounceLength > 0) {
            for (size_t i = debounceIndex; i < debounceIndex + debounceLength; i++) {
                uint8_t realIndex = i & debounceModulo;
                debounceSettledCount[realIndex]++;
                debounceHighCount[realIndex] = (uint8_t)(debounceHighCount[realIndex] << 1);
                debounceHighCount[realIndex] |= GetSensorValues[debounceTracker[realIndex]]();
                if (debounceSettledCount[realIndex] > 4) {
                    uint8_t last5 = debounceHighCount[realIndex] & HighCycles;
                    if (last5 == HighCycles || last5 == 0b0) {
                        // settled High/low callback
                        if (SensorInputCallbacks[debounceTracker[realIndex]](last5 == HighCycles, debounceTracker[realIndex])) {
                            debounceHighCount[realIndex] = 0;
                            debounceSettledCount[realIndex] = 0;
                            debounceTracker[realIndex] = 0;
                            debounceIndex++;
                            debounceLength--;
                        }
                    } else {
                        // sensor not settled
                        // HT16K33_DisplayIntBinary(last5);
                        debounceHighCount[realIndex] = 0;
                        debounceSettledCount[realIndex] = 0;
                        debounceTracker[realIndex] = 0;
                        debounceIndex++;
                        debounceLength--;
                    }
                }
            }
        }
        if(EnterFireSequence){
            EnterFireSequence = false;
            StartFireSequence();
        }
        if(UpdateDisplay){
            UpdateDisplay = false;
            HT16K33_DisplayInt(NumberToDisplay);
        }

        // if (interruptCounter > 9998)
        //     interruptCounter = 0;
        // HT16K33_DisplayInt(interruptCounter);
    }
}
/**
 End of File
*/