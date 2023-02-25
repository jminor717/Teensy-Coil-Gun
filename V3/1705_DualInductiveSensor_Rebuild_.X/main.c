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

#define CoilHighTime 10 * 2

#define TestMode

#ifdef TestMode
#define FireTimeout 50000
#else
#define FireTimeout 900
#endif

bool CMP1_Ready = false, CMP2_Ready = false, SetCmp1Ready = false;
bool canFire = false, PreviousTriggered = false;
uint8_t CoilHighTimeout = CoilHighTime;
uint8_t PreviousHighCnt = 0, PreviousSettledCnt = 0;

uint16_t FireReadyTimeout = FireTimeout;

bool findThrshold = false, startupFinished = false;

void EndFireSequence();

void TMR0_250ms_InterruptHandler(void){
    if(!startupFinished){
        findThrshold = true;
    }
}

void TMR1_10ms_InterruptHandler(void)
{
#ifdef TestMode
    CMP1_Ready = true;
    CMP2_Ready = true;
#endif
    if (FireReadyTimeout <= 1) {
        EndFireSequence();
        TMR1_StopTimer();
        FireReadyTimeout = 0;
        canFire = true;
        return;
    }
    FireReadyTimeout--;
}

void TMR2_500us_InterruptHandler(void)
{
    if(SetCmp1Ready){
        SetCmp1Ready = false;
        CMP1_Ready = true;
    }
    if (CoilHighTimeout <= 1) {
        EndFireSequence();
        return;
    }
    CoilHighTimeout--;
}

void PreviousIn_InterruptHandler(void)
{
    // add your IOCCF0 interrupt custom code
    // or set custom function using IOCCF0_SetInterruptHandler()
    if (canFire) {
        PreviousSettledCnt = 0;
        PreviousTriggered = true;
    }
}

uint8_t FindThreshold()
{
    uint8_t thr = 0, attempts = 0;
    while (1)
    {
        thr++;
        DAC_SetOutput(thr);
        for (size_t i = 0; i < 500; i++)
        {
            NOP();
        }
        // __delay_us(500);
        Coil_1_Toggle();
        if (CMP1_GetOutputStatus() && CMP2_GetOutputStatus() && thr > 20) {
            Coil_1_SetHigh();

            break;
        }
        if(thr >= 250){
            //thr = 0;
            //attempts++;
            //if(attempts > 2){
                thr = 128;
                Coil_1_SetLow();
                break;
            //}
        }
    }
    return thr;
}

void StartCoil_1()
{   
    Coil_1_SetHigh();
#ifndef TestMode
    TMR2_WriteTimer(0); // reset timer to 0
    TMR2_StartTimer(); // 500 uS timer before comparator is ready
    CoilHighTimeout = CoilHighTime;
#endif
    TMR1_StartTimer();
    FireReadyTimeout = FireTimeout;
}

void StopCoil_1()
{
    Coil_1_SetLow();
}

void StartCoil_2()
{
    Coil_2_SetHigh();
    TMR2_WriteTimer(0); // reset timer to 0
    CoilHighTimeout = CoilHighTime;
}

void StopCoil_2()
{
    Coil_2_SetLow();
    Next_out_SetHigh();
    
}

void CMP2_ISR(void)
{
    // clear the CMP2 interrupt flag
    PIR2bits.C2IF = 0;
#ifdef TestMode
    if (CMP1_Ready) {
       // Coil_2_LAT = CMP2_GetOutputStatus();
    }
#else
    if (CMP2_Ready) {
        StopCoil_2();
        CMP2_Ready = false;
        EndFireSequence();
    }
#endif
}

void CMP1_ISR(void)
{
    // clear the CMP1 interrupt flag
    PIR2bits.C1IF = 0;
#ifdef TestMode
    if (CMP1_Ready) {
      //  Coil_1_LAT = CMP1_GetOutputStatus();
    }
#else
    if (CMP1_Ready) {
        StopCoil_1();
        CMP1_Ready = false;
        CMP2_Ready = true;
        __delay_us(2);
        StartCoil_2();
    }
#endif

}

void EndFireSequence()
{
    Coil_1_SetLow();
    Coil_2_SetLow();
    Sensor_Enable_SetLow();
    
    CMP1_Ready = false;
    CMP2_Ready = false;
    
    TMR2_StopTimer();
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
#ifdef TestMode
    // test mode needs low and high interupts
    CM1CON1 = 0xE9;
    CM2CON1 = 0xEA;
#endif

    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
    TMR1_SetInterruptHandler(TMR1_10ms_InterruptHandler);
    TMR2_SetInterruptHandler(TMR2_500us_InterruptHandler);    
    TMR0_SetInterruptHandler(TMR0_250ms_InterruptHandler);

    IOCCF0_SetInterruptHandler(PreviousIn_InterruptHandler);
    //INTERRUPT_GlobalInterruptDisable();
    //INTERRUPT_PeripheralInterruptDisable();

    Next_out_SetLow();    
    Next_out_SetLow();

    
    while (1)
    {
        if (PreviousTriggered) {
            PreviousSettledCnt++;
            if (Previous_In_GetValue()) {
                PreviousHighCnt++;
            } else {
                PreviousHighCnt = 0;
            }

            if (PreviousHighCnt > 5) {
#ifndef TestMode
                StartCoil_1();
#endif             
                Sensor_Enable_SetHigh();
                resetPreviousDebounce();
            }
            if (PreviousSettledCnt > 15) {
                Sensor_Enable_SetLow();
                resetPreviousDebounce();
            }
        }
        if(findThrshold){
            INTERRUPT_GlobalInterruptDisable();
            INTERRUPT_PeripheralInterruptDisable();  
            Sensor_Enable_SetHigh();
            __delay_ms(500);
            Sensor_Enable_SetHigh();

            uint8_t DacOut = FindThreshold();

            RA2 = 0;
            PORTA = 0;
            LATAbits.LATA2 = 0;
            Sensor_Enable_SetLow();
            
            DAC_SetOutput(DacOut - 38);// 0.3V / (2V/256)
            canFire = true;
            startupFinished = true;
            findThrshold = false;
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
        }
#ifdef TestMode
        Coil_2_LAT = CMP2_GetOutputStatus();
        Coil_1_LAT = CMP1_GetOutputStatus();
#endif
    }
}
/**
 End of File
*/