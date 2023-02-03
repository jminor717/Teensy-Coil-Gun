/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F1705
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set Sensor_Enable aliases
#define Sensor_Enable_TRIS                 TRISAbits.TRISA2
#define Sensor_Enable_LAT                  LATAbits.LATA2
#define Sensor_Enable_PORT                 PORTAbits.RA2
#define Sensor_Enable_WPU                  WPUAbits.WPUA2
#define Sensor_Enable_OD                   ODCONAbits.ODA2
#define Sensor_Enable_ANS                  ANSELAbits.ANSA2
#define Sensor_Enable_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define Sensor_Enable_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define Sensor_Enable_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define Sensor_Enable_GetValue()           PORTAbits.RA2
#define Sensor_Enable_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define Sensor_Enable_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define Sensor_Enable_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define Sensor_Enable_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define Sensor_Enable_SetPushPull()        do { ODCONAbits.ODA2 = 0; } while(0)
#define Sensor_Enable_SetOpenDrain()       do { ODCONAbits.ODA2 = 1; } while(0)
#define Sensor_Enable_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define Sensor_Enable_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set Coil_1 aliases
#define Coil_1_TRIS                 TRISAbits.TRISA4
#define Coil_1_LAT                  LATAbits.LATA4
#define Coil_1_PORT                 PORTAbits.RA4
#define Coil_1_WPU                  WPUAbits.WPUA4
#define Coil_1_OD                   ODCONAbits.ODA4
#define Coil_1_ANS                  ANSELAbits.ANSA4
#define Coil_1_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define Coil_1_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define Coil_1_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define Coil_1_GetValue()           PORTAbits.RA4
#define Coil_1_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define Coil_1_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define Coil_1_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define Coil_1_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define Coil_1_SetPushPull()        do { ODCONAbits.ODA4 = 0; } while(0)
#define Coil_1_SetOpenDrain()       do { ODCONAbits.ODA4 = 1; } while(0)
#define Coil_1_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define Coil_1_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set Next_out aliases
#define Next_out_TRIS                 TRISAbits.TRISA5
#define Next_out_LAT                  LATAbits.LATA5
#define Next_out_PORT                 PORTAbits.RA5
#define Next_out_WPU                  WPUAbits.WPUA5
#define Next_out_OD                   ODCONAbits.ODA5
#define Next_out_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define Next_out_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define Next_out_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define Next_out_GetValue()           PORTAbits.RA5
#define Next_out_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define Next_out_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define Next_out_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define Next_out_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define Next_out_SetPushPull()        do { ODCONAbits.ODA5 = 0; } while(0)
#define Next_out_SetOpenDrain()       do { ODCONAbits.ODA5 = 1; } while(0)

// get/set Previous_In aliases
#define Previous_In_TRIS                 TRISCbits.TRISC0
#define Previous_In_LAT                  LATCbits.LATC0
#define Previous_In_PORT                 PORTCbits.RC0
#define Previous_In_WPU                  WPUCbits.WPUC0
#define Previous_In_OD                   ODCONCbits.ODC0
#define Previous_In_ANS                  ANSELCbits.ANSC0
#define Previous_In_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define Previous_In_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define Previous_In_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define Previous_In_GetValue()           PORTCbits.RC0
#define Previous_In_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define Previous_In_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define Previous_In_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define Previous_In_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define Previous_In_SetPushPull()        do { ODCONCbits.ODC0 = 0; } while(0)
#define Previous_In_SetOpenDrain()       do { ODCONCbits.ODC0 = 1; } while(0)
#define Previous_In_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define Previous_In_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set S1 aliases
#define S1_TRIS                 TRISCbits.TRISC1
#define S1_LAT                  LATCbits.LATC1
#define S1_PORT                 PORTCbits.RC1
#define S1_WPU                  WPUCbits.WPUC1
#define S1_OD                   ODCONCbits.ODC1
#define S1_ANS                  ANSELCbits.ANSC1
#define S1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define S1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define S1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define S1_GetValue()           PORTCbits.RC1
#define S1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define S1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define S1_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define S1_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define S1_SetPushPull()        do { ODCONCbits.ODC1 = 0; } while(0)
#define S1_SetOpenDrain()       do { ODCONCbits.ODC1 = 1; } while(0)
#define S1_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define S1_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set S2 aliases
#define S2_TRIS                 TRISCbits.TRISC2
#define S2_LAT                  LATCbits.LATC2
#define S2_PORT                 PORTCbits.RC2
#define S2_WPU                  WPUCbits.WPUC2
#define S2_OD                   ODCONCbits.ODC2
#define S2_ANS                  ANSELCbits.ANSC2
#define S2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define S2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define S2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define S2_GetValue()           PORTCbits.RC2
#define S2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define S2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define S2_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define S2_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define S2_SetPushPull()        do { ODCONCbits.ODC2 = 0; } while(0)
#define S2_SetOpenDrain()       do { ODCONCbits.ODC2 = 1; } while(0)
#define S2_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define S2_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set IO_RC3 aliases
#define IO_RC3_TRIS                 TRISCbits.TRISC3
#define IO_RC3_LAT                  LATCbits.LATC3
#define IO_RC3_PORT                 PORTCbits.RC3
#define IO_RC3_WPU                  WPUCbits.WPUC3
#define IO_RC3_OD                   ODCONCbits.ODC3
#define IO_RC3_ANS                  ANSELCbits.ANSC3
#define IO_RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define IO_RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define IO_RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define IO_RC3_GetValue()           PORTCbits.RC3
#define IO_RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define IO_RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define IO_RC3_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define IO_RC3_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define IO_RC3_SetPushPull()        do { ODCONCbits.ODC3 = 0; } while(0)
#define IO_RC3_SetOpenDrain()       do { ODCONCbits.ODC3 = 1; } while(0)
#define IO_RC3_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define IO_RC3_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set IO_RC4 aliases
#define IO_RC4_TRIS                 TRISCbits.TRISC4
#define IO_RC4_LAT                  LATCbits.LATC4
#define IO_RC4_PORT                 PORTCbits.RC4
#define IO_RC4_WPU                  WPUCbits.WPUC4
#define IO_RC4_OD                   ODCONCbits.ODC4
#define IO_RC4_ANS                  ANSELCbits.ANSC4
#define IO_RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define IO_RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define IO_RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define IO_RC4_GetValue()           PORTCbits.RC4
#define IO_RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define IO_RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define IO_RC4_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define IO_RC4_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define IO_RC4_SetPushPull()        do { ODCONCbits.ODC4 = 0; } while(0)
#define IO_RC4_SetOpenDrain()       do { ODCONCbits.ODC4 = 1; } while(0)
#define IO_RC4_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define IO_RC4_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set Coil_2 aliases
#define Coil_2_TRIS                 TRISCbits.TRISC5
#define Coil_2_LAT                  LATCbits.LATC5
#define Coil_2_PORT                 PORTCbits.RC5
#define Coil_2_WPU                  WPUCbits.WPUC5
#define Coil_2_OD                   ODCONCbits.ODC5
#define Coil_2_ANS                  ANSELCbits.ANSC5
#define Coil_2_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define Coil_2_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define Coil_2_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define Coil_2_GetValue()           PORTCbits.RC5
#define Coil_2_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define Coil_2_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define Coil_2_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define Coil_2_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define Coil_2_SetPushPull()        do { ODCONCbits.ODC5 = 0; } while(0)
#define Coil_2_SetOpenDrain()       do { ODCONCbits.ODC5 = 1; } while(0)
#define Coil_2_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define Coil_2_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCCF0 pin functionality
 * @Example
    IOCCF0_ISR();
 */
void IOCCF0_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCCF0 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCCF0 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF0_SetInterruptHandler(MyInterruptHandler);

*/
void IOCCF0_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCCF0 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCCF0_SetInterruptHandler() method.
    This handler is called every time the IOCCF0 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF0_SetInterruptHandler(IOCCF0_InterruptHandler);

*/
extern void (*IOCCF0_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCCF0 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCCF0_SetInterruptHandler() method.
    This handler is called every time the IOCCF0 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF0_SetInterruptHandler(IOCCF0_DefaultInterruptHandler);

*/
void IOCCF0_DefaultInterruptHandler(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/