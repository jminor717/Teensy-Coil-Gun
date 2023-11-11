/*
 * File:   HT16K33_driver.c
 * Author: jacob
 *
 * Created on February 3, 2023, 5:26 PM
 */


#include <xc.h>
#include "HT16K33_driver.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"

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

void HT16K33_sendCMD(uint8_t cmd)
{
    // if (_cache && (_displayCache[pos] == mask))
    //     return;
    uint8_t data_[1] = { cmd };
    I2C1_WriteNBytes(0x70, data_, 1);
    // _displayCache[pos] = _cache ? mask : HT16K33_NONE;
}

bool HT16K33_DisplayInt(int16_t n)
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

bool HT16K33_DisplayIntBinary(uint8_t n)
{
    bool inRange = ((0 < n) && (n < 0b1111));

    writePos(0, charmap[n & 0b1], false);
    writePos(1, charmap[(n >> 1) & 0b1], false);
    writePosNP(2, 1);
    writePos(3, charmap[(n >> 2) & 0b1], false);
    writePos(4, charmap[(n >> 3) & 0b1], false);
    return inRange;
}