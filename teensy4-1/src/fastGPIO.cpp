#include <core_pins.h>
/*
#define coilH1 24
#define coilH2 25
#define coilH3 26
#define coilH4 27
#define coilH5 28
#define coilH6 29
#define coilH7 30
#define coilH8 31
#define coilH9 32
#define coilH10 33
#define coilH11 34
#define coilH12 35
#define coilH13 36

#define coilL1 37
#define coilL2 38
#define coilL3 39
#define coilL4 40
#define coilL5 41
#define coilL6 14
#define coilL7 15
#define coilL8 16
#define coilL9 17
#define coilL10 18
#define coilL11 19
#define coilL12 20
#define coilL13 21

void coil1H(int val)
{
    if (val)//this notation requires that the pin number be defined at compile time and is faster than if it were defined later
        *portSetRegister(coilH1) = digitalPinToBitMask(coilH1);
    else
        *portClearRegister(coilH1) = digitalPinToBitMask(coilH1);
}
void coil2H(int val)
{
    if (val)
        *portSetRegister(coilH2) = digitalPinToBitMask(coilH2);
    else
        *portClearRegister(coilH2) = digitalPinToBitMask(coilH2);
}
void coil3H(int val)
{
    if (val)
        *portSetRegister(coilH3) = digitalPinToBitMask(coilH3);
    else
        *portClearRegister(coilH3) = digitalPinToBitMask(coilH3);
}
void coil4H(int val)
{
    if (val)
        *portSetRegister(coilH4) = digitalPinToBitMask(coilH4);
    else
        *portClearRegister(coilH4) = digitalPinToBitMask(coilH4);
}
void coil5H(int val)
{
    if (val)
        *portSetRegister(coilH5) = digitalPinToBitMask(coilH5);
    else
        *portClearRegister(coilH5) = digitalPinToBitMask(coilH5);
}
void coil6H(int val)
{
    if (val)
        *portSetRegister(coilH6) = digitalPinToBitMask(coilH6);
    else
        *portClearRegister(coilH6) = digitalPinToBitMask(coilH6);
}
void coil7H(int val)
{
    if (val)
        *portSetRegister(coilH7) = digitalPinToBitMask(coilH7);
    else
        *portClearRegister(coilH7) = digitalPinToBitMask(coilH7);
}
void coil8H(int val)
{
    if (val)
        *portSetRegister(coilH8) = digitalPinToBitMask(coilH8);
    else
        *portClearRegister(coilH8) = digitalPinToBitMask(coilH8);
}
void coil9H(int val)
{
    if (val)
        *portSetRegister(coilH9) = digitalPinToBitMask(coilH9);
    else
        *portClearRegister(coilH9) = digitalPinToBitMask(coilH9);
}
void coil10H(int val)
{
    if (val)
        *portSetRegister(coilH10) = digitalPinToBitMask(coilH10);
    else
        *portClearRegister(coilH10) = digitalPinToBitMask(coilH10);
}
void coil11H(int val)
{
    if (val)
        *portSetRegister(coilH11) = digitalPinToBitMask(coilH11);
    else
        *portClearRegister(coilH11) = digitalPinToBitMask(coilH11);
}
void coil12H(int val)
{
    if (val)
        *portSetRegister(coilH12) = digitalPinToBitMask(coilH12);
    else
        *portClearRegister(coilH12) = digitalPinToBitMask(coilH12);
}
void coil13H(int val)
{
    if (val)
        *portSetRegister(coilH13) = digitalPinToBitMask(coilH13);
    else
        *portClearRegister(coilH13) = digitalPinToBitMask(coilH13);
}




void coil1L(int val)
{
    if (val)
        *portSetRegister(coilL1) = digitalPinToBitMask(coilL1);
    else
        *portClearRegister(coilL1) = digitalPinToBitMask(coilL1);
}
void coil2L(int val)
{
    if (val)
        *portSetRegister(coilL2) = digitalPinToBitMask(coilL2);
    else
        *portClearRegister(coilL2) = digitalPinToBitMask(coilL2);
}
void coil3L(int val)
{
    if (val)
        *portSetRegister(coilL3) = digitalPinToBitMask(coilL3);
    else
        *portClearRegister(coilL3) = digitalPinToBitMask(coilL3);
}
void coil4L(int val)
{
    if (val)
        *portSetRegister(coilL4) = digitalPinToBitMask(coilL4);
    else
        *portClearRegister(coilL4) = digitalPinToBitMask(coilL4);
}
void coil5L(int val)
{
    if (val)
        *portSetRegister(coilL5) = digitalPinToBitMask(coilL5);
    else
        *portClearRegister(coilL5) = digitalPinToBitMask(coilL5);
}
void coil6L(int val)
{
    if (val)
        *portSetRegister(coilL6) = digitalPinToBitMask(coilL6);
    else
        *portClearRegister(coilL6) = digitalPinToBitMask(coilL6);
}
void coil7L(int val)
{
    if (val)
        *portSetRegister(coilL7) = digitalPinToBitMask(coilL7);
    else
        *portClearRegister(coilL7) = digitalPinToBitMask(coilL7);
}
void coil8L(int val)
{
    if (val)
        *portSetRegister(coilL8) = digitalPinToBitMask(coilL8);
    else
        *portClearRegister(coilL8) = digitalPinToBitMask(coilL8);
}
void coil9L(int val)
{
    if (val)
        *portSetRegister(coilL9) = digitalPinToBitMask(coilL9);
    else
        *portClearRegister(coilL9) = digitalPinToBitMask(coilL9);
}
void coil10L(int val)
{
    if (val)
        *portSetRegister(coilL10) = digitalPinToBitMask(coilL10);
    else
        *portClearRegister(coilL10) = digitalPinToBitMask(coilL10);
}
void coil11L(int val)
{
    if (val)
        *portSetRegister(coilL11) = digitalPinToBitMask(coilL11);
    else
        *portClearRegister(coilL11) = digitalPinToBitMask(coilL11);
}
void coil12L(int val)
{
    if (val)
        *portSetRegister(coilL12) = digitalPinToBitMask(coilL12);
    else
        *portClearRegister(coilL12) = digitalPinToBitMask(coilL12);
}
void coil13L(int val)
{
    if (val)
        *portSetRegister(coilL13) = digitalPinToBitMask(coilL13);
    else
        *portClearRegister(coilL13) = digitalPinToBitMask(coilL13);
}
*/