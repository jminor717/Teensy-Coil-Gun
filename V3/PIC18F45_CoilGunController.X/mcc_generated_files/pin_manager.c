/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F45Q10
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB             :  MPLAB X 6.00

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.
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

#include "pin_manager.h"




void (*IOCAF0_InterruptHandler)(void);
void (*IOCAF1_InterruptHandler)(void);
void (*IOCAF2_InterruptHandler)(void);
void (*IOCAF3_InterruptHandler)(void);
void (*IOCAF4_InterruptHandler)(void);
void (*IOCAF5_InterruptHandler)(void);
void (*IOCCF0_InterruptHandler)(void);
void (*IOCCF1_InterruptHandler)(void);
void (*IOCCF2_InterruptHandler)(void);
void (*IOCCF3_InterruptHandler)(void);
void (*IOCEF0_InterruptHandler)(void);
void (*IOCEF1_InterruptHandler)(void);
void (*IOCEF2_InterruptHandler)(void);


void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
    LATE = 0x00;
    LATD = 0x0F;
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0xF0;

    /**
    TRISx registers
    */
    TRISE = 0x07;
    TRISA = 0xFF;
    TRISB = 0xFF;
    TRISC = 0x0F;
    TRISD = 0xF0;

    /**
    ANSELx registers
    */
    ANSELD = 0xF0;
    ANSELC = 0x00;
    ANSELB = 0xCF;
    ANSELE = 0x00;
    ANSELA = 0x40;

    /**
    WPUx registers
    */
    WPUD = 0x00;
    WPUE = 0x00;
    WPUB = 0x00;
    WPUA = 0x00;
    WPUC = 0x00;

    /**
    ODx registers
    */
    ODCONE = 0x00;
    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;
    ODCOND = 0x00;

    /**
    SLRCONx registers
    */
    SLRCONA = 0xFF;
    SLRCONB = 0xFF;
    SLRCONC = 0xFF;
    SLRCOND = 0xFF;
    SLRCONE = 0x07;

    /**
    INLVLx registers
    */
    INLVLA = 0xFF;
    INLVLB = 0xFF;
    INLVLC = 0xFF;
    INLVLD = 0xFF;
    INLVLE = 0x0F;


    /**
    IOCx registers 
    */
    //interrupt on change for group IOCAF - flag
    IOCAFbits.IOCAF0 = 0;
    //interrupt on change for group IOCAF - flag
    IOCAFbits.IOCAF1 = 0;
    //interrupt on change for group IOCAF - flag
    IOCAFbits.IOCAF2 = 0;
    //interrupt on change for group IOCAF - flag
    IOCAFbits.IOCAF3 = 0;
    //interrupt on change for group IOCAF - flag
    IOCAFbits.IOCAF4 = 0;
    //interrupt on change for group IOCAF - flag
    IOCAFbits.IOCAF5 = 0;
    //interrupt on change for group IOCAN - negative
    IOCANbits.IOCAN0 = 1;
    //interrupt on change for group IOCAN - negative
    IOCANbits.IOCAN1 = 1;
    //interrupt on change for group IOCAN - negative
    IOCANbits.IOCAN2 = 1;
    //interrupt on change for group IOCAN - negative
    IOCANbits.IOCAN3 = 1;
    //interrupt on change for group IOCAN - negative
    IOCANbits.IOCAN4 = 1;
    //interrupt on change for group IOCAN - negative
    IOCANbits.IOCAN5 = 1;
    //interrupt on change for group IOCAP - positive
    IOCAPbits.IOCAP0 = 1;
    //interrupt on change for group IOCAP - positive
    IOCAPbits.IOCAP1 = 1;
    //interrupt on change for group IOCAP - positive
    IOCAPbits.IOCAP2 = 1;
    //interrupt on change for group IOCAP - positive
    IOCAPbits.IOCAP3 = 1;
    //interrupt on change for group IOCAP - positive
    IOCAPbits.IOCAP4 = 1;
    //interrupt on change for group IOCAP - positive
    IOCAPbits.IOCAP5 = 1;
    //interrupt on change for group IOCCF - flag
    IOCCFbits.IOCCF0 = 0;
    //interrupt on change for group IOCCF - flag
    IOCCFbits.IOCCF1 = 0;
    //interrupt on change for group IOCCF - flag
    IOCCFbits.IOCCF2 = 0;
    //interrupt on change for group IOCCF - flag
    IOCCFbits.IOCCF3 = 0;
    //interrupt on change for group IOCCN - negative
    IOCCNbits.IOCCN0 = 1;
    //interrupt on change for group IOCCN - negative
    IOCCNbits.IOCCN1 = 1;
    //interrupt on change for group IOCCN - negative
    IOCCNbits.IOCCN2 = 1;
    //interrupt on change for group IOCCN - negative
    IOCCNbits.IOCCN3 = 1;
    //interrupt on change for group IOCCP - positive
    IOCCPbits.IOCCP0 = 1;
    //interrupt on change for group IOCCP - positive
    IOCCPbits.IOCCP1 = 1;
    //interrupt on change for group IOCCP - positive
    IOCCPbits.IOCCP2 = 1;
    //interrupt on change for group IOCCP - positive
    IOCCPbits.IOCCP3 = 1;
    //interrupt on change for group IOCEF - flag
    IOCEFbits.IOCEF0 = 0;
    //interrupt on change for group IOCEF - flag
    IOCEFbits.IOCEF1 = 0;
    //interrupt on change for group IOCEF - flag
    IOCEFbits.IOCEF2 = 0;
    //interrupt on change for group IOCEN - negative
    IOCENbits.IOCEN0 = 1;
    //interrupt on change for group IOCEN - negative
    IOCENbits.IOCEN1 = 1;
    //interrupt on change for group IOCEN - negative
    IOCENbits.IOCEN2 = 1;
    //interrupt on change for group IOCEP - positive
    IOCEPbits.IOCEP0 = 1;
    //interrupt on change for group IOCEP - positive
    IOCEPbits.IOCEP1 = 1;
    //interrupt on change for group IOCEP - positive
    IOCEPbits.IOCEP2 = 1;



    // register default IOC callback functions at runtime; use these methods to register a custom function
    IOCAF0_SetInterruptHandler(IOCAF0_DefaultInterruptHandler);
    IOCAF1_SetInterruptHandler(IOCAF1_DefaultInterruptHandler);
    IOCAF2_SetInterruptHandler(IOCAF2_DefaultInterruptHandler);
    IOCAF3_SetInterruptHandler(IOCAF3_DefaultInterruptHandler);
    IOCAF4_SetInterruptHandler(IOCAF4_DefaultInterruptHandler);
    IOCAF5_SetInterruptHandler(IOCAF5_DefaultInterruptHandler);
    IOCCF0_SetInterruptHandler(IOCCF0_DefaultInterruptHandler);
    IOCCF1_SetInterruptHandler(IOCCF1_DefaultInterruptHandler);
    IOCCF2_SetInterruptHandler(IOCCF2_DefaultInterruptHandler);
    IOCCF3_SetInterruptHandler(IOCCF3_DefaultInterruptHandler);
    IOCEF0_SetInterruptHandler(IOCEF0_DefaultInterruptHandler);
    IOCEF1_SetInterruptHandler(IOCEF1_DefaultInterruptHandler);
    IOCEF2_SetInterruptHandler(IOCEF2_DefaultInterruptHandler);
   
    // Enable IOCI interrupt 
    PIE0bits.IOCIE = 1; 
    
	
    T6INPPS = 0x0C;   //RB4->TMR6:T6IN;    
}
  
void PIN_MANAGER_IOC(void)
{   
	// interrupt on change for pin IOCAF0
    if(IOCAFbits.IOCAF0 == 1)
    {
        IOCAF0_ISR();  
    }	
	// interrupt on change for pin IOCAF1
    if(IOCAFbits.IOCAF1 == 1)
    {
        IOCAF1_ISR();  
    }	
	// interrupt on change for pin IOCAF2
    if(IOCAFbits.IOCAF2 == 1)
    {
        IOCAF2_ISR();  
    }	
	// interrupt on change for pin IOCAF3
    if(IOCAFbits.IOCAF3 == 1)
    {
        IOCAF3_ISR();  
    }	
	// interrupt on change for pin IOCAF4
    if(IOCAFbits.IOCAF4 == 1)
    {
        IOCAF4_ISR();  
    }	
	// interrupt on change for pin IOCAF5
    if(IOCAFbits.IOCAF5 == 1)
    {
        IOCAF5_ISR();  
    }	
	// interrupt on change for pin IOCCF0
    if(IOCCFbits.IOCCF0 == 1)
    {
        IOCCF0_ISR();  
    }	
	// interrupt on change for pin IOCCF1
    if(IOCCFbits.IOCCF1 == 1)
    {
        IOCCF1_ISR();  
    }	
	// interrupt on change for pin IOCCF2
    if(IOCCFbits.IOCCF2 == 1)
    {
        IOCCF2_ISR();  
    }	
	// interrupt on change for pin IOCCF3
    if(IOCCFbits.IOCCF3 == 1)
    {
        IOCCF3_ISR();  
    }	
	// interrupt on change for pin IOCEF0
    if(IOCEFbits.IOCEF0 == 1)
    {
        IOCEF0_ISR();  
    }	
	// interrupt on change for pin IOCEF1
    if(IOCEFbits.IOCEF1 == 1)
    {
        IOCEF1_ISR();  
    }	
	// interrupt on change for pin IOCEF2
    if(IOCEFbits.IOCEF2 == 1)
    {
        IOCEF2_ISR();  
    }	
}

/**
   IOCAF0 Interrupt Service Routine
*/
void IOCAF0_ISR(void) {

    // Add custom IOCAF0 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCAF0_InterruptHandler)
    {
        IOCAF0_InterruptHandler();
    }
    IOCAFbits.IOCAF0 = 0;
}

/**
  Allows selecting an interrupt handler for IOCAF0 at application runtime
*/
void IOCAF0_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCAF0_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCAF0
*/
void IOCAF0_DefaultInterruptHandler(void){
    // add your IOCAF0 interrupt custom code
    // or set custom function using IOCAF0_SetInterruptHandler()
}

/**
   IOCAF1 Interrupt Service Routine
*/
void IOCAF1_ISR(void) {

    // Add custom IOCAF1 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCAF1_InterruptHandler)
    {
        IOCAF1_InterruptHandler();
    }
    IOCAFbits.IOCAF1 = 0;
}

/**
  Allows selecting an interrupt handler for IOCAF1 at application runtime
*/
void IOCAF1_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCAF1_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCAF1
*/
void IOCAF1_DefaultInterruptHandler(void){
    // add your IOCAF1 interrupt custom code
    // or set custom function using IOCAF1_SetInterruptHandler()
}

/**
   IOCAF2 Interrupt Service Routine
*/
void IOCAF2_ISR(void) {

    // Add custom IOCAF2 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCAF2_InterruptHandler)
    {
        IOCAF2_InterruptHandler();
    }
    IOCAFbits.IOCAF2 = 0;
}

/**
  Allows selecting an interrupt handler for IOCAF2 at application runtime
*/
void IOCAF2_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCAF2_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCAF2
*/
void IOCAF2_DefaultInterruptHandler(void){
    // add your IOCAF2 interrupt custom code
    // or set custom function using IOCAF2_SetInterruptHandler()
}

/**
   IOCAF3 Interrupt Service Routine
*/
void IOCAF3_ISR(void) {

    // Add custom IOCAF3 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCAF3_InterruptHandler)
    {
        IOCAF3_InterruptHandler();
    }
    IOCAFbits.IOCAF3 = 0;
}

/**
  Allows selecting an interrupt handler for IOCAF3 at application runtime
*/
void IOCAF3_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCAF3_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCAF3
*/
void IOCAF3_DefaultInterruptHandler(void){
    // add your IOCAF3 interrupt custom code
    // or set custom function using IOCAF3_SetInterruptHandler()
}

/**
   IOCAF4 Interrupt Service Routine
*/
void IOCAF4_ISR(void) {

    // Add custom IOCAF4 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCAF4_InterruptHandler)
    {
        IOCAF4_InterruptHandler();
    }
    IOCAFbits.IOCAF4 = 0;
}

/**
  Allows selecting an interrupt handler for IOCAF4 at application runtime
*/
void IOCAF4_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCAF4_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCAF4
*/
void IOCAF4_DefaultInterruptHandler(void){
    // add your IOCAF4 interrupt custom code
    // or set custom function using IOCAF4_SetInterruptHandler()
}

/**
   IOCAF5 Interrupt Service Routine
*/
void IOCAF5_ISR(void) {

    // Add custom IOCAF5 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCAF5_InterruptHandler)
    {
        IOCAF5_InterruptHandler();
    }
    IOCAFbits.IOCAF5 = 0;
}

/**
  Allows selecting an interrupt handler for IOCAF5 at application runtime
*/
void IOCAF5_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCAF5_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCAF5
*/
void IOCAF5_DefaultInterruptHandler(void){
    // add your IOCAF5 interrupt custom code
    // or set custom function using IOCAF5_SetInterruptHandler()
}

/**
   IOCCF0 Interrupt Service Routine
*/
void IOCCF0_ISR(void) {

    // Add custom IOCCF0 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCCF0_InterruptHandler)
    {
        IOCCF0_InterruptHandler();
    }
    IOCCFbits.IOCCF0 = 0;
}

/**
  Allows selecting an interrupt handler for IOCCF0 at application runtime
*/
void IOCCF0_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCCF0_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCCF0
*/
void IOCCF0_DefaultInterruptHandler(void){
    // add your IOCCF0 interrupt custom code
    // or set custom function using IOCCF0_SetInterruptHandler()
}

/**
   IOCCF1 Interrupt Service Routine
*/
void IOCCF1_ISR(void) {

    // Add custom IOCCF1 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCCF1_InterruptHandler)
    {
        IOCCF1_InterruptHandler();
    }
    IOCCFbits.IOCCF1 = 0;
}

/**
  Allows selecting an interrupt handler for IOCCF1 at application runtime
*/
void IOCCF1_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCCF1_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCCF1
*/
void IOCCF1_DefaultInterruptHandler(void){
    // add your IOCCF1 interrupt custom code
    // or set custom function using IOCCF1_SetInterruptHandler()
}

/**
   IOCCF2 Interrupt Service Routine
*/
void IOCCF2_ISR(void) {

    // Add custom IOCCF2 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCCF2_InterruptHandler)
    {
        IOCCF2_InterruptHandler();
    }
    IOCCFbits.IOCCF2 = 0;
}

/**
  Allows selecting an interrupt handler for IOCCF2 at application runtime
*/
void IOCCF2_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCCF2_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCCF2
*/
void IOCCF2_DefaultInterruptHandler(void){
    // add your IOCCF2 interrupt custom code
    // or set custom function using IOCCF2_SetInterruptHandler()
}

/**
   IOCCF3 Interrupt Service Routine
*/
void IOCCF3_ISR(void) {

    // Add custom IOCCF3 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCCF3_InterruptHandler)
    {
        IOCCF3_InterruptHandler();
    }
    IOCCFbits.IOCCF3 = 0;
}

/**
  Allows selecting an interrupt handler for IOCCF3 at application runtime
*/
void IOCCF3_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCCF3_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCCF3
*/
void IOCCF3_DefaultInterruptHandler(void){
    // add your IOCCF3 interrupt custom code
    // or set custom function using IOCCF3_SetInterruptHandler()
}

/**
   IOCEF0 Interrupt Service Routine
*/
void IOCEF0_ISR(void) {

    // Add custom IOCEF0 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCEF0_InterruptHandler)
    {
        IOCEF0_InterruptHandler();
    }
    IOCEFbits.IOCEF0 = 0;
}

/**
  Allows selecting an interrupt handler for IOCEF0 at application runtime
*/
void IOCEF0_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCEF0_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCEF0
*/
void IOCEF0_DefaultInterruptHandler(void){
    // add your IOCEF0 interrupt custom code
    // or set custom function using IOCEF0_SetInterruptHandler()
}

/**
   IOCEF1 Interrupt Service Routine
*/
void IOCEF1_ISR(void) {

    // Add custom IOCEF1 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCEF1_InterruptHandler)
    {
        IOCEF1_InterruptHandler();
    }
    IOCEFbits.IOCEF1 = 0;
}

/**
  Allows selecting an interrupt handler for IOCEF1 at application runtime
*/
void IOCEF1_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCEF1_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCEF1
*/
void IOCEF1_DefaultInterruptHandler(void){
    // add your IOCEF1 interrupt custom code
    // or set custom function using IOCEF1_SetInterruptHandler()
}

/**
   IOCEF2 Interrupt Service Routine
*/
void IOCEF2_ISR(void) {

    // Add custom IOCEF2 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCEF2_InterruptHandler)
    {
        IOCEF2_InterruptHandler();
    }
    IOCEFbits.IOCEF2 = 0;
}

/**
  Allows selecting an interrupt handler for IOCEF2 at application runtime
*/
void IOCEF2_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCEF2_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCEF2
*/
void IOCEF2_DefaultInterruptHandler(void){
    // add your IOCEF2 interrupt custom code
    // or set custom function using IOCEF2_SetInterruptHandler()
}

/**
 End of File
*/