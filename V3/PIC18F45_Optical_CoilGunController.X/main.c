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

#define S10_AS_SENSOR_OUTPUT
#define TEST_FIRE_SEQUENCE
//#define TEST_MULTI_COIL

typedef enum
{
    SAFE,
    SEMI_AUTO,
} FireMode_t;

FireMode_t FireMode = SAFE;

uint16_t FireTimeCounter = 0;
uint8_t CoilTimeCounter = 0;

uint8_t CoilTimeout = 40 * 4;
uint16_t FireTimeout = (uint16_t)5000 * 4;

bool EnterFireSequence = false;
bool CurrentFireInput = false;
bool inFire = false;
bool ReadyForNextFire = true;
uint8_t CurrentCoil = 0;

#define NUM_COILS 8
#define ALL_SENSOR_MASK 0b11111111

bool UpdateDisplay = false;
int16_t NumberToDisplay = 0;

uint8_t FireDebounceCount = 0;
uint8_t FireDebounceThreshold = 60; // 6mS
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

void Enter_C0(void) { }
void Enter_C1(void) {
    CC1_SetHigh();
#ifdef TEST_MULTI_COIL
    C2_L_SetLow();
    C2_H_SetLow();
    C1_L_SetLow();
    C1_H_SetLow();
#endif
}
void Enter_C2(void) {
    CC2_SetHigh();
#ifdef TEST_MULTI_COIL
    C2_L_SetHigh();
    C2_H_SetLow();
    C1_L_SetHigh();
    C1_H_SetLow();
#endif
}
void Enter_C3(void) {
    CC1_SetLow();
    CC3_SetHigh();
#ifdef TEST_MULTI_COIL
    C2_L_SetLow();
    C2_H_SetHigh();
    C1_L_SetLow();
    C1_H_SetHigh();
#endif
}
void Enter_C4(void) {
    CC2_SetLow();
    CC4_SetHigh();
#ifdef TEST_MULTI_COIL
    C2_L_SetHigh();
    C2_H_SetHigh();
    C1_L_SetHigh();
    C1_H_SetHigh();
#endif
}
void Enter_C5(void) {
    CC3_SetLow();
    CC5_SetHigh();
#ifdef TEST_MULTI_COIL
    C2_L_SetLow();
    C2_H_SetLow();
    C1_L_SetLow();
    C1_H_SetLow();
#endif
}
void Enter_C6(void) {
    CC4_SetLow();
    CC6_SetHigh();
}
void Enter_C7(void) {
    CC5_SetLow();
    CC7_SetHigh();
}
void Enter_C8(void) {
    CC6_SetLow();
    CC8_SetHigh();
}

void C1HighSideOn() {
    C1_L_SetHigh();
    C1_H_SetHigh();
}
void C1LowSideOn() {
    C1_L_SetLow();
    C1_H_SetLow();
}
void C2HighSideOn() {
    C2_L_SetHigh();
    C2_H_SetHigh();
}
void C2LowSideOn() {
    C2_L_SetLow();
    C2_H_SetLow();
}

uint8_t Get_Safety(void) { return Safety_in_GetValue(); }

void NullSensorTrip(uint8_t sensorNum) { return; }
void EvenSensor(uint8_t sensorNum);
void OddSensor(uint8_t sensorNum);
bool AllSensorsHigh();

bool NullSensorCallback(uint8_t value, uint8_t SensorNumber) { return true; }
bool SafetySettled(uint8_t value, uint8_t SensorNumber);
bool SensorCallback(uint8_t value, uint8_t SensorNumber);

void EndFireSequence();

uint8_t (*GetSensorValues[10])(void) = {
    Get_S0,
    Get_S1,
    Get_S2,
    Get_S3,
    Get_S4,
    Get_S5,
    Get_S6,
    Get_S7,
    Get_S8,
    Get_Safety
};

bool (*SensorInputCallbacks[10])(uint8_t, uint8_t) = {
    NullSensorCallback,
    SensorCallback, // 1
    SensorCallback, // 2
    SensorCallback, // 3
    SensorCallback, // 4
    SensorCallback, // 5
    SensorCallback, // 6
    SensorCallback, // 7
    SensorCallback, // 8
    SafetySettled // 9
};

void (*SensorTrippedCallbacks[10])(uint8_t) = {
    NullSensorTrip,
    OddSensor, // 1
    EvenSensor, // 2
    OddSensor, // 3
    EvenSensor, // 4
    OddSensor, // 5
    EvenSensor, // 6
    OddSensor, // 7
    EvenSensor, // 8
    NullSensorTrip
};
#define SAFETY_INDEX 9

void (*EnterCoil[10])(void) = {
    Enter_C0,
    Enter_C1,
    Enter_C2,
    Enter_C3,
    Enter_C4,
    Enter_C5,
    Enter_C6,
    Enter_C7,
    Enter_C8
};

void SetDebounceFor(uint8_t sensor) {
    if ((sensor < NUM_COILS && inFire) || sensor == SAFETY_INDEX) {
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
    // (sensor > NUM_COILS || !inFire) && sensor != SAFETY_INDEX
    // (sensor < NUM_COILS && inFire) || sensor == SAFETY_INDEX
}

void INTERRUPT_Initialize(void) {
    // Disable Interrupt Priority Vectors (16CXXX Compatibility Mode)
    INTCONbits.IPEN = 0;
    INTERRUPT_GlobalInterruptEnable();
    // INTCONbits.GIE = 1; // Enable global interrupts
    INTERRUPT_PeripheralInterruptEnable();
    // INTCONbits.PEIE = 1; // Enable the Peripheral Interrupts
}

void __interrupt() INTERRUPT_InterruptManager(void) {
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
            case _IOCCF_IOCCF3_MASK:
                IOCCFbits.IOCCF3 = 0;
                if (FireMode != SAFE) {
                    TMR1_StartTimer();
                    FireDebounceCount = 0;
                }
                return;
            case _IOCCF_IOCCF2_MASK:
                IOCCFbits.IOCCF2 = 0;
                SetDebounceFor(SAFETY_INDEX);
                return;
            default:
                break;
            }
        }

        if (IOCCFbits.IOCCF3 == 1) { // interrupt on change for pin IOCCF1
            IOCCFbits.IOCCF3 = 0;
            if (FireMode != SAFE) {
                TMR1_StartTimer();
                FireDebounceCount = 0;
            }
        }
        if (IOCCFbits.IOCCF2 == 1) { // interrupt on change for pin IOCCF1
            IOCCFbits.IOCCF2 = 0;
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
#ifndef TEST_MULTI_COIL
            C1LowSideOn();
            C2LowSideOn();
#endif
            TMR0_StopTimer();
            ReadyForNextFire = true;
            UpdateDisplay = true;
            NumberToDisplay = 0x0000;
        }
        if (CoilTimeCounter > CoilTimeout && inFire) {
#ifndef TEST_FIRE_SEQUENCE
            EndFireSequence();
#endif
            // UpdateDisplay = true;
            // NumberToDisplay = 6700 + CurrentCoil;
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

void StartFireSequence() {
    HT16K33_DisplayIntBinary(0b1111);
    __delay_ms(2);
    if (!AllSensorsHigh()) {
        ReadyForNextFire = true;
        return;
    }
    TMR0_StartTimer();
    ReadyForNextFire = false;
    CurrentCoil = 0;
#ifndef TEST_MULTI_COIL
    C1HighSideOn();
    C2LowSideOn();
#endif
    __delay_ms(2);
    inFire = true;
}

void EndFireSequence() {
    inFire = false;
#ifndef TEST_MULTI_COIL
    C1LowSideOn();
    C2LowSideOn();
#endif
    CC1_SetLow();
    CC2_SetLow();
    CC3_SetLow();
    CC4_SetLow();
    CC5_SetLow();
    CC6_SetLow();
    CC7_SetLow();
    CC8_SetLow();
    CurrentCoil = 0;
}

const uint8_t PORTASensorMask = _PORTA_RA0_MASK | _PORTA_RA1_MASK | _PORTA_RA2_MASK | _PORTA_RA3_MASK | _PORTA_RA4_MASK | _PORTA_RA5_MASK;
const uint8_t PORTESensorMask = _PORTE_RE0_MASK | _PORTE_RE1_MASK;

// bool OnlyOneSensorHigh()
//{
//     uint16_t sensorData = (uint16_t)((uint8_t)PORTA & PORTASensorMask)
//         + (uint16_t)(((uint8_t)PORTE & PORTESensorMask) << 6)
//     return (sensorData && !(sensorData & (sensorData - 1)));
// }

bool AllSensorsHigh() {
    uint16_t sensorData = (uint16_t)((uint8_t)PORTA & PORTASensorMask)
        + (uint16_t)(((uint8_t)PORTE & PORTESensorMask) << 6);
    return sensorData & ALL_SENSOR_MASK;
}

bool OnlyOneSensorLow() {
    uint16_t sensorData = (uint16_t)((uint8_t)PORTA & PORTASensorMask)
        + (uint16_t)(((uint8_t)PORTE & PORTESensorMask) << 6)
        + (uint16_t)(1 << 9);

    // due to the black magics of binary arithmetic the more powers of 2 you add the larger the number this method can handle
    // in this situation were we only care about checking if there is only a single 0 after the most significant 1
    // then we could get away with as few as 2 of these but the performance penalty is small enough to not make it worth the lower accuracy
    uint16_t x = sensorData; // say num = 100000
    x |= x >> 1; // 100000 | 010000 = 110000
    x |= x >> 2; // 110000 | 001100 = 111100
    x |= x >> 4; // 111100 | 000011 = 111111
    x |= x >> 8; // 111111 | 000000 = 111111
    // x |= x >> 16;    // 111111 | 000000 = 111111

    uint16_t inv = (sensorData ^ x);

    return (inv && !(inv & (inv - 1)));
}

bool SensorCallback(uint8_t value, uint8_t SensorNumber) {
    // realistically this could be set low whenever this is just a convenient time to do it
    // invert the sensor value since it is an active low signal
    // value = !value;
    // && inFire && OnlyOneSensorLow()
    if (value && SensorNumber == CurrentCoil + 1 && SensorNumber < NUM_COILS + 1) {
        // everything is in the correct state

        //        CurrentCoil = SensorNumber;
        CoilTimeCounter = 0;
        CurrentCoil++;
        EnterCoil[CurrentCoil]();
        SensorTrippedCallbacks[SensorNumber](SensorNumber);
        UpdateDisplay = true;
        NumberToDisplay = 6600 + SensorNumber;
        return true;
    } else if (value && SensorNumber == CurrentCoil) {
        // ignore this,
    } else if (value) { // if (value && OnlyOneSensorHigh())
        // the wrong sensor or more than one sensor was triggered
        // EndFireSequence();

        // UpdateDisplay = true;
        // NumberToDisplay = 6900 + SensorNumber;
    }

    if (value && SensorNumber == NUM_COILS) {
        EndFireSequence();
        UpdateDisplay = true;
        NumberToDisplay = 6800 + SensorNumber;
    }

    return true;
}

void EvenSensor(uint8_t sensorNum) {
#ifndef TEST_MULTI_COIL
    C2LowSideOn();
    C1HighSideOn();
#endif
}

void OddSensor(uint8_t sensorNum) {
#ifndef TEST_MULTI_COIL
    C1LowSideOn();
    C2HighSideOn();
#endif
}

bool SafetySettled(uint8_t value, uint8_t SensorNumber) {
    EndFireSequence();
    UpdateDisplay = true;
    NumberToDisplay = 1200 + value;
    if (value) {
        FireMode = SAFE;
    } else {
        FireMode = SEMI_AUTO;
    }

    FireDebounceCount = 0;
#ifndef TEST_MULTI_COIL
    C1LowSideOn();
    C2LowSideOn();
#endif
    return true;
}

/*
                         Main application
 */
void main(void) {
    // Initialize the device
    SYSTEM_Initialize();
    INTERRUPT_Initialize();

    TMR0_StopTimer();

    HT16K33_sendCMD(HT16K33_ON);
    HT16K33_sendCMD(HT16K33_DISPLAYON);
    HT16K33_sendCMD(HT16K33_BRIGHTNESS | 1);

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

    HT16K33_DisplayInt(3313);
    C1LowSideOn();
    C2LowSideOn();

    uint8_t HighCycles = 0b111;

    SetDebounceFor(SAFETY_INDEX);

    while (1) {
        if (debounceLength > 0) {
            for (size_t i = debounceIndex; i < debounceIndex + debounceLength; i++) {
                uint8_t realIndex = i & debounceModulo;
                uint8_t sensorNumber = debounceTracker[realIndex];
                debounceSettledCount[realIndex]++;
                debounceHighCount[realIndex] = (uint8_t)(debounceHighCount[realIndex] << 1);
                debounceHighCount[realIndex] |= GetSensorValues[sensorNumber]();
                if (debounceSettledCount[realIndex] > 4) {
                    uint8_t last5 = debounceHighCount[realIndex] & HighCycles;
                    if (last5 == HighCycles || last5 == 0b0) {
                        // settled High/low callback
                        if (SensorInputCallbacks[sensorNumber](last5 == HighCycles, sensorNumber)) {
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
        if (EnterFireSequence) {
            EnterFireSequence = false;
#ifdef TEST_FIRE_SEQUENCE
            if (CurrentCoil == 0) {
                EndFireSequence();
            }
            SensorCallback(1, CurrentCoil + 1);
            NumberToDisplay = CurrentCoil;
            UpdateDisplay = true;
            if (CurrentCoil % (NUM_COILS) == 0) {
                CurrentCoil = 0;
            }
#else
            StartFireSequence();
#endif
        }
        if (UpdateDisplay & !inFire) {
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