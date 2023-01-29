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

adc_channel_t LastChanel = S2;
// uint16_t S1Data[100] = {0};
// uint16_t S2Data[100] = {0};
// uint8_t S2Index = 0, S1Index =0;

uint16_t DataStore[255] = { 0 };
uint8_t DataIndex = 0;

bool adcConvFinished = false;
bool adcCaptureRunning = false;

bool FindingThreshold = false;
bool PreviousTriggered = false;

uint16_t StoredThreshold;
uint16_t flashAddr = 0x01C0;
uint8_t DacOut = 0;

void ADC_UserInterruptHandler(void)
{
    // add your ADC interrupt custom code
    // or set custom function using ADC_SetInterruptHandler()
    uint16_t data = ADC_GetConversionResult();

    //    if(LastChanel == S1){
    //        LastChanel = S2;
    //        S1Data[S1Index++] = data;
    //        if(S1Index >= 100){
    //            adcConvFinished = true;
    //            return;
    //        }
    //    }else{
    //        LastChanel = S1;
    //        S2Data[S2Index++] = data;
    //        if(S2Index >= 100){
    //            adcConvFinished = true;
    //            return;
    //        }
    //    }
    //    RC3 = !RC3;

    DataStore[DataIndex++] = data;
    if (DataIndex >= 255) {
        TMR4_StopTimer();
        adcConvFinished = true;
        return;
    }

    //    RC3 = DataIndex % 2;
    IO_RC3_Toggle();

    //    ADC_SelectChannel(LastChanel);
    //    ADC_StartConversion();
}


void PreviousIn_InterruptHandler(void){
    // add your IOCCF0 interrupt custom code
    // or set custom function using IOCCF0_SetInterruptHandler()
    
    PreviousTriggered = true;
    TMR4_StartTimer();
    
    LastChanel = S1;

    ADC_SelectChannel(LastChanel);
    adcConvFinished = false;
    adcCaptureRunning = true;
    DataIndex = 1;
    DataStore[0] = LastChanel;
}

void CMP2_ISR(void)
{
    // clear the CMP2 interrupt flag
    PIR2bits.C2IF = 0;
    if (adcCaptureRunning) {
        return;
    }

    
    //    ADC_StartConversion();
}

void CMP1_ISR(void)
{
    // clear the CMP1 interrupt flag
    PIR2bits.C1IF = 0;
    if (adcCaptureRunning) {
        return;
    }
    LastChanel = S2;

    ADC_SelectChannel(LastChanel);
    adcConvFinished = false;
    adcCaptureRunning = true;
    DataIndex = 1;
    DataStore[0] = LastChanel;
    //    ADC_StartConversion();
}

void TMR6_UserInterruptHandler(void)
{
    // add your TMR6 interrupt custom code
    // or set custom function using TMR6_SetInterruptHandler()
//    if (!FindingThreshold) {
//        DacOut++;
//        DAC_SetOutput(DacOut);
//    }
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

/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

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

    ADC_SetInterruptHandler(ADC_UserInterruptHandler);
    TMR6_SetInterruptHandler(TMR6_UserInterruptHandler);
    IOCCF0_SetInterruptHandler(PreviousIn_InterruptHandler);

    Sensor_Enable_SetHigh();
    __delay_ms(500);

    DacOut = FindThreshold() - 15;// 0.3V / (5V/256) 
    DAC_SetOutput(DacOut);

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
        if (adcConvFinished) {
            adcCaptureRunning = false;
            //            S2Data[0] = 0;
            //            S1Data[0] = 0;

            //            RC3 = 0;
            IO_RC3_SetLow();
            //            ADC_SelectChannel(LastChanel);
            //            ADC_StartConversion();
            DataIndex = 0;
        }
    }
}
/**
 End of File
*/