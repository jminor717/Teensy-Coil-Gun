//Gun controll

#include <Arduino.h>
#include <atomic>
#include <queue>
#include <deque>
//#include "QuickCompBoolList.hpp"
//#include <fastGPIO.hpp>

//#define TestElectrical

#define FORCE_INLINE __attribute__((always_inline)) inline

//FREE 23

#define UnusedPin 23

#define opto1 0
#define opto2 1
#define opto3 2
#define opto4 3
#define opto5 4
#define opto6 5
#define opto7 6
// #define opto8 7
// #define opto9 8
// #define opto10 9
// #define opto11 10
// #define opto12 11
// #define opto13 12
// #define opto14 24
// #define opto15 25
// #define opto16 26
// #define opto17 27
// #define opto18 28
// #define opto19 29

#define coil1L 7
#define coil1H 8
#define coil2L 9
#define coil2H 10
#define coil3L 11
#define coil3H 12
#define coil4L 24
#define coil4H 25
#define coil5L 26
#define coil5H 27
#define coil6L 28
#define coil6H 29

// #define coil1 30
// #define coil2 31
// #define coil3 32
// #define coil4 33
// #define coil5 34
// #define coil6 35
// #define coil7 36
// #define coil8 37
// #define coil9 38
// #define coil10 39
// #define coil11 40
// #define coil12 41
// #define coil13 14
// #define coil14 15
// #define coil15 16
// #define coil16 17
// #define coil17 18
// #define coil18 19
// #define coil19 20

#define inputSwitch 21
#define BuckEnable 13
#define StableStateReachedPin 22

#define ProjectileLength 2
#define DebounceQueSize 3
#define FireSettleLimit 50

IntervalTimer myTimer;

std::atomic<bool> running(false);
std::atomic<bool> ending(false);
std::atomic<bool> StopAll(false);

int tim = 6 * 1000; // 6 miliseconds worth of microsecons
std::atomic<bool> FireTriggered(false);

template <size_t MaxLen>
class QuickCompBoolList
{
private:
    size_t position = 0;
    uint32_t comp = 0;

public:
    uint32_t data = 0;
    QuickCompBoolList()
    { //create a int with the number of 1's expected by isAllTrue
        for (size_t i = 0; i < MaxLen; i++)
        {
            comp = comp | (1UL << i);
        }
    }
    void push(const bool &value)
    {
        if (position >= MaxLen)
        {
            position = 0;
        }
        data ^= (-value ^ data) & (1UL << position);
        position++;
    }
    bool isAllTrue() { return data == comp; }
    bool isAllFalse() { return data == 0UL; }
};

void Fire();
void FireInterrupt();

elapsedMicros timeOutNow;
QuickCompBoolList<DebounceQueSize> DebounceQue;

static inline void Sequence(uint8_t opt1, uint8_t opt2, uint8_t ON1, uint8_t ON2, uint8_t OFF1, uint8_t OFF2) __attribute__((always_inline, unused));
static inline void Sequence(uint8_t opt1, uint8_t opt2, uint8_t ON1, uint8_t ON2, uint8_t OFF1, uint8_t OFF2)
{
    if (StopAll)
        return;
#ifdef TestElectrical
    delay(1);
#else
    //myTimer.begin(timout, tim);
    uint8_t x = 0, y = 0;
    if (__builtin_constant_p(opt1))
    {
        if (opt1 != UnusedPin)
        {
            x = digitalReadFast(opt1);
        }
    }
    if (__builtin_constant_p(opt2))
    {
        if (opt2 != UnusedPin)
        {
            y = digitalReadFast(opt2);
        }
    }

    unsigned long end = timeOutNow + tim;
    while (!(x || y || (timeOutNow < end)))
    {
        if (__builtin_constant_p(opt1))
        {
            if (opt1 != UnusedPin)
            {
                x = digitalReadFast(opt1);
            }
        }
        if (__builtin_constant_p(opt2))
        {
            if (opt2 != UnusedPin)
            {
                y = digitalReadFast(opt2);
            }
        }
    }
    if ((timeOutNow < end))
    {
        StopAll = true;
        return;
    }
#endif
    if (__builtin_constant_p(ON1))
    {
        if (ON1 != UnusedPin)
        {
            digitalWriteFast(ON1, HIGH);
        }
    }
    if (__builtin_constant_p(ON2))
    {
        if (ON2 != UnusedPin)
        {
            digitalWriteFast(ON2, HIGH);
        }
    }
    if (__builtin_constant_p(OFF1))
    {
        if (OFF1 != UnusedPin)
        {
            digitalWriteFast(OFF1, LOW);
        }
    }
    if (__builtin_constant_p(OFF2))
    {
        if (OFF2 != UnusedPin)
        {
            digitalWriteFast(OFF2, LOW);
        }
    }
}

void timout()
{
    StopAll = true;
    myTimer.end();
    ending = true;
    running = true; //this should be true anyways but set it here to make sure

    digitalWriteFast(coil6L, LOW);
    digitalWriteFast(coil6H, LOW);
    digitalWriteFast(coil5L, LOW);
    digitalWriteFast(coil5H, LOW);
    digitalWriteFast(coil4L, LOW);
    digitalWriteFast(coil4H, LOW);
    digitalWriteFast(coil3L, LOW);
    digitalWriteFast(coil3H, LOW);
    digitalWriteFast(coil2L, LOW);
    digitalWriteFast(coil2H, LOW);
    digitalWriteFast(coil1L, LOW);
    digitalWriteFast(coil1H, LOW);

    digitalWriteFast(BuckEnable, LOW);

    running = false;
    Serial.println("timeout");
    delay(200); //allow time for everything to reach a steady state

    //and turn on the low side transistors so that the highside bootstrap capacitor can charge
    digitalWriteFast(coil1L, HIGH);
    digitalWriteFast(coil2L, HIGH);
    digitalWriteFast(coil3L, HIGH);
    digitalWriteFast(coil4L, HIGH);
    digitalWriteFast(coil5L, HIGH);
    digitalWriteFast(coil6L, HIGH);

    delay(1000);

    digitalWriteFast(StableStateReachedPin, HIGH);
    ending = false;
    attachInterrupt(digitalPinToInterrupt(inputSwitch), FireInterrupt, RISING);
}

void FireInterrupt()
{
    detachInterrupt(digitalPinToInterrupt(inputSwitch));
    uint8_t projectilePresent = 0;
    uint16_t FireSettleCount = 0;
    if (!(running || ending))
    {
        while (1)
        {
            projectilePresent = digitalReadFast(opto1);
            DebounceQue.push(digitalReadFast(inputSwitch));
            FireSettleCount++;
            if (DebounceQue.isAllTrue())
            {
                FireSettleCount = 0;
                Fire();
                break;
            }
            if (FireSettleCount > FireSettleLimit) //allow FireSettleLimit number of cycles before aborting the fire sequence
            {
                FireSettleCount = 0;
                attachInterrupt(digitalPinToInterrupt(inputSwitch), FireInterrupt, RISING);
                break;
            }
        }
    }
}

void Fire()
{
    running = true;
    StopAll = false;
    digitalWriteFast(StableStateReachedPin, LOW); // tell power controll that we are in the fiering process
    Serial.println("fire");

    digitalWriteFast(BuckEnable, HIGH); // tell power controll that we are ready to receive power
    digitalWriteFast(coil1H, HIGH);
    digitalWriteFast(coil2H, HIGH);

    Sequence(opto2, opto3, coil3L, coil3H, UnusedPin, UnusedPin);
    Sequence(opto3, opto4, coil4L, coil4H, coil1L, coil1H);
    Sequence(opto4, opto5, coil5L, coil5H, coil2L, coil2H);
    Sequence(opto5, opto6, coil6L, coil6H, coil3L, coil3H);
    Sequence(opto6, opto7, UnusedPin, UnusedPin, coil3L, coil3H);
    digitalWriteFast(BuckEnable, LOW); // stop the buck converter before the last coil is turned off
                                       // this will bleed off any energy remaining in the inductor
    Sequence(opto7, UnusedPin, UnusedPin, UnusedPin, coil4L, coil4H);

    digitalWriteFast(coil6L, LOW);
    digitalWriteFast(coil6H, LOW);
    digitalWriteFast(coil5L, LOW);
    digitalWriteFast(coil5H, LOW);

    timout();

    // Sequence1(opto2, opto3, coil3);
    // Sequence(opto3, opto4, coil4, coil1);
    // Sequence(opto4, opto5, coil5, coil2);
    // Sequence(opto5, opto6, coil6, coil3);
    // Sequence(opto6, opto7, coil7, coil4);
    // Sequence(opto7, opto8, coil8, coil5);
    // Sequence(opto8, opto9, coil9, coil6);
    // Sequence(opto9, opto10, coil10, coil7);
    // Sequence(opto10, opto11, coil11, coil8);
    // Sequence(opto11, opto12, coil12, coil9);
    // Sequence(opto12, opto13, coil13, coil10);
    // Sequence(opto13, opto14, coil14, coil11);
    // Sequence(opto14, opto15, coil15, coil12);
    // Sequence(opto15, opto16, coil16, coil13);
    // Sequence(opto16, opto17, coil17, coil14);
    // Sequence(opto17, opto18, coil18, coil15);
    // Sequence(opto18, opto19, coil19, coil16);
    // Sequence(opto19, coil17);

    // digitalWriteFast(coil18, LOW);
    // digitalWriteFast(coil18, LOW);
}

#undef main

int main()
{
    pinMode(BuckEnable, OUTPUT);
    pinMode(StableStateReachedPin, OUTPUT);

    // pinMode(coil1, OUTPUT);
    // pinMode(coil2, OUTPUT);
    // pinMode(coil3, OUTPUT);
    // pinMode(coil4, OUTPUT);
    // pinMode(coil5, OUTPUT);
    // pinMode(coil6, OUTPUT);
    // pinMode(coil7, OUTPUT);
    // pinMode(coil8, OUTPUT);
    // pinMode(coil9, OUTPUT);
    // pinMode(coil10, OUTPUT);
    // pinMode(coil11, OUTPUT);
    // pinMode(coil12, OUTPUT);
    // pinMode(coil13, OUTPUT);
    // pinMode(coil14, OUTPUT);
    // pinMode(coil15, OUTPUT);
    // pinMode(coil16, OUTPUT);
    // pinMode(coil17, OUTPUT);
    // pinMode(coil18, OUTPUT);
    // pinMode(coil19, OUTPUT);

    // digitalWrite(coil1, LOW);
    // digitalWrite(coil2, LOW);
    // digitalWrite(coil3, LOW);
    // digitalWrite(coil4, LOW);
    // digitalWrite(coil5, LOW);
    // digitalWrite(coil6, LOW);
    // digitalWrite(coil7, LOW);
    // digitalWrite(coil8, LOW);
    // digitalWrite(coil9, LOW);
    // digitalWrite(coil10, LOW);
    // digitalWrite(coil11, LOW);
    // digitalWrite(coil12, LOW);
    // digitalWrite(coil13, LOW);
    // digitalWrite(coil14, LOW);
    // digitalWrite(coil15, LOW);
    // digitalWrite(coil16, LOW);
    // digitalWrite(coil17, LOW);
    // digitalWrite(coil18, LOW);
    // digitalWrite(coil19, LOW);

    pinMode(coil1L, OUTPUT);
    pinMode(coil1H, OUTPUT);
    pinMode(coil2L, OUTPUT);
    pinMode(coil2H, OUTPUT);
    pinMode(coil3L, OUTPUT);
    pinMode(coil3H, OUTPUT);
    pinMode(coil4L, OUTPUT);
    pinMode(coil4H, OUTPUT);
    pinMode(coil5L, OUTPUT);
    pinMode(coil5H, OUTPUT);
    pinMode(coil6L, OUTPUT);
    pinMode(coil6H, OUTPUT);

    delay(1);

    digitalWriteFast(coil1L, LOW);
    digitalWriteFast(coil1H, LOW);
    digitalWriteFast(coil2L, LOW);
    digitalWriteFast(coil2H, LOW);
    digitalWriteFast(coil3L, LOW);
    digitalWriteFast(coil3H, LOW);
    digitalWriteFast(coil4L, LOW);
    digitalWriteFast(coil4H, LOW);
    digitalWriteFast(coil5L, LOW);
    digitalWriteFast(coil5H, LOW);
    digitalWriteFast(coil6L, LOW);
    digitalWriteFast(coil6H, LOW);

    delay(50);
    //turn on the low side drive to keep the high side drive bootsrap cap charged
    digitalWriteFast(coil1L, HIGH);
    digitalWriteFast(coil2L, HIGH);
    digitalWriteFast(coil3L, HIGH);
    digitalWriteFast(coil4L, HIGH);
    digitalWriteFast(coil5L, HIGH);
    digitalWriteFast(coil6L, HIGH);

    pinMode(inputSwitch, INPUT_PULLDOWN);

    pinMode(opto1, INPUT_PULLUP);
    pinMode(opto2, INPUT_PULLUP);
    pinMode(opto3, INPUT_PULLUP);
    pinMode(opto4, INPUT_PULLUP);
    pinMode(opto5, INPUT_PULLUP);
    pinMode(opto6, INPUT_PULLUP);
    pinMode(opto7, INPUT_PULLUP);
    // pinMode(opto8, INPUT_PULLUP);
    // pinMode(opto9, INPUT_PULLUP);
    // pinMode(opto10, INPUT_PULLUP);
    // pinMode(opto11, INPUT_PULLUP);
    // pinMode(opto12, INPUT_PULLUP);
    // pinMode(opto13, INPUT_PULLUP);
    // pinMode(opto14, INPUT_PULLUP);
    // pinMode(opto15, INPUT_PULLUP);
    // pinMode(opto16, INPUT_PULLUP);
    // pinMode(opto17, INPUT_PULLUP);
    // pinMode(opto18, INPUT_PULLUP);
    // pinMode(opto19, INPUT_PULLUP);

    Serial.begin(9600);
    Serial.println("begining");
    myTimer.begin(timout, tim);
    //attachInterrupt(digitalPinToInterrupt(inputSwitch), FireInterrupt, RISING);
}