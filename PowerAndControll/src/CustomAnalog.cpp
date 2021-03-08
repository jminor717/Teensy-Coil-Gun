#include "CustomAnalog.hpp"
#include "analog.c"
#include "Arduino.h"

int analogReadPerADC(uint8_t pin, uint8_t ADC)
{
    //if (ADC == ADC_2) //&& pin >= 14
    //    pin -= 14;
    if (pin > sizeof(pin_to_channel))
        return 0;
    if (calibrating)
        wait_for_cal();
    uint8_t ch = pin_to_channel[pin];
    if (ch == 255)
        return 0;
    //	printf("%d\n", ch);
    //	if (ch > 15) return 0;
    if (ADC == ADC_1)
    {
        ADC1_HC0 = ch;
        while (!(ADC1_HS & ADC_HS_COCO0))
            ; // wait
        return ADC1_R0;
    }
    else
    {
        ADC2_HC0 = ch & 0x7f;
        while (!(ADC2_HS & ADC_HS_COCO0))
            ; // wait
        return ADC2_R0;
    }
}

void analogReadResPerADC(unsigned int bits, uint8_t ADC)
{
    uint32_t tmp32, mode;

    if (bits == 8)
    {
        // 8 bit conversion (17 clocks) plus 8 clocks for input settling
        mode = ADC_CFG_MODE(0) | ADC_CFG_ADSTS(3);
    }
    else if (bits == 10)
    {
        // 10 bit conversion (17 clocks) plus 20 clocks for input settling
        mode = ADC_CFG_MODE(1) | ADC_CFG_ADSTS(2) | ADC_CFG_ADLSMP;
    }
    else
    {
        // 12 bit conversion (25 clocks) plus 24 clocks for input settling
        mode = ADC_CFG_MODE(2) | ADC_CFG_ADSTS(3) | ADC_CFG_ADLSMP;
    }
    if (ADC == ADC_1)
    {
        tmp32 = (ADC1_CFG & (0xFFFFFC00));
        tmp32 |= (ADC1_CFG & (0x03)); // ADICLK
        tmp32 |= (ADC1_CFG & (0xE0)); // ADIV & ADLPC

        tmp32 |= mode;
        ADC1_CFG = tmp32;
    }
    else
    {
        tmp32 = (ADC2_CFG & (0xFFFFFC00));
        tmp32 |= (ADC2_CFG & (0x03)); // ADICLK
        tmp32 |= (ADC2_CFG & (0xE0)); // ADIV & ADLPC

        tmp32 |= mode;
        ADC2_CFG = tmp32;
    }
}