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

uint16_t FireTimeCounter = 0;
uint8_t CoilTimeCounter = 0;

uint8_t CoilTimeout = 10 * 4;
uint16_t FireTimeout = (uint16_t)10000 * 4;

uint8_t FireDebounceCount = 0;
uint8_t FireDebounceLimit = 5;

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
uint8_t Get_Trigger(void) { return Trigger_in_GetValue(); }
uint8_t Get_Safety(void) { return Safety_in_GetValue(); }

#define TriggerIndex 12
#define SafetyIndex 13

void NullSensorCallback(uint8_t value, uint8_t SensorNumber)
{
}

void EvenSensor(uint8_t value, uint8_t SensorNumber);
void OddSensor(uint8_t value, uint8_t SensorNumber);
void TriggerSettled(uint8_t value, uint8_t SensorNumber);
void SafetySettled(uint8_t value, uint8_t SensorNumber);

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
    Get_Trigger,
    Get_Safety
};

void (*SensorInputCallbacks[14])(uint8_t, uint8_t) = {
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
    TriggerSettled,
    SafetySettled
};

void SetDebounceFor(uint8_t sensor)
{
    debounceLength++;
    debounceTracker[(debounceIndex + debounceLength) & debounceModulo] = sensor;
    debounceHighCount[(debounceIndex + debounceLength) & debounceModulo] = 0;
    debounceSettledCount[(debounceIndex + debounceLength) & debounceModulo] = 0;
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
    if (IOCAF != 0) { // && (bits && !(bits & (bits-1)))
        if (IOCAF && !(IOCAF & (IOCAF - 1))) {
            switch (IOCAF) {
            case 0b1:
                IOCAFbits.IOCAF0 = 0;
                SetDebounceFor(1);
                return;
            case 0b1 << 1:
                IOCAFbits.IOCAF1 = 0;
                SetDebounceFor(2);
                return;
            case 0b1 << 2:
                IOCAFbits.IOCAF2 = 0;
                SetDebounceFor(3);
                return;
            case 0b1 << 3:
                IOCAFbits.IOCAF3 = 0;
                SetDebounceFor(4);
                return;
            case 0b1 << 4:
                IOCAFbits.IOCAF4 = 0;
                SetDebounceFor(5);
                return;
            case 0b1 << 5:
                IOCAFbits.IOCAF5 = 0;
                SetDebounceFor(6);
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
        if (IOCCF && !(IOCCF & (IOCCF - 1))) {
            switch (IOCCF) {
            case 0b1:
                IOCCFbits.IOCCF0 = 0;
                SetDebounceFor(10);
                return;
            case 0b1 << 1:
                IOCCFbits.IOCCF1 = 0;
                SetDebounceFor(11);
                return;
            case 0b1 << 6:
                IOCCFbits.IOCCF6 = 0;
                SetDebounceFor(TriggerIndex);
                return;
            case 0b1 << 7:
                IOCCFbits.IOCCF7 = 0;
                SetDebounceFor(SafetyIndex);
                return;
            default:
                break;
            }
        }

        if (IOCCFbits.IOCCF0 == 1) { // interrupt on change for pin IOCCF0
            IOCCFbits.IOCCF0 = 0;
            SetDebounceFor(10);
        }
        if (IOCCFbits.IOCCF1 == 1) { // interrupt on change for pin IOCCF1
            IOCCFbits.IOCCF1 = 0;
            SetDebounceFor(11);
        }
        if (IOCCFbits.IOCCF6 == 1) { // interrupt on change for pin IOCCF1
            IOCCFbits.IOCCF6 = 0;
            SetDebounceFor(TriggerIndex);
        }
        if (IOCCFbits.IOCCF7 == 1) { // interrupt on change for pin IOCCF1
            IOCCFbits.IOCCF7 = 0;
            SetDebounceFor(SafetyIndex);
        }
        IOCCF = 0;
    }

    if (IOCEF) {
        if (IOCEF && !(IOCEF & (IOCEF - 1))) {
            switch (IOCEF) {
            case 0b1:
                IOCEFbits.IOCEF0 = 0;
                SetDebounceFor(7);
                return;
            case 0b1 << 1:
                IOCEFbits.IOCEF1 = 0;
                SetDebounceFor(8);
                return;
            case 0b1 << 2:
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

    // timer 6 interrupt section
    if (PIE4bits.TMR6IE == 1 && PIR4bits.TMR6IF == 1) {
        // clear the TMR6 interrupt flag
        PIR4bits.TMR6IF = 0;
        FireTimeCounter++;
        CoilTimeCounter++;
        if (FireTimeout > FireTimeCounter) {
            FireTimeCounter = 0;
            CoilTimeCounter = 0;
            TMR6_Stop();
        }
    }
}

uint8_t PORTASensorMask = _PORTA_RA0_MASK | _PORTA_RA1_MASK | _PORTA_RA2_MASK | _PORTA_RA3_MASK | _PORTA_RA4_MASK | _PORTA_RA5_MASK;
uint8_t PORTESensorMask = _PORTE_RE0_MASK | _PORTE_RE1_MASK | _PORTE_RE2_MASK;
uint8_t PORTCSensorMask = _PORTC_RC0_MASK | _PORTC_RC1_MASK;

bool OnlyOneSensorHigh()
{
    uint16_t sensorData = (uint16_t)((uint8_t)PORTA & PORTASensorMask)
        + (uint16_t)(((uint8_t)PORTE & PORTESensorMask) << 6)
        + (uint16_t)(((uint8_t)PORTC & PORTCSensorMask) << 9);
    return (sensorData && !(sensorData & (sensorData - 1)));
}

void EvenSensor(uint8_t value, uint8_t SensorNumber)
{
    C2_H_LAT = value;
}
void OddSensor(uint8_t value, uint8_t SensorNumber)
{
    C1_H_LAT = value;
}
void TriggerSettled(uint8_t value, uint8_t SensorNumber)
{
    if (FireTimeCounter == 0) {
        if (value) {
            FireDebounceCount++;
        } else {
            FireDebounceCount = 0;
        }

        if (FireDebounceCount >= FireDebounceLimit) {
            TMR6_Start();
        }
    }
}
void SafetySettled(uint8_t value, uint8_t SensorNumber)
{
    FireTimeCounter = value;
    FireDebounceCount = 0;
}

/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    INTERRUPT_Initialize();

    HT16K33_sendCMD(HT16K33_ON);
    HT16K33_sendCMD(HT16K33_DISPLAYON);
    HT16K33_sendCMD(HT16K33_BRIGHTNESS | 0);

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
    uint8_t HighCycles = 0b11;
    while (1) {
        if (debounceLength > 0) {
            for (size_t i = debounceIndex; i < debounceIndex + debounceLength; i++) {
                uint8_t realIndex = i & debounceModulo;
                debounceSettledCount[realIndex]++;
                debounceHighCount[realIndex] = (uint8_t)(debounceHighCount[realIndex] << 1);
                debounceHighCount[realIndex] |= GetSensorValues[debounceTracker[realIndex]]();
                if (debounceSettledCount[realIndex] > 4) {
                    uint8_t last5 = debounceHighCount[realIndex] & HighCycles;
                    if (last5 == HighCycles) {
                        // settled High callback
                        SensorInputCallbacks[debounceTracker[realIndex]](1, debounceTracker[realIndex]);
                    } else if (last5 == 0b0) {
                        // settled low callback
                        SensorInputCallbacks[debounceTracker[realIndex]](0, debounceTracker[realIndex]);
                    } else {
                        // sensor not settled
                        // HT16K33_DisplayIntBinary(last5);
                    }
                    debounceHighCount[realIndex] = 0;
                    debounceSettledCount[realIndex] = 0;
                    debounceTracker[realIndex] = 0;
                    debounceIndex++;
                    debounceLength--;
                }
            }
        }

        // if (interruptCounter > 9998)
        //     interruptCounter = 0;
        // HT16K33_DisplayInt(interruptCounter);
    }
}
/**
 End of File
*/