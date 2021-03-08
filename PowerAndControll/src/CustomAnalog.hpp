#include "imxrt.h"
#include "core_pins.h"
#include "debug/printf.h"
#include "avr/pgmspace.h"

#define ADC_1 1
#define ADC_2 2

void analogReadResPerADC(unsigned int, uint8_t);
int analogReadPerADC(uint8_t, uint8_t);