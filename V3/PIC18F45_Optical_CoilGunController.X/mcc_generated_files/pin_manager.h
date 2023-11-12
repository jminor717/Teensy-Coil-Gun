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
        Device            :  PIC18F45Q10
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

// get/set S1_in aliases
#define S1_in_TRIS                 TRISAbits.TRISA0
#define S1_in_LAT                  LATAbits.LATA0
#define S1_in_PORT                 PORTAbits.RA0
#define S1_in_WPU                  WPUAbits.WPUA0
#define S1_in_OD                   ODCONAbits.ODCA0
#define S1_in_ANS                  ANSELAbits.ANSELA0
#define S1_in_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define S1_in_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define S1_in_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define S1_in_GetValue()           PORTAbits.RA0
#define S1_in_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define S1_in_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define S1_in_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define S1_in_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define S1_in_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define S1_in_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define S1_in_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define S1_in_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set S2_in aliases
#define S2_in_TRIS                 TRISAbits.TRISA1
#define S2_in_LAT                  LATAbits.LATA1
#define S2_in_PORT                 PORTAbits.RA1
#define S2_in_WPU                  WPUAbits.WPUA1
#define S2_in_OD                   ODCONAbits.ODCA1
#define S2_in_ANS                  ANSELAbits.ANSELA1
#define S2_in_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define S2_in_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define S2_in_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define S2_in_GetValue()           PORTAbits.RA1
#define S2_in_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define S2_in_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define S2_in_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define S2_in_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define S2_in_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define S2_in_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define S2_in_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define S2_in_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set S3_in aliases
#define S3_in_TRIS                 TRISAbits.TRISA2
#define S3_in_LAT                  LATAbits.LATA2
#define S3_in_PORT                 PORTAbits.RA2
#define S3_in_WPU                  WPUAbits.WPUA2
#define S3_in_OD                   ODCONAbits.ODCA2
#define S3_in_ANS                  ANSELAbits.ANSELA2
#define S3_in_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define S3_in_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define S3_in_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define S3_in_GetValue()           PORTAbits.RA2
#define S3_in_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define S3_in_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define S3_in_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define S3_in_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define S3_in_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define S3_in_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define S3_in_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define S3_in_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set S4_in aliases
#define S4_in_TRIS                 TRISAbits.TRISA3
#define S4_in_LAT                  LATAbits.LATA3
#define S4_in_PORT                 PORTAbits.RA3
#define S4_in_WPU                  WPUAbits.WPUA3
#define S4_in_OD                   ODCONAbits.ODCA3
#define S4_in_ANS                  ANSELAbits.ANSELA3
#define S4_in_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define S4_in_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define S4_in_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define S4_in_GetValue()           PORTAbits.RA3
#define S4_in_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define S4_in_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define S4_in_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define S4_in_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define S4_in_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define S4_in_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define S4_in_SetAnalogMode()      do { ANSELAbits.ANSELA3 = 1; } while(0)
#define S4_in_SetDigitalMode()     do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set S5_in aliases
#define S5_in_TRIS                 TRISAbits.TRISA4
#define S5_in_LAT                  LATAbits.LATA4
#define S5_in_PORT                 PORTAbits.RA4
#define S5_in_WPU                  WPUAbits.WPUA4
#define S5_in_OD                   ODCONAbits.ODCA4
#define S5_in_ANS                  ANSELAbits.ANSELA4
#define S5_in_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define S5_in_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define S5_in_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define S5_in_GetValue()           PORTAbits.RA4
#define S5_in_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define S5_in_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define S5_in_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define S5_in_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define S5_in_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define S5_in_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define S5_in_SetAnalogMode()      do { ANSELAbits.ANSELA4 = 1; } while(0)
#define S5_in_SetDigitalMode()     do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set S6_in aliases
#define S6_in_TRIS                 TRISAbits.TRISA5
#define S6_in_LAT                  LATAbits.LATA5
#define S6_in_PORT                 PORTAbits.RA5
#define S6_in_WPU                  WPUAbits.WPUA5
#define S6_in_OD                   ODCONAbits.ODCA5
#define S6_in_ANS                  ANSELAbits.ANSELA5
#define S6_in_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define S6_in_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define S6_in_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define S6_in_GetValue()           PORTAbits.RA5
#define S6_in_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define S6_in_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define S6_in_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define S6_in_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define S6_in_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define S6_in_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define S6_in_SetAnalogMode()      do { ANSELAbits.ANSELA5 = 1; } while(0)
#define S6_in_SetDigitalMode()     do { ANSELAbits.ANSELA5 = 0; } while(0)

// get/set C2_H aliases
#define C2_H_TRIS                 TRISAbits.TRISA6
#define C2_H_LAT                  LATAbits.LATA6
#define C2_H_PORT                 PORTAbits.RA6
#define C2_H_WPU                  WPUAbits.WPUA6
#define C2_H_OD                   ODCONAbits.ODCA6
#define C2_H_ANS                  ANSELAbits.ANSELA6
#define C2_H_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define C2_H_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define C2_H_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define C2_H_GetValue()           PORTAbits.RA6
#define C2_H_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define C2_H_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define C2_H_SetPullup()          do { WPUAbits.WPUA6 = 1; } while(0)
#define C2_H_ResetPullup()        do { WPUAbits.WPUA6 = 0; } while(0)
#define C2_H_SetPushPull()        do { ODCONAbits.ODCA6 = 0; } while(0)
#define C2_H_SetOpenDrain()       do { ODCONAbits.ODCA6 = 1; } while(0)
#define C2_H_SetAnalogMode()      do { ANSELAbits.ANSELA6 = 1; } while(0)
#define C2_H_SetDigitalMode()     do { ANSELAbits.ANSELA6 = 0; } while(0)

// get/set C2_L aliases
#define C2_L_TRIS                 TRISAbits.TRISA7
#define C2_L_LAT                  LATAbits.LATA7
#define C2_L_PORT                 PORTAbits.RA7
#define C2_L_WPU                  WPUAbits.WPUA7
#define C2_L_OD                   ODCONAbits.ODCA7
#define C2_L_ANS                  ANSELAbits.ANSELA7
#define C2_L_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define C2_L_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define C2_L_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define C2_L_GetValue()           PORTAbits.RA7
#define C2_L_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define C2_L_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define C2_L_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define C2_L_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define C2_L_SetPushPull()        do { ODCONAbits.ODCA7 = 0; } while(0)
#define C2_L_SetOpenDrain()       do { ODCONAbits.ODCA7 = 1; } while(0)
#define C2_L_SetAnalogMode()      do { ANSELAbits.ANSELA7 = 1; } while(0)
#define C2_L_SetDigitalMode()     do { ANSELAbits.ANSELA7 = 0; } while(0)

// get/set RB4 procedures
#define RB4_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define RB4_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define RB4_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define RB4_GetValue()              PORTBbits.RB4
#define RB4_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define RB4_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define RB4_SetPullup()             do { WPUBbits.WPUB4 = 1; } while(0)
#define RB4_ResetPullup()           do { WPUBbits.WPUB4 = 0; } while(0)
#define RB4_SetAnalogMode()         do { ANSELBbits.ANSELB4 = 1; } while(0)
#define RB4_SetDigitalMode()        do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set RB5 procedures
#define RB5_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define RB5_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define RB5_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define RB5_GetValue()              PORTBbits.RB5
#define RB5_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define RB5_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define RB5_SetPullup()             do { WPUBbits.WPUB5 = 1; } while(0)
#define RB5_ResetPullup()           do { WPUBbits.WPUB5 = 0; } while(0)
#define RB5_SetAnalogMode()         do { ANSELBbits.ANSELB5 = 1; } while(0)
#define RB5_SetDigitalMode()        do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set C1_L aliases
#define C1_L_TRIS                 TRISCbits.TRISC0
#define C1_L_LAT                  LATCbits.LATC0
#define C1_L_PORT                 PORTCbits.RC0
#define C1_L_WPU                  WPUCbits.WPUC0
#define C1_L_OD                   ODCONCbits.ODCC0
#define C1_L_ANS                  ANSELCbits.ANSELC0
#define C1_L_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define C1_L_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define C1_L_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define C1_L_GetValue()           PORTCbits.RC0
#define C1_L_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define C1_L_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define C1_L_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define C1_L_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define C1_L_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define C1_L_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define C1_L_SetAnalogMode()      do { ANSELCbits.ANSELC0 = 1; } while(0)
#define C1_L_SetDigitalMode()     do { ANSELCbits.ANSELC0 = 0; } while(0)

// get/set C1_H aliases
#define C1_H_TRIS                 TRISCbits.TRISC1
#define C1_H_LAT                  LATCbits.LATC1
#define C1_H_PORT                 PORTCbits.RC1
#define C1_H_WPU                  WPUCbits.WPUC1
#define C1_H_OD                   ODCONCbits.ODCC1
#define C1_H_ANS                  ANSELCbits.ANSELC1
#define C1_H_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define C1_H_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define C1_H_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define C1_H_GetValue()           PORTCbits.RC1
#define C1_H_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define C1_H_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define C1_H_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define C1_H_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define C1_H_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define C1_H_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define C1_H_SetAnalogMode()      do { ANSELCbits.ANSELC1 = 1; } while(0)
#define C1_H_SetDigitalMode()     do { ANSELCbits.ANSELC1 = 0; } while(0)

// get/set Safety_in aliases
#define Safety_in_TRIS                 TRISCbits.TRISC2
#define Safety_in_LAT                  LATCbits.LATC2
#define Safety_in_PORT                 PORTCbits.RC2
#define Safety_in_WPU                  WPUCbits.WPUC2
#define Safety_in_OD                   ODCONCbits.ODCC2
#define Safety_in_ANS                  ANSELCbits.ANSELC2
#define Safety_in_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define Safety_in_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define Safety_in_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define Safety_in_GetValue()           PORTCbits.RC2
#define Safety_in_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define Safety_in_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define Safety_in_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define Safety_in_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define Safety_in_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define Safety_in_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define Safety_in_SetAnalogMode()      do { ANSELCbits.ANSELC2 = 1; } while(0)
#define Safety_in_SetDigitalMode()     do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set Trigger_in aliases
#define Trigger_in_TRIS                 TRISCbits.TRISC3
#define Trigger_in_LAT                  LATCbits.LATC3
#define Trigger_in_PORT                 PORTCbits.RC3
#define Trigger_in_WPU                  WPUCbits.WPUC3
#define Trigger_in_OD                   ODCONCbits.ODCC3
#define Trigger_in_ANS                  ANSELCbits.ANSELC3
#define Trigger_in_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define Trigger_in_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define Trigger_in_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define Trigger_in_GetValue()           PORTCbits.RC3
#define Trigger_in_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define Trigger_in_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define Trigger_in_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define Trigger_in_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define Trigger_in_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define Trigger_in_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define Trigger_in_SetAnalogMode()      do { ANSELCbits.ANSELC3 = 1; } while(0)
#define Trigger_in_SetDigitalMode()     do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set CC6 aliases
#define CC6_TRIS                 TRISCbits.TRISC4
#define CC6_LAT                  LATCbits.LATC4
#define CC6_PORT                 PORTCbits.RC4
#define CC6_WPU                  WPUCbits.WPUC4
#define CC6_OD                   ODCONCbits.ODCC4
#define CC6_ANS                  ANSELCbits.ANSELC4
#define CC6_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define CC6_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define CC6_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define CC6_GetValue()           PORTCbits.RC4
#define CC6_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define CC6_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define CC6_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define CC6_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define CC6_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define CC6_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define CC6_SetAnalogMode()      do { ANSELCbits.ANSELC4 = 1; } while(0)
#define CC6_SetDigitalMode()     do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set CC5 aliases
#define CC5_TRIS                 TRISCbits.TRISC5
#define CC5_LAT                  LATCbits.LATC5
#define CC5_PORT                 PORTCbits.RC5
#define CC5_WPU                  WPUCbits.WPUC5
#define CC5_OD                   ODCONCbits.ODCC5
#define CC5_ANS                  ANSELCbits.ANSELC5
#define CC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define CC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define CC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define CC5_GetValue()           PORTCbits.RC5
#define CC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define CC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define CC5_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define CC5_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define CC5_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define CC5_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define CC5_SetAnalogMode()      do { ANSELCbits.ANSELC5 = 1; } while(0)
#define CC5_SetDigitalMode()     do { ANSELCbits.ANSELC5 = 0; } while(0)

// get/set CC4 aliases
#define CC4_TRIS                 TRISCbits.TRISC6
#define CC4_LAT                  LATCbits.LATC6
#define CC4_PORT                 PORTCbits.RC6
#define CC4_WPU                  WPUCbits.WPUC6
#define CC4_OD                   ODCONCbits.ODCC6
#define CC4_ANS                  ANSELCbits.ANSELC6
#define CC4_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define CC4_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define CC4_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define CC4_GetValue()           PORTCbits.RC6
#define CC4_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define CC4_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define CC4_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define CC4_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define CC4_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define CC4_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define CC4_SetAnalogMode()      do { ANSELCbits.ANSELC6 = 1; } while(0)
#define CC4_SetDigitalMode()     do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set CC3 aliases
#define CC3_TRIS                 TRISCbits.TRISC7
#define CC3_LAT                  LATCbits.LATC7
#define CC3_PORT                 PORTCbits.RC7
#define CC3_WPU                  WPUCbits.WPUC7
#define CC3_OD                   ODCONCbits.ODCC7
#define CC3_ANS                  ANSELCbits.ANSELC7
#define CC3_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define CC3_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define CC3_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define CC3_GetValue()           PORTCbits.RC7
#define CC3_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define CC3_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define CC3_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define CC3_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define CC3_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define CC3_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define CC3_SetAnalogMode()      do { ANSELCbits.ANSELC7 = 1; } while(0)
#define CC3_SetDigitalMode()     do { ANSELCbits.ANSELC7 = 0; } while(0)

// get/set CC8 aliases
#define CC8_TRIS                 TRISDbits.TRISD2
#define CC8_LAT                  LATDbits.LATD2
#define CC8_PORT                 PORTDbits.RD2
#define CC8_WPU                  WPUDbits.WPUD2
#define CC8_OD                   ODCONDbits.ODCD2
#define CC8_ANS                  ANSELDbits.ANSELD2
#define CC8_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define CC8_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define CC8_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define CC8_GetValue()           PORTDbits.RD2
#define CC8_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define CC8_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define CC8_SetPullup()          do { WPUDbits.WPUD2 = 1; } while(0)
#define CC8_ResetPullup()        do { WPUDbits.WPUD2 = 0; } while(0)
#define CC8_SetPushPull()        do { ODCONDbits.ODCD2 = 0; } while(0)
#define CC8_SetOpenDrain()       do { ODCONDbits.ODCD2 = 1; } while(0)
#define CC8_SetAnalogMode()      do { ANSELDbits.ANSELD2 = 1; } while(0)
#define CC8_SetDigitalMode()     do { ANSELDbits.ANSELD2 = 0; } while(0)

// get/set CC7 aliases
#define CC7_TRIS                 TRISDbits.TRISD3
#define CC7_LAT                  LATDbits.LATD3
#define CC7_PORT                 PORTDbits.RD3
#define CC7_WPU                  WPUDbits.WPUD3
#define CC7_OD                   ODCONDbits.ODCD3
#define CC7_ANS                  ANSELDbits.ANSELD3
#define CC7_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define CC7_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define CC7_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define CC7_GetValue()           PORTDbits.RD3
#define CC7_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define CC7_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)
#define CC7_SetPullup()          do { WPUDbits.WPUD3 = 1; } while(0)
#define CC7_ResetPullup()        do { WPUDbits.WPUD3 = 0; } while(0)
#define CC7_SetPushPull()        do { ODCONDbits.ODCD3 = 0; } while(0)
#define CC7_SetOpenDrain()       do { ODCONDbits.ODCD3 = 1; } while(0)
#define CC7_SetAnalogMode()      do { ANSELDbits.ANSELD3 = 1; } while(0)
#define CC7_SetDigitalMode()     do { ANSELDbits.ANSELD3 = 0; } while(0)

// get/set CC2 aliases
#define CC2_TRIS                 TRISDbits.TRISD4
#define CC2_LAT                  LATDbits.LATD4
#define CC2_PORT                 PORTDbits.RD4
#define CC2_WPU                  WPUDbits.WPUD4
#define CC2_OD                   ODCONDbits.ODCD4
#define CC2_ANS                  ANSELDbits.ANSELD4
#define CC2_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define CC2_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define CC2_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define CC2_GetValue()           PORTDbits.RD4
#define CC2_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define CC2_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)
#define CC2_SetPullup()          do { WPUDbits.WPUD4 = 1; } while(0)
#define CC2_ResetPullup()        do { WPUDbits.WPUD4 = 0; } while(0)
#define CC2_SetPushPull()        do { ODCONDbits.ODCD4 = 0; } while(0)
#define CC2_SetOpenDrain()       do { ODCONDbits.ODCD4 = 1; } while(0)
#define CC2_SetAnalogMode()      do { ANSELDbits.ANSELD4 = 1; } while(0)
#define CC2_SetDigitalMode()     do { ANSELDbits.ANSELD4 = 0; } while(0)

// get/set CC1 aliases
#define CC1_TRIS                 TRISDbits.TRISD5
#define CC1_LAT                  LATDbits.LATD5
#define CC1_PORT                 PORTDbits.RD5
#define CC1_WPU                  WPUDbits.WPUD5
#define CC1_OD                   ODCONDbits.ODCD5
#define CC1_ANS                  ANSELDbits.ANSELD5
#define CC1_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define CC1_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define CC1_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define CC1_GetValue()           PORTDbits.RD5
#define CC1_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define CC1_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define CC1_SetPullup()          do { WPUDbits.WPUD5 = 1; } while(0)
#define CC1_ResetPullup()        do { WPUDbits.WPUD5 = 0; } while(0)
#define CC1_SetPushPull()        do { ODCONDbits.ODCD5 = 0; } while(0)
#define CC1_SetOpenDrain()       do { ODCONDbits.ODCD5 = 1; } while(0)
#define CC1_SetAnalogMode()      do { ANSELDbits.ANSELD5 = 1; } while(0)
#define CC1_SetDigitalMode()     do { ANSELDbits.ANSELD5 = 0; } while(0)

// get/set S7_in aliases
#define S7_in_TRIS                 TRISEbits.TRISE0
#define S7_in_LAT                  LATEbits.LATE0
#define S7_in_PORT                 PORTEbits.RE0
#define S7_in_WPU                  WPUEbits.WPUE0
#define S7_in_OD                   ODCONEbits.ODCE0
#define S7_in_ANS                  ANSELEbits.ANSELE0
#define S7_in_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define S7_in_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define S7_in_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define S7_in_GetValue()           PORTEbits.RE0
#define S7_in_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define S7_in_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define S7_in_SetPullup()          do { WPUEbits.WPUE0 = 1; } while(0)
#define S7_in_ResetPullup()        do { WPUEbits.WPUE0 = 0; } while(0)
#define S7_in_SetPushPull()        do { ODCONEbits.ODCE0 = 0; } while(0)
#define S7_in_SetOpenDrain()       do { ODCONEbits.ODCE0 = 1; } while(0)
#define S7_in_SetAnalogMode()      do { ANSELEbits.ANSELE0 = 1; } while(0)
#define S7_in_SetDigitalMode()     do { ANSELEbits.ANSELE0 = 0; } while(0)

// get/set S8_in aliases
#define S8_in_TRIS                 TRISEbits.TRISE1
#define S8_in_LAT                  LATEbits.LATE1
#define S8_in_PORT                 PORTEbits.RE1
#define S8_in_WPU                  WPUEbits.WPUE1
#define S8_in_OD                   ODCONEbits.ODCE1
#define S8_in_ANS                  ANSELEbits.ANSELE1
#define S8_in_SetHigh()            do { LATEbits.LATE1 = 1; } while(0)
#define S8_in_SetLow()             do { LATEbits.LATE1 = 0; } while(0)
#define S8_in_Toggle()             do { LATEbits.LATE1 = ~LATEbits.LATE1; } while(0)
#define S8_in_GetValue()           PORTEbits.RE1
#define S8_in_SetDigitalInput()    do { TRISEbits.TRISE1 = 1; } while(0)
#define S8_in_SetDigitalOutput()   do { TRISEbits.TRISE1 = 0; } while(0)
#define S8_in_SetPullup()          do { WPUEbits.WPUE1 = 1; } while(0)
#define S8_in_ResetPullup()        do { WPUEbits.WPUE1 = 0; } while(0)
#define S8_in_SetPushPull()        do { ODCONEbits.ODCE1 = 0; } while(0)
#define S8_in_SetOpenDrain()       do { ODCONEbits.ODCE1 = 1; } while(0)
#define S8_in_SetAnalogMode()      do { ANSELEbits.ANSELE1 = 1; } while(0)
#define S8_in_SetDigitalMode()     do { ANSELEbits.ANSELE1 = 0; } while(0)

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
    Interrupt on Change Handler for the IOCAF0 pin functionality
 * @Example
    IOCAF0_ISR();
 */
void IOCAF0_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCAF0 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCAF0 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF0_SetInterruptHandler(MyInterruptHandler);

*/
void IOCAF0_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCAF0 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCAF0_SetInterruptHandler() method.
    This handler is called every time the IOCAF0 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF0_SetInterruptHandler(IOCAF0_InterruptHandler);

*/
extern void (*IOCAF0_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCAF0 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCAF0_SetInterruptHandler() method.
    This handler is called every time the IOCAF0 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF0_SetInterruptHandler(IOCAF0_DefaultInterruptHandler);

*/
void IOCAF0_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCAF1 pin functionality
 * @Example
    IOCAF1_ISR();
 */
void IOCAF1_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCAF1 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCAF1 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF1_SetInterruptHandler(MyInterruptHandler);

*/
void IOCAF1_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCAF1 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCAF1_SetInterruptHandler() method.
    This handler is called every time the IOCAF1 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF1_SetInterruptHandler(IOCAF1_InterruptHandler);

*/
extern void (*IOCAF1_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCAF1 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCAF1_SetInterruptHandler() method.
    This handler is called every time the IOCAF1 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF1_SetInterruptHandler(IOCAF1_DefaultInterruptHandler);

*/
void IOCAF1_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCAF2 pin functionality
 * @Example
    IOCAF2_ISR();
 */
void IOCAF2_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCAF2 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCAF2 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF2_SetInterruptHandler(MyInterruptHandler);

*/
void IOCAF2_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCAF2 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCAF2_SetInterruptHandler() method.
    This handler is called every time the IOCAF2 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF2_SetInterruptHandler(IOCAF2_InterruptHandler);

*/
extern void (*IOCAF2_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCAF2 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCAF2_SetInterruptHandler() method.
    This handler is called every time the IOCAF2 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF2_SetInterruptHandler(IOCAF2_DefaultInterruptHandler);

*/
void IOCAF2_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCAF3 pin functionality
 * @Example
    IOCAF3_ISR();
 */
void IOCAF3_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCAF3 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCAF3 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF3_SetInterruptHandler(MyInterruptHandler);

*/
void IOCAF3_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCAF3 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCAF3_SetInterruptHandler() method.
    This handler is called every time the IOCAF3 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF3_SetInterruptHandler(IOCAF3_InterruptHandler);

*/
extern void (*IOCAF3_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCAF3 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCAF3_SetInterruptHandler() method.
    This handler is called every time the IOCAF3 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF3_SetInterruptHandler(IOCAF3_DefaultInterruptHandler);

*/
void IOCAF3_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCAF4 pin functionality
 * @Example
    IOCAF4_ISR();
 */
void IOCAF4_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCAF4 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCAF4 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF4_SetInterruptHandler(MyInterruptHandler);

*/
void IOCAF4_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCAF4 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCAF4_SetInterruptHandler() method.
    This handler is called every time the IOCAF4 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF4_SetInterruptHandler(IOCAF4_InterruptHandler);

*/
extern void (*IOCAF4_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCAF4 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCAF4_SetInterruptHandler() method.
    This handler is called every time the IOCAF4 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF4_SetInterruptHandler(IOCAF4_DefaultInterruptHandler);

*/
void IOCAF4_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCAF5 pin functionality
 * @Example
    IOCAF5_ISR();
 */
void IOCAF5_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCAF5 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCAF5 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF5_SetInterruptHandler(MyInterruptHandler);

*/
void IOCAF5_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCAF5 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCAF5_SetInterruptHandler() method.
    This handler is called every time the IOCAF5 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF5_SetInterruptHandler(IOCAF5_InterruptHandler);

*/
extern void (*IOCAF5_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCAF5 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCAF5_SetInterruptHandler() method.
    This handler is called every time the IOCAF5 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCAF5_SetInterruptHandler(IOCAF5_DefaultInterruptHandler);

*/
void IOCAF5_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCCF2 pin functionality
 * @Example
    IOCCF2_ISR();
 */
void IOCCF2_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCCF2 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCCF2 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF2_SetInterruptHandler(MyInterruptHandler);

*/
void IOCCF2_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCCF2 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCCF2_SetInterruptHandler() method.
    This handler is called every time the IOCCF2 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF2_SetInterruptHandler(IOCCF2_InterruptHandler);

*/
extern void (*IOCCF2_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCCF2 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCCF2_SetInterruptHandler() method.
    This handler is called every time the IOCCF2 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF2_SetInterruptHandler(IOCCF2_DefaultInterruptHandler);

*/
void IOCCF2_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCCF3 pin functionality
 * @Example
    IOCCF3_ISR();
 */
void IOCCF3_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCCF3 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCCF3 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF3_SetInterruptHandler(MyInterruptHandler);

*/
void IOCCF3_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCCF3 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCCF3_SetInterruptHandler() method.
    This handler is called every time the IOCCF3 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF3_SetInterruptHandler(IOCCF3_InterruptHandler);

*/
extern void (*IOCCF3_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCCF3 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCCF3_SetInterruptHandler() method.
    This handler is called every time the IOCCF3 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF3_SetInterruptHandler(IOCCF3_DefaultInterruptHandler);

*/
void IOCCF3_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCEF0 pin functionality
 * @Example
    IOCEF0_ISR();
 */
void IOCEF0_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCEF0 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCEF0 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCEF0_SetInterruptHandler(MyInterruptHandler);

*/
void IOCEF0_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCEF0 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCEF0_SetInterruptHandler() method.
    This handler is called every time the IOCEF0 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCEF0_SetInterruptHandler(IOCEF0_InterruptHandler);

*/
extern void (*IOCEF0_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCEF0 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCEF0_SetInterruptHandler() method.
    This handler is called every time the IOCEF0 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCEF0_SetInterruptHandler(IOCEF0_DefaultInterruptHandler);

*/
void IOCEF0_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCEF1 pin functionality
 * @Example
    IOCEF1_ISR();
 */
void IOCEF1_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCEF1 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCEF1 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCEF1_SetInterruptHandler(MyInterruptHandler);

*/
void IOCEF1_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCEF1 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCEF1_SetInterruptHandler() method.
    This handler is called every time the IOCEF1 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCEF1_SetInterruptHandler(IOCEF1_InterruptHandler);

*/
extern void (*IOCEF1_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCEF1 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCEF1_SetInterruptHandler() method.
    This handler is called every time the IOCEF1 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCEF1_SetInterruptHandler(IOCEF1_DefaultInterruptHandler);

*/
void IOCEF1_DefaultInterruptHandler(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/