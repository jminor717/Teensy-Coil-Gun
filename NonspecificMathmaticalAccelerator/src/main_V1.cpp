//Gun controll
/*
#include <Arduino.h>
#include <atomic>
#include <queue>
#include <deque>
//#include "QuickCompBoolList.hpp"
//#include <fastGPIO.hpp>

//#define TestElectrical

//FREE 16, 17, , 23

#define opto1 0
#define opto2 1
#define opto3 2
#define opto4 3
#define opto5 4
#define opto6 5
#define opto7 6
#define opto8 7
#define opto9 8
#define opto10 9
#define opto11 10
#define opto12 11

#define inputSwitch 12
#define BuckEnable 13
#define StableStateReachedPin 22

#define coilH1 24
#define coilH2 26
#define coilH3 28
#define coilH4 30
#define coilH5 32
#define coilH6 34
#define coilH7 36
#define coilH8 38
#define coilH9 40
#define coilH10 14
#define coilH11 18
#define coilH12 20

#define coilL1 25
#define coilL2 27
#define coilL3 29
#define coilL4 31
#define coilL5 33
#define coilL6 35
#define coilL7 37
#define coilL8 39
#define coilL9 41
#define coilL10 15
#define coilL11 19
#define coilL12 21

#define ProjectileLength 2
#define DebounceQueSize 3
#define FireSettleLimit 50

IntervalTimer myTimer;

std::atomic<bool> running(false);
std::atomic<bool> ending(false);

int tim = 10 * 1000; // 10 miliseconds
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

void opto1callback();
std::atomic<bool> opto1Active(false);
void opto2callback();
std::atomic<bool> opto2Active(false);
void opto3callback();
std::atomic<bool> opto3Active(false);
void opto4callback();
std::atomic<bool> opto4Active(false);
void opto5callback();
std::atomic<bool> opto5Active(false);
void opto6callback();
std::atomic<bool> opto6Active(false);
void opto7callback();
std::atomic<bool> opto7Active(false);
void opto8callback();
std::atomic<bool> opto8Active(false);
void opto9callback();
std::atomic<bool> opto9Active(false);
void opto10callback();
std::atomic<bool> opto10Active(false);
void opto11callback();
std::atomic<bool> opto11Active(false);
void opto12callback();
std::atomic<bool> opto12Active(false);

QuickCompBoolList<DebounceQueSize> DebounceQue;

void timout()
{
    myTimer.end();
    ending = true;
    running = true; //this should be true anyways but set it here to make sure

    digitalWriteFast(coilL1, LOW);
    digitalWriteFast(coilH1, LOW);
    digitalWriteFast(coilL2, LOW);
    digitalWriteFast(coilH2, LOW);
    digitalWriteFast(coilL3, LOW);
    digitalWriteFast(coilH3, LOW);
    digitalWriteFast(coilL4, LOW);
    digitalWriteFast(coilH4, LOW);
    digitalWriteFast(coilL5, LOW);
    digitalWriteFast(coilH5, LOW);
    digitalWriteFast(coilL6, LOW);
    digitalWriteFast(coilH6, LOW);
    digitalWriteFast(coilL7, LOW);
    digitalWriteFast(coilH7, LOW);
    digitalWriteFast(coilL8, LOW);
    digitalWriteFast(coilH8, LOW);
    digitalWriteFast(coilL9, LOW);
    digitalWriteFast(coilH9, LOW);
    digitalWriteFast(coilL10, LOW);
    digitalWriteFast(coilH10, LOW);
    digitalWriteFast(coilL11, LOW);
    digitalWriteFast(coilH11, LOW);
    digitalWriteFast(coilL12, LOW);
    digitalWriteFast(coilH12, LOW);
    digitalWriteFast(BuckEnable, LOW);

    if (opto1Active)
    {
        detachInterrupt(opto1); //stop any further inturupts until next fire
        opto1Active = false;
    }
    if (opto2Active)
    {
        detachInterrupt(opto2);
        opto2Active = false;
    }
    if (opto3Active)
    {
        detachInterrupt(opto3);
        opto3Active = false;
    }
    if (opto4Active)
    {
        detachInterrupt(opto4);
        opto4Active = false;
    }
    if (opto5Active)
    {
        detachInterrupt(opto5);
        opto5Active = false;
    }
    if (opto6Active)
    {
        detachInterrupt(opto6);
        opto6Active = false;
    }
    if (opto7Active)
    {
        detachInterrupt(opto7);
        opto7Active = false;
    }
    if (opto8Active)
    {
        detachInterrupt(opto8);
        opto8Active = false;
    }
    if (opto9Active)
    {
        detachInterrupt(opto9);
        opto9Active = false;
    }
    if (opto10Active)
    {
        detachInterrupt(opto10);
        opto10Active = false;
    }
    if (opto11Active)
    {
        detachInterrupt(opto11);
        opto11Active = false;
    }
    if (opto12Active)
    {
        detachInterrupt(opto12);
        opto12Active = false;
    }

    running = false;
    Serial.println("timeout");
    delay(50); //allow time for everything to reach a steady state

    digitalWriteFast(coilL1, HIGH); // turn on low side transistors so that the highside bootstrap capacitor can charge
    digitalWriteFast(coilL2, HIGH);
    digitalWriteFast(coilL3, HIGH);
    digitalWriteFast(coilL4, HIGH);
    digitalWriteFast(coilL5, HIGH);
    digitalWriteFast(coilL6, HIGH);
    digitalWriteFast(coilL7, HIGH);
    digitalWriteFast(coilL8, HIGH);
    digitalWriteFast(coilL9, HIGH);
    digitalWriteFast(coilL10, HIGH);
    digitalWriteFast(coilL11, HIGH);
    digitalWriteFast(coilL12, HIGH);
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

void Fire()
{
    running = true;
    digitalWriteFast(StableStateReachedPin, LOW); // tell power controll that we are in the fiering process
    Serial.println("fire");

    digitalWriteFast(BuckEnable, HIGH); // tell power controll that we are ready to receive power
    digitalWriteFast(coilL1, HIGH);
    digitalWriteFast(coilL2, HIGH);
    digitalWriteFast(coilH1, HIGH);
    digitalWriteFast(coilH2, HIGH);
#ifdef TestElectrical
    delay(1);
    opto1callback();
#else
    attachInterrupt(opto1, opto1callback, FALLING);
    opto1Active = true;
    myTimer.begin(timout, tim);
#endif
}

void opto1callback()
{
    //Serial.println("1");
    switch (ProjectileLength)
    {
    case 1:
    {
        digitalWriteFast(coilL3, HIGH);
        digitalWriteFast(coilH3, HIGH);
        digitalWriteFast(coilH1, LOW);
        digitalWriteFast(coilL1, LOW);
        break;
    }
    case 2:
    {
        digitalWriteFast(coilL3, HIGH);
        digitalWriteFast(coilH3, HIGH);
        digitalWriteFast(coilH1, LOW);
        digitalWriteFast(coilL1, LOW);
        break;
    }
    case 3:
    {
        digitalWriteFast(coilL3, HIGH);
        digitalWriteFast(coilH3, HIGH);
        break;
    }
    case 4:
    {
        digitalWriteFast(coilL3, HIGH);
        digitalWriteFast(coilH3, HIGH);
        break;
    }
    default:
        break;
    }

#ifdef TestElectrical
    delay(1);
    opto2callback();
#else
    attachInterrupt(opto2, opto2callback, FALLING);
    detachInterrupt(opto1);
    opto1Active = false;
    opto2Active = true;
    myTimer.begin(timout, tim);
#endif
}
void opto2callback()
{
    //Serial.println("2");
    switch (ProjectileLength)
    {
    case 1:
    {
        digitalWriteFast(coilL4, HIGH);
        digitalWriteFast(coilH4, HIGH);
        digitalWriteFast(coilH2, LOW);
        digitalWriteFast(coilL2, LOW);
        break;
    }
    case 2:
    {
        digitalWriteFast(coilL4, HIGH);
        digitalWriteFast(coilH4, HIGH);
        digitalWriteFast(coilH2, LOW);
        digitalWriteFast(coilL2, LOW);
        break;
    }
    case 3:
    {
        digitalWriteFast(coilL4, HIGH);
        digitalWriteFast(coilH4, HIGH);
        digitalWriteFast(coilH1, LOW);
        digitalWriteFast(coilL1, LOW);
        break;
    }
    case 4:
    {
        digitalWriteFast(coilL4, HIGH);
        digitalWriteFast(coilH4, HIGH);
        break;
    }
    default:
        break;
    }

#ifdef TestElectrical
    delay(1);
    opto3callback();
#else
    attachInterrupt(opto3, opto3callback, FALLING);
    detachInterrupt(opto2);
    opto2Active = false;
    opto3Active = true;
    myTimer.begin(timout, tim);
#endif
}
void opto3callback()
{
    //Serial.println("3");
    switch (ProjectileLength)
    {
    case 1:
    {
        digitalWriteFast(coilL5, HIGH);
        digitalWriteFast(coilH5, HIGH);
        digitalWriteFast(coilH3, LOW);
        digitalWriteFast(coilL3, LOW);
        break;
    }
    case 2:
    {
        digitalWriteFast(coilL5, HIGH);
        digitalWriteFast(coilH5, HIGH);
        digitalWriteFast(coilH3, LOW);
        digitalWriteFast(coilL3, LOW);
        break;
    }
    case 3:
    {
        digitalWriteFast(coilL5, HIGH);
        digitalWriteFast(coilH5, HIGH);
        digitalWriteFast(coilH2, LOW);
        digitalWriteFast(coilL3, LOW);
        break;
    }
    case 4:
    {
        digitalWriteFast(coilL5, HIGH);
        digitalWriteFast(coilH5, HIGH);
        digitalWriteFast(coilH1, LOW);
        digitalWriteFast(coilL1, LOW);
        break;
    }
    default:
        break;
    }

#ifdef TestElectrical
    delay(1);
    opto4callback();
#else
    attachInterrupt(opto4, opto4callback, FALLING);
    detachInterrupt(opto3);
    opto3Active = false;
    opto4Active = true;
    myTimer.begin(timout, tim);
#endif
}
void opto4callback()
{
    //Serial.println("4");
    switch (ProjectileLength)
    {
    case 1:
    {
        digitalWriteFast(coilL6, HIGH);
        digitalWriteFast(coilH6, HIGH);
        digitalWriteFast(coilH4, LOW);
        digitalWriteFast(coilL4, LOW);
        break;
    }
    case 2:
    {
        digitalWriteFast(coilL6, HIGH);
        digitalWriteFast(coilH6, HIGH);
        digitalWriteFast(coilH4, LOW);
        digitalWriteFast(coilL4, LOW);
        break;
    }
    case 3:
    {
        digitalWriteFast(coilL6, HIGH);
        digitalWriteFast(coilH6, HIGH);
        digitalWriteFast(coilH3, LOW);
        digitalWriteFast(coilL3, LOW);
        break;
    }
    case 4:
    {
        digitalWriteFast(coilL6, HIGH);
        digitalWriteFast(coilH6, HIGH);
        digitalWriteFast(coilH2, LOW);
        digitalWriteFast(coilL2, LOW);
        break;
    }
    default:
        break;
    }

#ifdef TestElectrical
    delay(1);
    opto5callback();
#else
    attachInterrupt(opto5, opto5callback, FALLING);
    detachInterrupt(opto4);
    opto4Active = false;
    opto5Active = true;
    myTimer.begin(timout, tim);
#endif
}
void opto5callback()
{
    //Serial.println("5");
    switch (ProjectileLength)
    {
    case 1:
    {
        digitalWriteFast(coilL7, HIGH);
        digitalWriteFast(coilH7, HIGH);
        digitalWriteFast(coilH5, LOW);
        digitalWriteFast(coilL5, LOW);
        break;
    }
    case 2:
    {
        digitalWriteFast(coilL7, HIGH);
        digitalWriteFast(coilH7, HIGH);
        digitalWriteFast(coilH5, LOW);
        digitalWriteFast(coilL5, LOW);
        break;
    }
    case 3:
    {
        digitalWriteFast(coilL7, HIGH);
        digitalWriteFast(coilH7, HIGH);
        digitalWriteFast(coilH4, LOW);
        digitalWriteFast(coilL4, LOW);
        break;
    }
    case 4:
    {
        digitalWriteFast(coilL7, HIGH);
        digitalWriteFast(coilH7, HIGH);
        digitalWriteFast(coilH3, LOW);
        digitalWriteFast(coilL3, LOW);
        break;
    }
    default:
        break;
    }

#ifdef TestElectrical
    delay(1);
    opto6callback();
#else
    attachInterrupt(opto6, opto6callback, FALLING);
    detachInterrupt(opto5);
    opto5Active = false;
    opto6Active = true;
    myTimer.begin(timout, tim);
#endif
}
void opto6callback()
{
    //Serial.println("6");
    switch (ProjectileLength)
    {
    case 1:
    {
        digitalWriteFast(coilL8, HIGH);
        digitalWriteFast(coilH8, HIGH);
        digitalWriteFast(coilH6, LOW);
        digitalWriteFast(coilL6, LOW);
        digitalWriteFast(BuckEnable, LOW); // tell power controll that we no longer need power, this should be done before the last coil is turned off
        break;
    }
    case 2:
    {
        digitalWriteFast(coilL8, HIGH);
        digitalWriteFast(coilH8, HIGH);
        digitalWriteFast(coilH6, LOW);
        digitalWriteFast(coilL6, LOW);
        digitalWriteFast(BuckEnable, LOW);
        break;
    }
    case 3:
    {
        digitalWriteFast(coilL8, HIGH);
        digitalWriteFast(coilH8, HIGH);
        digitalWriteFast(coilH5, LOW);
        digitalWriteFast(coilL5, LOW);
        break;
    }
    case 4:
    {
        digitalWriteFast(coilL8, HIGH);
        digitalWriteFast(coilH8, HIGH);
        digitalWriteFast(coilH4, LOW);
        digitalWriteFast(coilL4, LOW);
        break;
    }
    default:
        break;
    }

#ifdef TestElectrical
    delay(1);
    opto7callback();
#else
    attachInterrupt(opto7, opto7callback, FALLING);
    detachInterrupt(opto6);
    opto6Active = false;
    opto7Active = true;
    myTimer.begin(timout, tim);
#endif
}
void opto7callback()
{
    //Serial.println("7");
    switch (ProjectileLength)
    {
    case 1:
    {
        digitalWriteFast(coilL9, HIGH);
        digitalWriteFast(coilH9, HIGH);
        digitalWriteFast(coilH7, LOW);
        digitalWriteFast(coilL7, LOW);
        break;
    }
    case 2:
    {
        digitalWriteFast(coilL9, HIGH);
        digitalWriteFast(coilH9, HIGH);
        digitalWriteFast(coilH7, LOW);
        digitalWriteFast(coilL7, LOW);
        break;
    }
    case 3:
    {
        digitalWriteFast(coilL9, HIGH);
        digitalWriteFast(coilH9, HIGH);
        digitalWriteFast(coilH6, LOW);
        digitalWriteFast(coilL6, LOW);
        digitalWriteFast(BuckEnable, LOW);
        break;
    }
    case 4:
    {
        digitalWriteFast(coilL9, HIGH);
        digitalWriteFast(coilH9, HIGH);
        digitalWriteFast(coilH5, LOW);
        digitalWriteFast(coilL5, LOW);
        break;
    }
    default:
        break;
    }

#ifdef TestElectrical
    delay(1);
    opto8callback();
#else
    attachInterrupt(opto8, opto8callback, FALLING);
    detachInterrupt(opto7);
    opto7Active = false;
    opto8Active = true;
    myTimer.begin(timout, tim);
#endif
}
void opto8callback()
{
    //Serial.println("8");
    switch (ProjectileLength)
    {
    case 1:
    {
        digitalWriteFast(coilL10, HIGH);
        digitalWriteFast(coilH10, HIGH);
        digitalWriteFast(coilH8, LOW);
        digitalWriteFast(coilL8, LOW);
        break;
    }
    case 2:
    {
        digitalWriteFast(coilL10, HIGH);
        digitalWriteFast(coilH10, HIGH);
        digitalWriteFast(coilH8, LOW);
        digitalWriteFast(coilL8, LOW);
        break;
    }
    case 3:
    {
        digitalWriteFast(coilL10, HIGH);
        digitalWriteFast(coilH10, HIGH);
        digitalWriteFast(coilH7, LOW);
        digitalWriteFast(coilL7, LOW);
        break;
    }
    case 4:
    {
        digitalWriteFast(coilL10, HIGH);
        digitalWriteFast(coilH10, HIGH);
        digitalWriteFast(coilH6, LOW);
        digitalWriteFast(coilL6, LOW);
        digitalWriteFast(BuckEnable, LOW);
        break;
    }
    default:
        break;
    }

#ifdef TestElectrical
    delay(1);
    opto9callback();
#else
    attachInterrupt(opto9, opto9callback, FALLING);
    detachInterrupt(opto8);
    opto8Active = false;
    opto9Active = true;
    myTimer.begin(timout, tim);
#endif
}
void opto9callback()
{
    //Serial.println("9");
    switch (ProjectileLength)
    {
    case 1:
    {
        digitalWriteFast(coilL11, HIGH);
        digitalWriteFast(coilH11, HIGH);
        digitalWriteFast(coilH9, LOW);
        digitalWriteFast(coilL9, LOW);
        break;
    }
    case 2:
    {
        digitalWriteFast(coilL11, HIGH);
        digitalWriteFast(coilH11, HIGH);
        digitalWriteFast(coilH9, LOW);
        digitalWriteFast(coilL9, LOW);
        break;
    }
    case 3:
    {
        digitalWriteFast(coilL11, HIGH);
        digitalWriteFast(coilH11, HIGH);
        digitalWriteFast(coilH8, LOW);
        digitalWriteFast(coilL8, LOW);
        break;
    }
    case 4:
    {
        digitalWriteFast(coilL11, HIGH);
        digitalWriteFast(coilH11, HIGH);
        digitalWriteFast(coilH7, LOW);
        digitalWriteFast(coilL7, LOW);
        break;
    }
    default:
        break;
    }

#ifdef TestElectrical
    delay(1);
    opto10callback();
#else
    attachInterrupt(opto10, opto10callback, FALLING);
    detachInterrupt(opto9);
    opto9Active = false;
    opto10Active = true;
    myTimer.begin(timout, tim);
#endif
}
void opto10callback()
{
    //Serial.println("10");
    switch (ProjectileLength)
    {
    case 1:
    {
        digitalWriteFast(coilL12, HIGH);
        digitalWriteFast(coilH12, HIGH);
        digitalWriteFast(coilH10, LOW);
        digitalWriteFast(coilL10, LOW);
        break;
    }
    case 2:
    {
        digitalWriteFast(coilL12, HIGH);
        digitalWriteFast(coilH12, HIGH);
        digitalWriteFast(coilH10, LOW);
        digitalWriteFast(coilL10, LOW);
        break;
    }
    case 3:
    {
        digitalWriteFast(coilL12, HIGH);
        digitalWriteFast(coilH12, HIGH);
        digitalWriteFast(coilH9, LOW);
        digitalWriteFast(coilL9, LOW);
        break;
    }
    case 4:
    {
        digitalWriteFast(coilL12, HIGH);
        digitalWriteFast(coilH12, HIGH);
        digitalWriteFast(coilH8, LOW);
        digitalWriteFast(coilL8, LOW);
        break;
    }
    default:
        break;
    }

#ifdef TestElectrical
    delay(1);
    opto11callback();
#else
    attachInterrupt(opto11, opto11callback, FALLING);
    detachInterrupt(opto10);
    opto10Active = false;
    opto11Active = true;
    myTimer.begin(timout, tim);
#endif
}
void opto11callback()
{
    //Serial.println("11");
    switch (ProjectileLength)
    {
    case 1:
    {
        digitalWriteFast(coilH11, LOW);
        digitalWriteFast(coilL11, LOW);
        break;
    }
    case 2:
    {
        digitalWriteFast(coilH11, LOW);
        digitalWriteFast(coilL11, LOW);
        break;
    }
    case 3:
    {
        digitalWriteFast(coilH10, LOW);
        digitalWriteFast(coilL10, LOW);
        break;
    }
    case 4:
    {
        digitalWriteFast(coilH9, LOW);
        digitalWriteFast(coilL9, LOW);
        break;
    }
    default:
        break;
    }

#ifdef TestElectrical
    delay(1);
    opto12callback();
#else
    attachInterrupt(opto12, opto12callback, FALLING);
    detachInterrupt(opto11);
    opto11Active = false;
    opto12Active = true;
    myTimer.begin(timout, tim);
#endif
}
void opto12callback()
{
    //Serial.println("12");
    switch (ProjectileLength)
    {
    case 1:
    {
        digitalWriteFast(coilH12, LOW);
        digitalWriteFast(coilL12, LOW);
        break;
    }
    case 2:
    {
        digitalWriteFast(coilH12, LOW);
        digitalWriteFast(coilL12, LOW);
        break;
    }
    case 3:
    {
        digitalWriteFast(coilH11, LOW);
        digitalWriteFast(coilL11, LOW);
        digitalWriteFast(coilH12, LOW);
        digitalWriteFast(coilL12, LOW);
        break;
    }
    case 4:
    {
        digitalWriteFast(coilH10, LOW);
        digitalWriteFast(coilL10, LOW);
        digitalWriteFast(coilH11, LOW);
        digitalWriteFast(coilL11, LOW);
        digitalWriteFast(coilH12, LOW);
        digitalWriteFast(coilL12, LOW);
        break;
    }
    default:
        break;
    }

#ifdef TestElectrical
#else
    detachInterrupt(opto12);
    opto12Active = false;
#endif
    timout();
}

#undef main

int main()
{
    pinMode(BuckEnable, OUTPUT);
    pinMode(StableStateReachedPin, OUTPUT);

    pinMode(coilL1, OUTPUT);
    pinMode(coilL2, OUTPUT);
    pinMode(coilL3, OUTPUT);
    pinMode(coilL4, OUTPUT);
    pinMode(coilL5, OUTPUT);
    pinMode(coilL6, OUTPUT);
    pinMode(coilL7, OUTPUT);
    pinMode(coilL8, OUTPUT);
    pinMode(coilL9, OUTPUT);
    pinMode(coilL10, OUTPUT);
    pinMode(coilL11, OUTPUT);
    pinMode(coilL12, OUTPUT);

    digitalWrite(coilL1, LOW);
    digitalWrite(coilL2, LOW);
    digitalWrite(coilL3, LOW);
    digitalWrite(coilL4, LOW);
    digitalWrite(coilL5, LOW);
    digitalWrite(coilL6, LOW);
    digitalWrite(coilL7, LOW);
    digitalWrite(coilL8, LOW);
    digitalWrite(coilL9, LOW);
    digitalWrite(coilL10, LOW);
    digitalWrite(coilL11, LOW);
    digitalWrite(coilL12, LOW);

    pinMode(coilH1, OUTPUT);
    pinMode(coilH2, OUTPUT);
    pinMode(coilH3, OUTPUT);
    pinMode(coilH4, OUTPUT);
    pinMode(coilH5, OUTPUT);
    pinMode(coilH6, OUTPUT);
    pinMode(coilH7, OUTPUT);
    pinMode(coilH8, OUTPUT);
    pinMode(coilH9, OUTPUT);
    pinMode(coilH10, OUTPUT);
    pinMode(coilH11, OUTPUT);
    pinMode(coilH12, OUTPUT);

    digitalWriteFast(coilH1, LOW);
    digitalWrite(coilH1, LOW);
    digitalWrite(coilH2, LOW);
    digitalWrite(coilH3, LOW);
    digitalWrite(coilH4, LOW);
    digitalWrite(coilH5, LOW);
    digitalWrite(coilH6, LOW);
    digitalWrite(coilH7, LOW);
    digitalWrite(coilH8, LOW);
    digitalWrite(coilH9, LOW);
    digitalWrite(coilH10, LOW);
    digitalWrite(coilH11, LOW);
    digitalWrite(coilH12, LOW);

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

    Serial.begin(9600);
    Serial.println("begining");
    myTimer.begin(timout, tim);
    attachInterrupt(digitalPinToInterrupt(inputSwitch), FireInterrupt, RISING);
}



//FireSettleLimit

void loop()
{
    while (1)
    {
        if (!running)
        {
            DebounceQue.push(digitalReadFast(inputSwitch));
            if (FireTriggered)//set from fire pin interrupt 
            {
                FireSettleCount++;
                if (DebounceQue.isAllTrue())
                {
                    FireSettleCount = 0;
                    Fire();
                }
                if (FireSettleCount > FireSettleLimit) //allow FireSettleLimit number of cycles before aborting the fire sequence
                {
                    FireTriggered = false;
                    FireSettleCount = 0;
                }
            }
        }
    }
}*/