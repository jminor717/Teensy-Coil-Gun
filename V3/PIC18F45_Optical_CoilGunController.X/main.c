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





    __delay_us(5);
    Nop();
    _delay(80);
*/

#include "HT16K33_driver.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"
#include "mcc_generated_files/mcc.h"

//#define TEST_FIRE_SEQUENCE
//#define TEST_MULTI_COIL
//#define TEST_REACTION_TIME
//#define REMOVE_TIMEOUT

#define INVERT_SINGLE_COIL_DRIVE
#define COIL_8_FUCKED

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

#define NUM_COILS 7
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

// void NullSensorTrip() { return; }
void EvenSensor(void);
void OddSensor(void);

#ifdef INVERT_SINGLE_COIL_DRIVE
void C1_ON(){ CC1_SetLow(); }
void C2_ON(){ CC2_SetLow(); }
void C3_ON(){ CC3_SetLow(); }
void C4_ON(){ CC4_SetLow(); }
void C5_ON(){ CC5_SetLow(); }
void C6_ON(){ CC6_SetLow(); }
void C7_ON(){ CC7_SetLow(); }
#ifndef COIL_8_FUCKED
void C8_ON(){ CC8_SetLow(); }
#endif
void C1_OFF(){ CC1_SetHigh(); }
void C2_OFF(){ CC2_SetHigh(); }
void C3_OFF(){ CC3_SetHigh(); }
void C4_OFF(){ CC4_SetHigh(); }
void C5_OFF(){ CC5_SetHigh(); }
void C6_OFF(){ CC6_SetHigh(); }
void C7_OFF(){ CC7_SetHigh(); }
void C8_OFF(){ CC8_SetHigh(); }

#else
void C1_ON(){ CC1_SetHigh(); }
void C2_ON(){ CC2_SetHigh(); }
void C3_ON(){ CC3_SetHigh(); }
void C4_ON(){ CC4_SetHigh(); }
void C5_ON(){ CC5_SetHigh(); }
void C6_ON(){ CC6_SetHigh(); }
void C7_ON(){ CC7_SetHigh(); }
void C8_ON(){ CC8_SetHigh(); }

void C1_OFF(){ CC1_SetLow(); }
void C2_OFF(){ CC2_SetLow(); }
void C3_OFF(){ CC3_SetLow(); }
void C4_OFF(){ CC4_SetLow(); }
void C5_OFF(){ CC5_SetLow(); }
void C6_OFF(){ CC6_SetLow(); }
void C7_OFF(){ CC7_SetLow(); }
void C8_OFF(){ CC8_SetLow(); }

#endif

void Enter_C0(void) { }
void Enter_C1(void) {
    OddSensor();
    C1_ON();
    CurrentCoil = 1;
#ifdef TEST_MULTI_COIL
    C2_L_SetLow();
    C2_H_SetLow();
    C1_L_SetLow();
    C1_H_SetLow();
#endif
}
void Enter_C2(void) {
    C1_OFF();
    EvenSensor();
    C2_ON();
    CurrentCoil = 2;
#ifdef TEST_MULTI_COIL
    C2_L_SetHigh();
    C2_H_SetLow();
    C1_L_SetHigh();
    C1_H_SetLow();
#endif
}
void Enter_C3(void) {
    C2_OFF();
    OddSensor();
    C3_ON();
    CurrentCoil = 3;
#ifdef TEST_MULTI_COIL
    C2_L_SetLow();
    C2_H_SetHigh();
    C1_L_SetLow();
    C1_H_SetHigh();
#endif
}
void Enter_C4(void) {
    C3_OFF();
    EvenSensor();
    C4_ON();
    CurrentCoil = 4;
#ifdef TEST_MULTI_COIL
    C2_L_SetHigh();
    C2_H_SetHigh();
    C1_L_SetHigh();
    C1_H_SetHigh();
#endif
}
void Enter_C5(void) {
    C4_OFF();
    OddSensor();
    C5_ON();
    CurrentCoil = 5;
#ifdef TEST_MULTI_COIL
    C2_L_SetLow();
    C2_H_SetLow();
    C1_L_SetLow();
    C1_H_SetLow();
#endif
}
void Enter_C6(void) {
    C5_OFF();
    EvenSensor();
    C6_ON();
    CurrentCoil = 6;
}
void Enter_C7(void) {
    C6_OFF();
    OddSensor();
    C7_ON();
    CurrentCoil = 7;
}
void Enter_C8(void) {
    C7_OFF();
    EvenSensor();
#ifndef COIL_8_FUCKED
    C8_ON();
#endif
    CurrentCoil = 8;
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

void RailsLow(){
    C1LowSideOn();
    C2LowSideOn();
}

void EvenSensor() {
#ifndef TEST_MULTI_COIL
    C1LowSideOn();
    C2HighSideOn();
#endif
}

void OddSensor() {
#ifndef TEST_MULTI_COIL
    C2LowSideOn();
    C1HighSideOn();
#endif
}

uint8_t Get_Safety(void) { return Safety_in_GetValue(); }
bool AllSensorsHigh(void);

bool NullSensorCallback(uint8_t value, uint8_t SensorNumber) { return true; }
bool SafetySettled(uint8_t value, uint8_t SensorNumber);
bool SensorCallback(uint8_t value, uint8_t SensorNumber);

void EndFireSequence(void);

uint8_t (*GetSensorValues[10])(void) = {
    Get_S0,
    Get_S1,
#ifndef TEST_REACTION_TIME
    Get_S2,
    Get_S3,
    Get_S4,
    Get_S5,
    Get_S6,
    Get_S7,
    Get_S8,
#else
    Get_S1,
    Get_S1,
    Get_S1,
    Get_S1,
    Get_S1,
    Get_S1,
    Get_S1,
#endif
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
    // UpdateDisplay = true;
    // NumberToDisplay = 9000 + sensor;
    bool CheckSensor = inFire && sensor <= CurrentCoil + 2 && sensor >= CurrentCoil ;
    if (CheckSensor || sensor == SAFETY_INDEX) {
        // UpdateDisplay = true;
        // NumberToDisplay = 9100 + sensor ;
        for (size_t i = debounceIndex; i < debounceIndex + debounceLength; i++) {
            uint8_t realIndex = i & debounceModulo;
            if (debounceTracker[realIndex] == sensor) {
                debounceHighCount[realIndex] = 0;
                debounceSettledCount[realIndex] = 0;
                return;
            }
        }
        uint8_t ArrIndex = (debounceIndex + debounceLength) & debounceModulo;
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
        UpdateDisplay = true;
        NumberToDisplay = 9200;
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
#ifndef REMOVE_TIMEOUT
#ifndef TEST_MULTI_COIL
            RailsLow();
#endif
            UpdateDisplay = true;
            NumberToDisplay = 0x0000;
#endif
            TMR0_StopTimer();
            ReadyForNextFire = true;
        }
        if (CoilTimeCounter > CoilTimeout && inFire) {
            NumberToDisplay = 6700 + CurrentCoil;
#ifndef TEST_FIRE_SEQUENCE
#ifndef REMOVE_TIMEOUT
            EndFireSequence();
#endif
#endif
            UpdateDisplay = true;
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
        UpdateDisplay = true;
        NumberToDisplay = 9000;
        ReadyForNextFire = true;
        return;
    }
    TMR0_StartTimer();
    ReadyForNextFire = false;
    inFire = true;
    CurrentCoil = 0;
#ifndef TEST_MULTI_COIL
    Enter_C1();
#endif
    //__delay_ms(2);
}

void EndFireSequence(void) {
    inFire = false;
#ifndef TEST_MULTI_COIL
    RailsLow();
#endif
    C1_OFF();
    C2_OFF();
    C3_OFF();
    C4_OFF();
    C5_OFF();
    C6_OFF();
    C7_OFF();
    C8_OFF();
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
#ifdef TEST_REACTION_TIME
    SensorNumber = CurrentCoil + 1;
#endif
    if (SensorNumber >= NUM_COILS - 1) {
        EndFireSequence();
        UpdateDisplay = true;
        NumberToDisplay = 6800 + SensorNumber;
        return true;
    }
    
    // invert the sensor value since it is an active low signal
    value = !value;
    if(!value){
        return true;
    }
    
    //OnlyOneSensorLow()
    if (SensorNumber == CurrentCoil) {
        // everything is in the correct state
        CoilTimeCounter = 0;
        EnterCoil[SensorNumber + 1]();
        UpdateDisplay = true;
        NumberToDisplay = 6600 + SensorNumber;
        return true;
    }

    UpdateDisplay = true;
    NumberToDisplay = 6500 + SensorNumber;
    return true;
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
    RailsLow();
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
    
    C1_OFF();
    C2_OFF();
    C3_OFF();
    C4_OFF();
    C5_OFF();
    C6_OFF();
    C7_OFF();
    C8_OFF();

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

    HT16K33_DisplayInt(3313);
    RailsLow();

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
            if(CurrentCoil == 0){
                Enter_C1();
                
            }else{
                SensorCallback(0, CurrentCoil + 1);
            }
            NumberToDisplay = CurrentCoil;
            UpdateDisplay = true;
#else
            StartFireSequence();
#endif
        }
#ifdef REMOVE_TIMEOUT
        if (UpdateDisplay) {
#else
        if (UpdateDisplay & !inFire) {
#endif
            UpdateDisplay = false;
            HT16K33_DisplayInt(NumberToDisplay);
        }
    }
}
/**
 End of File
*/