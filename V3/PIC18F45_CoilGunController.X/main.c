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

#include "mcc_generated_files/mcc.h"

/* IOC initialization function */
static void IOC_Initialize(void)
{
    // Enable IOCI interrupt 
    PIE0bits.IOCIE = 1; 
}


/* IOC ISR function */
static void Local_IOCCF4_ISR (void)
{
//    PORTD |= 0b00000100;
    /* Toggle the LED */
//    LATEbits.LATE0 = ~LATEbits.LATE0;
    RD2 = ~RD2;  // LED OFF
//    PORTD &= 0b11111011;

}

void  INTERRUPT_Initialize (void)
{
    // Disable Interrupt Priority Vectors (16CXXX Compatibility Mode)
    INTCONbits.IPEN = 0;
    INTCONbits.GIE = 1;     /* Enable global interrupts */
    INTCONbits.PEIE = 1;
}
extern volatile uint8_t IOCEFbits_Data __at(0xF22);
extern volatile uint8_t IOCCFbits_Data __at(0xF15);
extern volatile uint8_t IOCBFbits_Data __at(0xF0D);
extern volatile uint8_t IOCAFbits_Data __at(0xF05);

void __interrupt() INTERRUPT_InterruptManager (void)
{
    if(IOCAFbits_Data != 0){
        switch(IOCBFbits_Data) {
            case 0b1:
                IOCAFbits.IOCAF0 = 0;
                return;
            case 0b1 << 1:
                IOCAFbits.IOCAF1 = 0;
                return;
            case 0b1 << 2:
                IOCAFbits.IOCAF2 = 0;
                return;
            case 0b1 << 3:
                IOCAFbits.IOCAF3 = 0;
                return;
            case 0b1 << 4:
                IOCAFbits.IOCAF4 = 0;
                return;
            case 0b1 << 5:
                IOCAFbits.IOCAF5 = 0;
                return;
            default:
                break;
        }
        
        if(IOCAFbits.IOCAF0 == 1) // interrupt on change for pin IOCAF0
        {
            IOCAFbits.IOCAF0 = 0;
        }	
        if(IOCAFbits.IOCAF1 == 1) // interrupt on change for pin IOCAF1
        {
            IOCAFbits.IOCAF1 = 0;
        }	
        if(IOCAFbits.IOCAF2 == 1) // interrupt on change for pin IOCAF2
        {
            IOCAFbits.IOCAF2 = 0;
        }	
        if(IOCAFbits.IOCAF3 == 1) // interrupt on change for pin IOCAF3
        {
            IOCAFbits.IOCAF3 = 0;
        }	
        if(IOCAFbits.IOCAF4 == 1) // interrupt on change for pin IOCAF4
        {
            IOCAFbits.IOCAF4 = 0;
        }	
        if(IOCAFbits.IOCAF5 == 1) // interrupt on change for pin IOCAF5
        {
            IOCAFbits.IOCAF5 = 0;
        //        IOCBF5_ISR();  
        }
        
        IOCAFbits_Data = 0;
    }
    
    if(IOCEFbits_Data){
        switch(IOCEFbits_Data) {
            case 0b1:
                IOCEFbits.IOCEF0 = 0;
                return;
            case 0b1 << 1:
                IOCEFbits.IOCEF1 = 0;
                return;
            case 0b1 << 2:
                IOCEFbits.IOCEF2 = 0;
                return;
            default:
                break;
        } 
       
        if(IOCEFbits.IOCEF0 == 1) // interrupt on change for pin IOCCF0
        {
            IOCEFbits.IOCEF0 = 0;
        }	
        if(IOCEFbits.IOCEF1 == 1) // interrupt on change for pin IOCCF1
        {
            IOCEFbits.IOCEF1 = 0;
        }	
        if(IOCEFbits.IOCEF2 == 1) // interrupt on change for pin IOCCF2
        {
            IOCEFbits.IOCEF2 = 0;
        }	       
        IOCEFbits_Data = 0;
    }

    if(IOCCFbits_Data){
        switch(IOCCFbits_Data) {
            case 0b1:
                IOCCFbits.IOCCF0 = 0;
                return;
            case 0b1 << 1:
                IOCCFbits.IOCCF1 = 0;
                Local_IOCCF4_ISR();  
                return;
            default:
                break;
        } 
       
        if(IOCCFbits.IOCCF0 == 1) // interrupt on change for pin IOCCF0
        {
            IOCCFbits.IOCCF0 = 0;
        }	
        if(IOCCFbits.IOCCF1 == 1) // interrupt on change for pin IOCCF1
        {
            IOCCFbits.IOCCF1 = 0;
            Local_IOCCF4_ISR();  
        }	
         
        IOCCFbits_Data = 0;
    }
}

/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    IOC_Initialize();
    INTERRUPT_Initialize();
    
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
//    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
//    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1)
    {
        PORTD &= 0b11111101;
//        PORTD |= 0b00000100;
//        RD1= 0;  // LED OFF
//        RD2= 0;  // LED OFF
        Nop();
        Nop();        
        Nop();        
        Nop();
        PORTD |= 0b00000010;
//        RD1= 1;  // LED ON
//        RD2= 1;  // LED ON
        Nop();
        Nop();        
        Nop();        
        Nop();
        PORTD &= 0b11111101;
//        RD2= 0;  // LED OFF
//        RD1= 0;  // LED OFF
        __delay_ms(100); // 1 Second Delay
        PORTD |= 0b00000010;
//        RD2= 1;  // LED ON
//        RD1= 1;  // LED ON
        __delay_ms(100); // 1 Second Delay
    }
}
/**
 End of File
*/