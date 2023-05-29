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
        Device            :  PIC16F1705
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

#include "mcc_generated_files/mcc.h"

//#define AdcThresholdChecking

#define ACQ_US_DELAY 5

#define CoilHighTime 160 // 40 * 4 (40ms / 250us)

#define SensorSettlingTime 3 // 750 us

//#define TestMode

#define FireTimeout 100 // 10 ms * 100
#define CmpReadyTime 3

bool CMP1_Ready = false, CMP2_Ready = false;
bool canAcceptFire = false;
uint8_t delayCanFire = 0;
bool canFire = false, PreviousTriggered = false;
bool StartFire = false;
bool enableTriggered = false;
bool Coil_Running = false;
uint8_t CoilHighTimeout = CoilHighTime;
uint8_t PreviousHighCnt = 0, PreviousSettledCnt = 0;
uint8_t enableTotalCount = 0, enableSettledCnt = 0, enableSettlingTo = 0;
uint8_t SetCmp1Ready = 0, SetCmp2Ready = 0;

uint16_t Sens1EMA = 0;
uint8_t SettleSensor = 0;

uint16_t FireReadyTimeout = FireTimeout;

bool findThreshold = false, startupFinished = false;

void EndFireSequence(void);
void resetEnableDebounce(void);
void resetPreviousDebounce(void);
void DisableSensor(void);
void EnableSensor(void);
void PreviousIn_InterruptHandler(void);
void SenseEnable_InterruptHandler(void);
uint16_t ema_fastest(uint16_t, uint16_t);
void RunSensorAveraging();

void TMR0_250ms_InterruptHandler(void) {
    if (!startupFinished) {
        findThreshold = true;
    }
}

void TMR1_10ms_InterruptHandler(void) {
    if (FireReadyTimeout <= 1) {
        EndFireSequence();
        TMR1_StopTimer();
        FireReadyTimeout = 0;
        DisableSensor();
        return;
    }
    FireReadyTimeout--;
}

void TMR2_250us_InterruptHandler(void) {
#ifndef AdcThresholdChecking
    if (SetCmp1Ready) {
        SetCmp1Ready--;
        if (SetCmp1Ready == 0) {
            CMP1_Ready = true;
        }
    }
    if (SetCmp2Ready) {
        SetCmp2Ready--;
        if (SetCmp2Ready == 0) {
            CMP2_Ready = true;
        }
    }
#endif
    if (SettleSensor) {
        SettleSensor--;
    }

    if (delayCanFire) {
        delayCanFire--;
        if (!delayCanFire) {
            canFire = true;
        }
    }

    if (CoilHighTimeout <= 1) {
        EndFireSequence();
        return;
    }
    CoilHighTimeout--;
}

void ADC_ChangeChannel(adc_channel_t channel) {
    // select the A/D channel
    ADCON0bits.CHS = channel;

    // Turn on the ADC module
    ADCON0bits.ADON = 1;

    // Acquisition time delay
    __delay_us(ACQ_US_DELAY);
}

adc_result_t ADC_RunConversion() {
    // Start the conversion
    ADCON0bits.GO_nDONE = 1;

    // Wait for the conversion to finish
    while (ADCON0bits.GO_nDONE) {
    }

    // Conversion finished, return the result
    return ((adc_result_t)((ADRESH << 8) + ADRESL));
}
//#ifndef AdcThresholdChecking
uint8_t FindThreshold() {
    DAC_SetOutput(0);
    uint8_t thr = 0;
    ADC_ChangeChannel(Sens1_in);
    uint16_t SensAdcVal = ADC_RunConversion();
    uint8_t incrament = 1;
    bool cmpVal = CMP1_GetOutputStatus();

    // 2.048 = 256   88
    // 5 = 1023    143

    for (size_t i = 0; i < 500; i++) {
        thr += incrament;
        DAC_SetOutput(thr);
        __delay_us(500);
        bool cmpValNew = CMP1_GetOutputStatus();
        if (cmpVal != cmpValNew && cmpValNew) {
            break;
        }
        cmpVal = cmpValNew;
    }

    ADC_ChangeChannel(Sens2_in);
    uint16_t Sens2Val = ADC_RunConversion();

    thr = 0;
    while (1) {
        thr++;
        DAC_SetOutput(thr);
        for (size_t i = 0; i < 100; i++) {
            NOP(); // delay 100 clock cycles
        }
        if (CMP1_GetOutputStatus() && CMP2_GetOutputStatus() && thr > 20) {
            break;
        }
        if (thr >= 250) {
            thr = 128;
            break;
        }
    }
    return thr;
}

void FindUnLoadedThreshold() {
    INTERRUPT_GlobalInterruptDisable();
    INTERRUPT_PeripheralInterruptDisable();

    Sensor_Enable_SetHigh();
    __delay_ms(1);
    Sensor_Enable_SetHigh();
    uint8_t DacOut = FindThreshold();
    Sensor_Enable_SetLow();
    DAC_SetOutput(DacOut - 38); // 0.3V / (2V/256)

    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
}
//#endif

void StartCoil_1() {
    Coil_1_SetLow();

    canAcceptFire = false;
    canFire = false;
    TMR2_WriteTimer(0); // reset timer to 0
    TMR2_StartTimer(); // 500 uS timer before comparator is ready
    CoilHighTimeout = CoilHighTime;
    TMR1_StartTimer();
    FireReadyTimeout = FireTimeout;
    Coil_Running = true;
#ifndef AdcThresholdChecking
    SetCmp1Ready = CmpReadyTime;
#endif
}

void StopCoil_1() { Coil_1_SetHigh(); }

void StartCoil_2() {
    Coil_2_SetLow();
    TMR2_WriteTimer(0); // reset timer to 0
    CoilHighTimeout = CoilHighTime;
}

void StopCoil_2() {
    Coil_2_SetHigh();
    Next_out_SetHigh();
}

void CMP2_ISR(void) {
    PIR2bits.C2IF = 0; // clear the CMP2 interrupt flag
    if (CMP2_Ready) {
        StopCoil_2();
        CMP2_Ready = false;
        EndFireSequence();
    }
}

void CMP1_ISR(void) {
    PIR2bits.C1IF = 0; // clear the CMP1 interrupt flag
    if (CMP1_Ready) {
        StopCoil_1();
        CMP1_Ready = false;
        SetCmp2Ready = CmpReadyTime;
        __delay_us(5);
        StartCoil_2();
    }
}

void EndFireSequence() {
    Coil_1_SetHigh();
    Coil_2_SetHigh();
    Sensor_Enable_SetLow();

    Coil_Running = false;

    CMP1_Ready = false;
    CMP2_Ready = false;

    TMR2_StopTimer();
    SettleSensor = 0;
}

//#define AdcVoltageOffset 245 // (4096/5) * 0.3
#define AdcVoltageOffset 20 // (4096/5) * 0.3


/*
    Main application
 */
void main(void) {
    SYSTEM_Initialize(); // initialize the device

    // coil output is inverted, turn both off until system is running
    Coil_1_SetHigh();
    Coil_2_SetHigh();
#ifdef TestMode
    CM1CON1 = 0xE9; // test mode needs low and high interrupts
    CM2CON1 = 0xEA;
#endif

    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();

    TMR1_SetInterruptHandler(TMR1_10ms_InterruptHandler);
    TMR2_SetInterruptHandler(TMR2_250us_InterruptHandler);
    TMR0_SetInterruptHandler(TMR0_250ms_InterruptHandler);
    IOCCF0_SetInterruptHandler(PreviousIn_InterruptHandler);
    IOCCF4_SetInterruptHandler(SenseEnable_InterruptHandler);

    Next_out_SetLow();
    Next_out_SetLow();

    while (1) {
        if (PreviousTriggered) {
            PreviousSettledCnt++;
            if (Previous_In_GetValue()) {
                PreviousHighCnt++;
            } else {
                PreviousHighCnt = 0;
            }

            if (PreviousHighCnt > 15) {
#ifdef AdcThresholdChecking
                StartFire = true;
                StartCoil_1();
#else
                StartCoil_1();
#endif
                resetPreviousDebounce();
            }
            if (PreviousSettledCnt > 30) {
                Sensor_Enable_SetLow();
                canAcceptFire = true;
                canFire = false;
                resetPreviousDebounce();
            }
            continue;
        }
        if (enableTriggered) {
            enableTotalCount++;
            uint8_t val = Sense_Enable_GetValue();
            if (val == enableSettlingTo) {
                enableSettledCnt++;
            } else {
                enableSettledCnt = 0;
            }
            enableSettlingTo = val;

            if (enableSettledCnt > 30) {
                if (enableSettlingTo) {
                    EnableSensor();
                } else {
                    DisableSensor();
                }
            }
            if (enableSettledCnt > 60) {
                DisableSensor();
            }
        }
        if (StartFire) {
            StartFire = false;
            uint16_t SensAdcVal = ADC_RunConversion();
            uint16_t SensEMA = Sens1EMA;
            uint16_t RawAdcReading[8] = {0};
            uint16_t RawAdcReading2[8] = {0};
            uint8_t AdcIndex = 0;
            SettleSensor = 3;
            while (SettleSensor > 0 && Coil_Running) {
//                RawAdcReading[AdcIndex++] = ADC_RunConversion();
//                AdcIndex = AdcIndex & 0xf;
                SensEMA = ADC_RunConversion();
                // SensAdcVal = ADC_RunConversion();
                // SensEMA = SensAdcVal; // ema_fastest(SensAdcVal, SensEMA);
            }

//            SensEMA = 0;
//            for (size_t i = 0; i < 8; i++) {
//                SensEMA += RawAdcReading[i];
//            }
//            SensEMA = SensEMA >> 3;

            while (Coil_Running) {
                SensAdcVal = ADC_RunConversion();
                if (((SensEMA + AdcVoltageOffset) < SensAdcVal)) { // && CMP1_GetOutputStatus()
                    break;
                }
            }

            if (Coil_Running) {
                StopCoil_1();

                ADC_ChangeChannel(Sens2_in); // changing the ADC channel includes a 5 us delay
                StartCoil_2();
                SettleSensor = 3;

                SensEMA = ADC_RunConversion();
                while (SettleSensor > 0 && Coil_Running) {
                    RawAdcReading2[AdcIndex++] = ADC_RunConversion();
                    AdcIndex = AdcIndex & 0xf;
                    SensEMA = ADC_RunConversion();
//                    SensAdcVal = ADC_RunConversion(); // the second sensor can be affected by the coil currents
//                    SensEMA = SensAdcVal; // ema_fastest(SensAdcVal, SensEMA);
                }
                
//                SensEMA = 0;
//                for (size_t i = 0; i < 8; i++) {
//                    SensEMA += RawAdcReading2[i];
//                }
//                SensEMA = SensEMA >> 3;

                while (Coil_Running) {
                    SensAdcVal = ADC_RunConversion();
                    if (((SensEMA + AdcVoltageOffset) < SensAdcVal)) { //  && CMP2_GetOutputStatus()
                        break;
                    }
                }

                StopCoil_2();
            }
            EndFireSequence();
            DisableSensor();
            
        }
#ifdef AdcThresholdChecking
        if (canFire && !canAcceptFire) {
            // start averaging the first sensors value before we fire
            uint16_t SensAdcVal = ADC_RunConversion();
            Sens1EMA = ema_fastest(SensAdcVal, Sens1EMA);
        }
#else
        if (findThreshold) {
            findThreshold = false;
            FindUnLoadedThreshold();
            canAcceptFire = true;
            startupFinished = true;
        }
#endif
#ifdef TestMode
        Coil_2_LAT = CMP2_GetOutputStatus();
        Coil_1_LAT = CMP1_GetOutputStatus();
#endif
    }
}

/*
 random simplification functions
 */

/// @brief compute the ema with a given input and average using a fixed window size of 4
/// @param inVal
/// @param average
/// @return
uint16_t ema_fastest(uint16_t inVal, uint16_t average) {
    // right shift by 1 for a window of 4 or by 2 for a window of 9
    return (average - ((average - inVal) >> 1));
}

void RunSensorAveraging() {
}

void resetEnableDebounce() {
    enableTriggered = false;
    enableSettledCnt = 0;
    enableTotalCount = 0;
}

void resetPreviousDebounce() {
    PreviousTriggered = false;
    PreviousHighCnt = 0;
    PreviousSettledCnt = 0;
}

void DisableSensor() {
    Sensor_Enable_SetLow();
    if (FireReadyTimeout == 0) {
        // only set these if we are already ready to fire
        canAcceptFire = true;
        canFire = false;
    }

    resetEnableDebounce();
}

void EnableSensor() {
    ADC_ChangeChannel(Sens1_in);
    Sensor_Enable_SetHigh();
    resetEnableDebounce();
    canAcceptFire = false;
    //    __delay_ms(1);
    canFire = true;
    //    delayCanFire = 1;
    //    CoilHighTimeout = 0xFF; // this will be set to the right value when coil 1 starts
    //    TMR2_WriteTimer(0); // reset timer to 0
    //    TMR2_StartTimer(); // 500 uS timer before comparator is ready
}

void PreviousIn_InterruptHandler(void) {
    //     Coil_2_Toggle();
    if (canFire) {
        PreviousSettledCnt = 0;
        PreviousTriggered = true;
    }
}

void SenseEnable_InterruptHandler(void) {
    //    Coil_1_Toggle();
    if (canAcceptFire || canFire) {
        enableTotalCount = 0;
        enableSettledCnt = 0;
        enableTriggered = true;
    }
}

/**
 End of File
*/