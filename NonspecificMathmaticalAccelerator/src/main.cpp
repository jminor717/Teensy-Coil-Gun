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

#define opto1 0
#define coil1 1
#define opto2 2
#define coil2 3
#define opto3 4
#define coil3 5
#define opto4 6
#define coil4 7
#define opto5 8
#define coil5 9
#define opto6 10
#define coil6 11
#define opto7 12
#define coil7 24
#define opto8 25
#define coil8 26
#define opto9 27
#define coil9 28
#define opto10 29
#define coil10 30
#define opto11 31
#define coil11 32
#define opto12 33
#define coil12 34
#define opto13 35
#define coil13 36
#define opto14 37
#define coil14 38
#define opto15 39
#define coil15 40
#define opto16 14
#define coil16 15
#define opto17 16
#define coil17 17
#define opto18 18
#define coil18 19
#define opto19 20
#define coil19 21

#define inputSwitch 41
#define BuckEnable 13
#define StableStateReachedPin 22

#define ProjectileLength 2
#define DebounceQueSize 3
#define FireSettleLimit 50

IntervalTimer myTimer;

std::atomic<bool> running(false);
std::atomic<bool> ending(false);
bool StopAll = false;

int tim = 6 * 1000; // 6 miliseconds
std::atomic<bool> FireTriggered(false);
std::atomic<uint16_t> FireSettleCount(0);

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

QuickCompBoolList<DebounceQueSize> DebounceQue;

void timout()
{
    myTimer.end();
    StopAll = true;
    ending = true;
    running = true; //this should be true anyways but set it here to make sure

    digitalWriteFast(BuckEnable, LOW);
    digitalWriteFast(coil1, LOW);
    digitalWriteFast(coil2, LOW);
    digitalWriteFast(coil3, LOW);
    digitalWriteFast(coil4, LOW);
    digitalWriteFast(coil5, LOW);
    digitalWriteFast(coil6, LOW);
    digitalWriteFast(coil7, LOW);
    digitalWriteFast(coil8, LOW);
    digitalWriteFast(coil9, LOW);
    digitalWriteFast(coil10, LOW);
    digitalWriteFast(coil11, LOW);
    digitalWriteFast(coil12, LOW);
    digitalWriteFast(coil13, LOW);
    digitalWriteFast(coil14, LOW);
    digitalWriteFast(coil15, LOW);
    digitalWriteFast(coil16, LOW);
    digitalWriteFast(coil17, LOW);
    digitalWriteFast(coil18, LOW);
    digitalWriteFast(coil19, LOW);


    running = false;
    Serial.println("timeout");
    delay(200); //allow time for everything to reach a steady state
                //and for the low side transistors to turn on so that the highside bootstrap capacitor can charge

    digitalWriteFast(StableStateReachedPin, HIGH);
    ending = false;

    delay(1000);
    attachInterrupt(digitalPinToInterrupt(inputSwitch), FireInterrupt, RISING);
}

void FireInterrupt()
{
    detachInterrupt(digitalPinToInterrupt(inputSwitch));

    FireSettleCount = 0;
    if (!(running || ending))
    {
        while (1)
        {
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

elapsedMicros timeOutNow;

void Sequence1(uint8_t opt1, uint8_t opt2, uint8_t ON)
{
    if (StopAll)
        return;
#ifdef TestElectrical
    delay(1);
#else
    myTimer.begin(timout, tim);
    uint8_t x = digitalReadFast(opt1);
    uint8_t y = digitalReadFast(opt2);
    unsigned long end = timeOutNow + 5000;
    while (x || y || (timeOutNow < end))
    {
        x = digitalReadFast(opt1);
        y = digitalReadFast(opt2);
    }
#endif
    digitalWriteFast(ON, HIGH);
}

void Sequence(uint8_t opt1, uint8_t opt2, uint8_t ON, uint8_t OFF)
{
    if (StopAll)
        return;
#ifdef TestElectrical
    delay(1);
#else
    myTimer.begin(timout, tim);
    uint8_t x = digitalReadFast(opt1);
    uint8_t y = digitalReadFast(opt2);
    unsigned long end = timeOutNow + 5000;
    while (x || y || (timeOutNow < end))
    {
        x = digitalReadFast(opt1);
        y = digitalReadFast(opt2);
    }
#endif
    digitalWriteFast(ON, HIGH);
    digitalWriteFast(OFF, LOW);
}

void Sequence(uint8_t opt1, uint8_t opt2, uint8_t OFF)
{
    if (StopAll)
        return;
#ifdef TestElectrical
    delay(1);
#else
    myTimer.begin(timout, tim);
    uint8_t x = digitalReadFast(opt1);
    uint8_t y = digitalReadFast(opt2);
    unsigned long end = timeOutNow + 5000;
    while (x || y || (timeOutNow < end))
    {
        x = digitalReadFast(opt1);
        y = digitalReadFast(opt2);
    }
#endif
    digitalWriteFast(OFF, LOW);
}

void Sequence(uint8_t opt1,  uint8_t OFF)
{
    if (StopAll)
        return;
#ifdef TestElectrical
    delay(1);
#else
    myTimer.begin(timout, tim);
    uint8_t x = digitalReadFast(opt1);
    unsigned long end = timeOutNow + 5000;
    while (x || (timeOutNow < end))
    {
        x = digitalReadFast(opt1);
    }
#endif
    digitalWriteFast(OFF, LOW);
}

void Fire()
{
    running = true;
    StopAll = false;
    digitalWriteFast(StableStateReachedPin, LOW); // tell power controll that we are in the fiering process
    Serial.println("fire");

    digitalWriteFast(BuckEnable, HIGH); // tell power controll that we are ready to receive power
    digitalWriteFast(coil1, HIGH);
    digitalWriteFast(coil2, HIGH);

    Sequence1(opto2, opto3, coil3);
    Sequence(opto3, opto4, coil4, coil1);
    Sequence(opto4, opto5, coil5, coil2);
    Sequence(opto5, opto6, coil6, coil3);
    Sequence(opto6, opto7, coil7, coil4);
    Sequence(opto7, opto8, coil8, coil5);
    Sequence(opto8, opto9, coil9, coil6);
    Sequence(opto9, opto10, coil10, coil7);
    Sequence(opto10, opto11, coil11, coil8);
    Sequence(opto11, opto12, coil12, coil9);
    Sequence(opto12, opto13, coil13, coil10);
    Sequence(opto13, opto14, coil14, coil11);
    Sequence(opto14, opto15, coil15, coil12);
    Sequence(opto15, opto16, coil16, coil13);
    Sequence(opto16, opto17, coil17, coil14);
    Sequence(opto17, opto18, coil18, coil15);
    Sequence(opto18, opto19, coil19, coil16);
    Sequence(opto19, coil17);

    digitalWriteFast(coil18, LOW);
    digitalWriteFast(coil18, LOW);
}



#undef main

int main()
{
    pinMode(BuckEnable, OUTPUT);
    pinMode(StableStateReachedPin, OUTPUT);

    pinMode(coil1, OUTPUT);
    pinMode(coil2, OUTPUT);
    pinMode(coil3, OUTPUT);
    pinMode(coil4, OUTPUT);
    pinMode(coil5, OUTPUT);
    pinMode(coil6, OUTPUT);
    pinMode(coil7, OUTPUT);
    pinMode(coil8, OUTPUT);
    pinMode(coil9, OUTPUT);
    pinMode(coil10, OUTPUT);
    pinMode(coil11, OUTPUT);
    pinMode(coil12, OUTPUT);
    pinMode(coil13, OUTPUT);
    pinMode(coil14, OUTPUT);
    pinMode(coil15, OUTPUT);
    pinMode(coil16, OUTPUT);
    pinMode(coil17, OUTPUT);
    pinMode(coil18, OUTPUT);
    pinMode(coil19, OUTPUT);

    digitalWrite(coil1, LOW);
    digitalWrite(coil2, LOW);
    digitalWrite(coil3, LOW);
    digitalWrite(coil4, LOW);
    digitalWrite(coil5, LOW);
    digitalWrite(coil6, LOW);
    digitalWrite(coil7, LOW);
    digitalWrite(coil8, LOW);
    digitalWrite(coil9, LOW);
    digitalWrite(coil10, LOW);
    digitalWrite(coil11, LOW);
    digitalWrite(coil12, LOW);
    digitalWrite(coil13, LOW);
    digitalWrite(coil14, LOW);
    digitalWrite(coil15, LOW);
    digitalWrite(coil16, LOW);
    digitalWrite(coil17, LOW);
    digitalWrite(coil18, LOW);
    digitalWrite(coil19, LOW);

    pinMode(inputSwitch, INPUT_PULLDOWN);

    pinMode(opto1, INPUT_PULLUP);
    pinMode(opto2, INPUT_PULLUP);
    pinMode(opto3, INPUT_PULLUP);
    pinMode(opto4, INPUT_PULLUP);
    pinMode(opto5, INPUT_PULLUP);
    pinMode(opto6, INPUT_PULLUP);
    pinMode(opto7, INPUT_PULLUP);
    pinMode(opto8, INPUT_PULLUP);
    pinMode(opto9, INPUT_PULLUP);
    pinMode(opto10, INPUT_PULLUP);
    pinMode(opto11, INPUT_PULLUP);
    pinMode(opto12, INPUT_PULLUP);
    pinMode(opto13, INPUT_PULLUP);
    pinMode(opto14, INPUT_PULLUP);
    pinMode(opto15, INPUT_PULLUP);
    pinMode(opto16, INPUT_PULLUP);
    pinMode(opto17, INPUT_PULLUP);
    pinMode(opto18, INPUT_PULLUP);
    pinMode(opto19, INPUT_PULLUP);

    Serial.begin(9600);
    Serial.println("begining");
    myTimer.begin(timout, tim);
    attachInterrupt(digitalPinToInterrupt(inputSwitch), FireInterrupt, RISING);
}