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

#define HighTimeout 6
#define FireTimeout 20

adc_channel_t LastChanel = S2;
// uint16_t S1Data[100] = {0};
// uint16_t S2Data[100] = {0};
// uint8_t S2Index = 0, S1Index =0;

// uint16_t DataStore[255] = { 0 };
// uint8_t DataIndex = 0;

bool FindingThreshold = false;
bool PreviousTriggered = false;
bool CMP_Ready = false;
bool InFireSequence = false;

uint16_t StoredThreshold;
uint16_t flashAddr = 0x01C0;
uint8_t DacOut = 128;

uint8_t PreviousHighCnt = 0, PreviousSettledCnt = 0;
uint8_t CoilHighTimeout = HighTimeout;
uint16_t FireReadyTimeout = 0;

void StartCoil_1()
{
    Coil_1_SetHigh();
    InFireSequence = true;
    TMR6_WriteTimer(0); // reset the one mS timer to 0
    TMR6_StartTimer(); // 500 uS timer before comparator is ready
    CoilHighTimeout = HighTimeout;
}

void StopCoil_1()
{
    Coil_1_SetLow();
}

void StartCoil_2()
{
    TMR2_WriteTimer(0);
    CoilHighTimeout = HighTimeout;
    Coil_2_SetHigh();
}

void StopCoil_2()
{
    Coil_2_SetLow();
    Next_out_SetHigh();
    Sensor_Enable_SetLow();
}

void EndFireSequence()
{
    Coil_1_SetLow();
    Coil_2_SetLow();
    TMR2_StartTimer();
    TMR2_WriteTimer(0); // reset the one mS timer to 0
    CMP_Ready = false;
    FireReadyTimeout = FireTimeout;
    CoilHighTimeout = 0;
    TMR6_StopTimer();
    InFireSequence = false;
}

void ADC_UserInterruptHandler(void)
{
    // start ADC auto conversions
    //    TMR4_StartTimer();
    //    LastChanel = S1;
    //    ADC_SelectChannel(LastChanel);
    //    DataIndex = 1;
    //    DataStore[0] = LastChanel;

    // add your ADC interrupt custom code
    // or set custom function using ADC_SetInterruptHandler()
    uint16_t data = ADC_GetConversionResult();

    // IO_RC3_Toggle();

    //    ADC_SelectChannel(LastChanel);
    //    ADC_StartConversion();
}

void PreviousIn_InterruptHandler(void)
{
    // add your IOCCF0 interrupt custom code
    // or set custom function using IOCCF0_SetInterruptHandler()
    if (FireReadyTimeout == 0 && !InFireSequence) {
        PreviousSettledCnt = 0;
        PreviousTriggered = true;
        Sensor_Enable_SetHigh();
    }
}

void CMP2_ISR(void)
{
    // clear the CMP2 interrupt flag
    PIR2bits.C2IF = 0;
    if (CMP_Ready) {
        // CoilHighTimeout = HighTimeoutMs;
        // StopCoil_2();
        // EndFireSequence();
    }
}

void CMP1_ISR(void)
{
    // clear the CMP1 interrupt flag
    PIR2bits.C1IF = 0;
    if (CMP_Ready) {
        StopCoil_1();
        __delay_us(3);
        StartCoil_2();
    }
}

void TMR6_UserInterruptHandler(void)
{
    // 500 micro second timer
    CMP_Ready = true;
    if (CoilHighTimeout == 1) {
        EndFireSequence();
        return;
    }
    if (CoilHighTimeout != 0) {
        CoilHighTimeout--;
        return;
    }
}

void TMR2_UserInterruptHandler(void)
{
    // one milli second timer
    if (FireReadyTimeout == 1) {
        Coil_1_SetLow();
        Coil_2_SetLow();
        TMR2_StopTimer();
        FireReadyTimeout = 0;
        // IO_RC4_SetLow();
        return;
    }
    if (FireReadyTimeout != 0) {
        FireReadyTimeout--;
        return;
    }
}

uint8_t FindThreshold()
{
    FindingThreshold = true;
    uint8_t threshold = 1;
    while (FindingThreshold) {
        DAC_SetOutput(threshold);
        __delay_ms(1);
        if (CMP1_GetOutputStatus() && CMP2_GetOutputStatus() && threshold > 10) {
            FindingThreshold = false;
            return threshold;
        } else {
            threshold++;
            if (threshold == 0) {
                threshold = 1;
            }
        }
    }
    return 128; // shouldn't be possible but makes the compiler happy
}

void resetPreviousDebounce(){
    PreviousTriggered = false;
    PreviousHighCnt = 0;
    PreviousSettledCnt = 0;
}

/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // ADC_SetInterruptHandler(ADC_UserInterruptHandler);
    TMR6_SetInterruptHandler(TMR6_UserInterruptHandler);
    TMR2_SetInterruptHandler(TMR2_UserInterruptHandler);

    IOCCF0_SetInterruptHandler(PreviousIn_InterruptHandler);

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    // INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    // INTERRUPT_PeripheralInterruptDisable();

    Sensor_Enable_SetHigh();
    __delay_ms(500);

    DacOut = FindThreshold() - 15;// 0.3V / (5V/256)
    DAC_SetOutput(DacOut);

    Sensor_Enable_SetLow();
    __delay_ms(100);

    //    ADC_SelectChannel(LastChanel);
    //    ADC_StartConversion();

    //    Sensor_Enable_LAT = 1;

    //    uint16_t    writeData = 0x2A00;
    //    writeData += 135;
    //    uint16_t    Buf[ERASE_FLASH_BLOCKSIZE];
    //
    //    FLASH_WriteWord(flashAddr, Buf, writeData);

    //    StoredThreshold = FLASH_ReadWord(flashAddr);
    //    if((StoredThreshold & 0xFF00) == 0x2A00){
    //        //found stored threshold
    //        if(DacOut != (uint8_t)(StoredThreshold & 0x00FF)){
    //
    //        }
    //        DacOut = (uint8_t)(StoredThreshold & 0x00FF);
    //        DAC_SetOutput(DacOut);
    //    }else{
    //        uint16_t    writeData = 0x2A00;
    //        writeData += DacOut;
    //        uint16_t    Buf[ERASE_FLASH_BLOCKSIZE];
    //
    //        FLASH_WriteWord(flashAddr, Buf, writeData);
    //    }

    while (1) {
        // Add your application code
        if (PreviousTriggered) {
            PreviousSettledCnt++;
            if (Previous_In_GetValue()) {
                PreviousHighCnt++;
            } else {
                PreviousHighCnt = 0;
            }

            if (PreviousHighCnt > 5) {
                StartCoil_1();
                resetPreviousDebounce();
            }
            if (PreviousSettledCnt > 15) {
                Sensor_Enable_SetLow();
                resetPreviousDebounce();
            }
        }
    }
}
/**
 End of File
*/