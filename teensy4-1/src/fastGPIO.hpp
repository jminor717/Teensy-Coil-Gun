#define coil1Hon() (*(&CORE_PIN24_PORTREG + 0x21) = CORE_PIN24_BITMASK)  //gpio register bit flips to improve exicution speed
#define coil1Hoff() (*(&CORE_PIN24_PORTREG + 0x22) = CORE_PIN24_BITMASK) //decrease gpio write time from 43ns to 3.6ns at cost of complexity
#define coil2Hon() (*(&CORE_PIN25_PORTREG + 0x21) = CORE_PIN25_BITMASK)
#define coil2Hoff() (*(&CORE_PIN25_PORTREG + 0x22) = CORE_PIN25_BITMASK)
#define coil3Hon() (*(&CORE_PIN26_PORTREG + 0x21) = CORE_PIN26_BITMASK)
#define coil3Hoff() (*(&CORE_PIN26_PORTREG + 0x22) = CORE_PIN26_BITMASK)
#define coil4Hon() (*(&CORE_PIN27_PORTREG + 0x21) = CORE_PIN27_BITMASK)
#define coil4Hoff() (*(&CORE_PIN27_PORTREG + 0x22) = CORE_PIN27_BITMASK)
#define coil5Hon() (*(&CORE_PIN28_PORTREG + 0x21) = CORE_PIN28_BITMASK)
#define coil5Hoff() (*(&CORE_PIN28_PORTREG + 0x22) = CORE_PIN28_BITMASK)
#define coil6Hon() (*(&CORE_PIN29_PORTREG + 0x21) = CORE_PIN29_BITMASK)
#define coil6Hoff() (*(&CORE_PIN29_PORTREG + 0x22) = CORE_PIN29_BITMASK)
#define coil7Hon() (*(&CORE_PIN30_PORTREG + 0x21) = CORE_PIN30_BITMASK)
#define coil7Hoff() (*(&CORE_PIN30_PORTREG + 0x22) = CORE_PIN30_BITMASK)
#define coil8Hon() (*(&CORE_PIN31_PORTREG + 0x21) = CORE_PIN31_BITMASK)
#define coil8Hoff() (*(&CORE_PIN31_PORTREG + 0x22) = CORE_PIN31_BITMASK)
#define coil9Hon() (*(&CORE_PIN32_PORTREG + 0x21) = CORE_PIN32_BITMASK)
#define coil9Hoff() (*(&CORE_PIN32_PORTREG + 0x22) = CORE_PIN32_BITMASK)
#define coil10Hon() (*(&CORE_PIN33_PORTREG + 0x21) = CORE_PIN33_BITMASK)
#define coil10Hoff() (*(&CORE_PIN33_PORTREG + 0x22) = CORE_PIN33_BITMASK)
#define coil11Hon() (*(&CORE_PIN34_PORTREG + 0x21) = CORE_PIN34_BITMASK)
#define coil11Hoff() (*(&CORE_PIN34_PORTREG + 0x22) = CORE_PIN34_BITMASK)
#define coil12Hon() (*(&CORE_PIN35_PORTREG + 0x21) = CORE_PIN35_BITMASK)
#define coil12Hoff() (*(&CORE_PIN35_PORTREG + 0x22) = CORE_PIN35_BITMASK)
#define coil13Hon() (*(&CORE_PIN36_PORTREG + 0x21) = CORE_PIN36_BITMASK)
#define coil13Hoff() (*(&CORE_PIN36_PORTREG + 0x22) = CORE_PIN36_BITMASK)


#define coil1Lon() (*(&CORE_PIN37_PORTREG + 0x21) = CORE_PIN37_BITMASK)
#define coil1Loff() (*(&CORE_PIN37_PORTREG + 0x22) = CORE_PIN37_BITMASK)
#define coil2Lon() (*(&CORE_PIN38_PORTREG + 0x21) = CORE_PIN38_BITMASK)
#define coil2Loff() (*(&CORE_PIN38_PORTREG + 0x22) = CORE_PIN38_BITMASK)
#define coil3Lon() (*(&CORE_PIN39_PORTREG + 0x21) = CORE_PIN39_BITMASK)
#define coil3Loff() (*(&CORE_PIN39_PORTREG + 0x22) = CORE_PIN39_BITMASK)
#define coil4Lon() (*(&CORE_PIN40_PORTREG + 0x21) = CORE_PIN40_BITMASK)
#define coil4Loff() (*(&CORE_PIN40_PORTREG + 0x22) = CORE_PIN40_BITMASK)
#define coil5Lon() (*(&CORE_PIN41_PORTREG + 0x21) = CORE_PIN41_BITMASK)
#define coil5Loff() (*(&CORE_PIN41_PORTREG + 0x22) = CORE_PIN41_BITMASK)
#define coil6Lon() (*(&CORE_PIN14_PORTREG + 0x21) = CORE_PIN14_BITMASK)
#define coil6Loff() (*(&CORE_PIN14_PORTREG + 0x22) = CORE_PIN14_BITMASK)
#define coil7Lon() (*(&CORE_PIN15_PORTREG + 0x21) = CORE_PIN15_BITMASK)
#define coil7Loff() (*(&CORE_PIN15_PORTREG + 0x22) = CORE_PIN15_BITMASK)
#define coil8Lon() (*(&CORE_PIN16_PORTREG + 0x21) = CORE_PIN16_BITMASK)
#define coil8Loff() (*(&CORE_PIN16_PORTREG + 0x22) = CORE_PIN16_BITMASK)
#define coil9Lon() (*(&CORE_PIN17_PORTREG + 0x21) = CORE_PIN17_BITMASK)
#define coil9Loff() (*(&CORE_PIN17_PORTREG + 0x22) = CORE_PIN17_BITMASK)
#define coil10Lon() (*(&CORE_PIN18_PORTREG + 0x21) = CORE_PIN18_BITMASK)
#define coil10Loff() (*(&CORE_PIN18_PORTREG + 0x22) = CORE_PIN18_BITMASK)
#define coil11Lon() (*(&CORE_PIN19_PORTREG + 0x21) = CORE_PIN19_BITMASK)
#define coil11Loff() (*(&CORE_PIN19_PORTREG + 0x22) = CORE_PIN19_BITMASK)
#define coil12Lon() (*(&CORE_PIN20_PORTREG + 0x21) = CORE_PIN20_BITMASK)
#define coil12Loff() (*(&CORE_PIN20_PORTREG + 0x22) = CORE_PIN20_BITMASK)
#define coil13Lon() (*(&CORE_PIN21_PORTREG + 0x21) = CORE_PIN21_BITMASK)
#define coil13Loff() (*(&CORE_PIN21_PORTREG + 0x22) = CORE_PIN21_BITMASK)

void coil1H(int val);
void coil2H(int val);
void coil3H(int val);
void coil4H(int val);
void coil5H(int val);
void coil6H(int val);
void coil7H(int val);
void coil8H(int val);
void coil9H(int val);
void coil10H(int val);
void coil11H(int val);
void coil12H(int val);
void coil13H(int val);

void coil1L(int val);
void coil2L(int val);
void coil3L(int val);
void coil4L(int val);
void coil5L(int val);
void coil6L(int val);
void coil7L(int val);
void coil8L(int val);
void coil9L(int val);
void coil10L(int val);
void coil11L(int val);
void coil12L(int val);
void coil13L(int val);