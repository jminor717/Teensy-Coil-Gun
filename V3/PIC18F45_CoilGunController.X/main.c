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

#include "mcc_generated_files/examples/i2c1_master_example.h"
#include "mcc_generated_files/mcc.h"

//  Commands
#define HT16K33_ON 0x21 //  0=off 1=on
#define HT16K33_STANDBY 0x20 //  bit xxxxxxx0

//  bit pattern 1000 0xxy
//  y    =  display on / off
//  xx   =  00=off     01=2Hz     10=1Hz     11=0.5Hz
#define HT16K33_DISPLAYON 0x81
#define HT16K33_DISPLAYOFF 0x80
#define HT16K33_BLINKON0_5HZ 0x87
#define HT16K33_BLINKON1HZ 0x85
#define HT16K33_BLINKON2HZ 0x83
#define HT16K33_BLINKOFF 0x81

//  bit pattern 1110 xxxx
//  xxxx    =  0000 .. 1111 (0 - F)
#define HT16K33_BRIGHTNESS 0xE0

static const uint8_t charmap[] = {
    //  TODO PROGMEM ?
    0x3F, //  0
    0x06, //  1
    0x5B, //  2
    0x4F, //  3
    0x66, //  4
    0x6D, //  5
    0x7D, //  6
    0x07, //  7
    0x7F, //  8
    0x6F, //  9
    0x77, //  A
    0x7C, //  B
    0x39, //  C
    0x5E, //  D
    0x79, //  E
    0x71, //  F
    0x00, //  space
    0x40, //  minus
    0x61, //  TOP_C
    0x63, //  degree �
};

#define HT16K33_SPACE 16
#define HT16K33_MINUS 17
#define HT16K33_TOP_C 18 //  c
#define HT16K33_DEGREE 19 //  °
#define HT16K33_NONE 99

uint8_t CurrentCountdown = 0;

/* IOC initialization function */
static void IOC_Initialize(void)
{
    // Enable IOCI interrupt
    PIE0bits.IOCIE = 1;
    // Enabling TMR6 interrupt.
    PIE4bits.TMR6IE = 1;
}

/* IOC ISR function */
static void Local_IOCCF4_ISR(void)
{
    CurrentCountdown += 1;
    TMR6_StartTimer();
    //    PORTD |= 0b00000100;
    //    RD2 = ~RD2; // LED OFF
    //    PORTD &= 0b11111011;
}

void INTERRUPT_Initialize(void)
{
    // Disable Interrupt Priority Vectors (16CXXX Compatibility Mode)
    INTCONbits.IPEN = 0;
    INTCONbits.GIE = 1; /* Enable global interrupts */
    INTCONbits.PEIE = 1;
}
extern volatile uint8_t IOCEFbits_Data __at(0xF22);
extern volatile uint8_t IOCCFbits_Data __at(0xF15);
extern volatile uint8_t IOCBFbits_Data __at(0xF0D);
extern volatile uint8_t IOCAFbits_Data __at(0xF05);

void __interrupt() INTERRUPT_InterruptManager(void)
{
    if (IOCAFbits_Data != 0) { // && (bits && !(bits & (bits-1)))
        if (IOCAFbits_Data && !(IOCAFbits_Data & (IOCAFbits_Data - 1))) {
            switch (IOCAFbits_Data) {
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
        }

        if (IOCAFbits.IOCAF0 == 1) { // interrupt on change for pin IOCAF0
            IOCAFbits.IOCAF0 = 0;
        }
        if (IOCAFbits.IOCAF1 == 1) { // interrupt on change for pin IOCAF1
            IOCAFbits.IOCAF1 = 0;
        }
        if (IOCAFbits.IOCAF2 == 1) { // interrupt on change for pin IOCAF2
            IOCAFbits.IOCAF2 = 0;
        }
        if (IOCAFbits.IOCAF3 == 1) { // interrupt on change for pin IOCAF3
            IOCAFbits.IOCAF3 = 0;
        }
        if (IOCAFbits.IOCAF4 == 1) { // interrupt on change for pin IOCAF4
            IOCAFbits.IOCAF4 = 0;
        }
        if (IOCAFbits.IOCAF5 == 1) { // interrupt on change for pin IOCAF5
            IOCAFbits.IOCAF5 = 0;
            // IOCBF5_ISR();
        }
        IOCAFbits_Data = 0;
    }

    if (IOCEFbits_Data) { //&& (bits && !(bits & (bits-1)))
        if (IOCEFbits_Data && !(IOCEFbits_Data & (IOCEFbits_Data - 1))) {
            switch (IOCEFbits_Data) {
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
        }

        if (IOCEFbits.IOCEF0 == 1) { // interrupt on change for pin IOCCF0
            IOCEFbits.IOCEF0 = 0;
        }
        if (IOCEFbits.IOCEF1 == 1) { // interrupt on change for pin IOCCF1
            IOCEFbits.IOCEF1 = 0;
        }
        if (IOCEFbits.IOCEF2 == 1) { // interrupt on change for pin IOCCF2
            IOCEFbits.IOCEF2 = 0;
        }
        IOCEFbits_Data = 0;
    }

    if (IOCCFbits_Data) { //  && (bits && !(bits & (bits-1)))
        if (IOCCFbits_Data && !(IOCCFbits_Data & (IOCCFbits_Data - 1))) { // why no work?
            switch (IOCCFbits_Data) {
            case 0b1:
                IOCCFbits.IOCCF0 = 0;
                return;
            case 0b1 << 1:
                IOCCFbits.IOCCF1 = 0;
                Local_IOCCF4_ISR();
                return;
            case 0b1 << 2:
                IOCCFbits.IOCCF2 = 0;
                return;
            default:
                break;
            }
        }

        if (IOCCFbits.IOCCF0 == 1) { // interrupt on change for pin IOCCF0
            IOCCFbits.IOCCF0 = 0;
        }
        if (IOCCFbits.IOCCF1 == 1) { // interrupt on change for pin IOCCF1
            IOCCFbits.IOCCF1 = 0;
            Local_IOCCF4_ISR();
        }
        if (IOCCFbits.IOCCF2 == 1) { // interrupt on change for pin IOCCF1
            IOCCFbits.IOCCF2 = 0;
        }
        if (IOCCFbits.IOCCF3 == 1) { // interrupt on change for pin IOCCF1
            IOCCFbits.IOCCF3 = 0;
        }
        IOCCFbits_Data = 0;
    }

    if (PIE4bits.TMR6IE == 1 && PIR4bits.TMR6IF == 1) {
        // clear the TMR6 interrupt flag
        PIR4bits.TMR6IF = 0;
        if (CurrentCountdown > 0) {
            CurrentCountdown--;
            TMR6_StartTimer();
        } else {
            RD2 = ~RD2; // LED OFF
        }
    }
}

void writePosNP(uint8_t pos, uint8_t mask)
{
    // if (_cache && (_displayCache[pos] == mask))
    //     return;
    uint8_t data_[2] = { pos * 2, mask };
    I2C1_WriteNBytes(0x70, data_, 2);
    // _displayCache[pos] = _cache ? mask : HT16K33_NONE;
}

void writePos(uint8_t pos, uint8_t mask, bool point)
{
    if (point)
        mask |= 0x80;
    //  if (_overflow) mask |= 0x80;
    else
        mask &= 0x7F;
    writePosNP(pos, mask);
}

void sendCMD(uint8_t cmd)
{
    // if (_cache && (_displayCache[pos] == mask))
    //     return;
    uint8_t data_[1] = { cmd };
    I2C1_WriteNBytes(0x70, data_, 1);
    // _displayCache[pos] = _cache ? mask : HT16K33_NONE;
}

bool displayInt(int16_t n)
{
    bool inRange = ((-1000 < n) && (n < 10000));
    uint8_t x[4], h, l;
    bool neg = (n < 0);
    if (neg)
        n = -n;
    h = (uint8_t)(n / 100);
    l = (uint8_t)(n - h * 100);
    x[0] = h / 10;
    x[1] = h - x[0] * 10;
    x[2] = l / 10;
    x[3] = l - x[2] * 10;

    if (neg) {
        x[0] = HT16K33_MINUS;
        // if (_digits >= 3) {
        //     x[0] = HT16K33_MINUS;
        // } else {
        //     int i = 0;
        //     for (i = 0; i < (4 - _digits); i++) {
        //         if (x[i] != 0)
        //             break;
        //         x[i] = HT16K33_SPACE;
        //     }
        //     x[i - 1] = HT16K33_MINUS;
        // }
    }
    writePos(0, charmap[x[0]], false);
    writePos(1, charmap[x[1]], false);
    writePosNP(2, 1);
    writePos(3, charmap[x[2]], false);
    writePos(4, charmap[x[3]], false);
    return inRange;
}

int16_t interruptCounter = 0;

/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    IOC_Initialize();
    INTERRUPT_Initialize();

    sendCMD(HT16K33_ON);
    sendCMD(HT16K33_DISPLAYON);
    sendCMD(HT16K33_BRIGHTNESS | 0);


    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    //    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    // INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    //    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    // INTERRUPT_PeripheralInterruptDisable();

    displayInt(0000);
    while (1) {
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
        __delay_ms(50); // 1 Second Delay
        PORTD |= 0b00000010;
        //        RD2= 1;  // LED ON
        //        RD1= 1;  // LED ON
        __delay_ms(50); // 1 Second Delay
        interruptCounter++;
        if (interruptCounter > 9998)
            interruptCounter = 0;
        displayInt(interruptCounter);
    }
}
/**
 End of File
*/