//Gun controll

#include <Arduino.h>
#include <atomic>
#include <queue>
#include <deque>
//#include "QuickCompBoolList.hpp"
//#include <fastGPIO.hpp>

//#define TestElectrical

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
void opto13callback();
std::atomic<bool> opto13Active(false);
void opto14callback();
std::atomic<bool> opto14Active(false);
void opto15callback();
std::atomic<bool> opto15Active(false);
void opto16callback();
std::atomic<bool> opto16Active(false);
void opto17callback();
std::atomic<bool> opto17Active(false);
void opto18callback();
std::atomic<bool> opto18Active(false);
void opto19callback();
std::atomic<bool> opto19Active(false);

void DetachActiveInterrupts();

void SwitchCoils(uint8_t ON, uint8_t OFF) __attribute__((always_inline));

QuickCompBoolList<DebounceQueSize> DebounceQue;

void timout()
{
    myTimer.end();
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

    DetachActiveInterrupts();

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

void Fire()
{
    running = true;
    digitalWriteFast(StableStateReachedPin, LOW); // tell power controll that we are in the fiering process
    Serial.println("fire");

    digitalWriteFast(BuckEnable, HIGH); // tell power controll that we are ready to receive power
    digitalWriteFast(coil1, HIGH);
    digitalWriteFast(coil2, HIGH);
#ifdef TestElectrical
    delay(1);
    opto1callback();
#else
    attachInterrupt(opto1, opto1callback, FALLING);
    opto1Active = true;
    myTimer.begin(timout, tim);
#endif
}

void SwitchCoils(uint8_t ON, uint8_t OFF)
{
    digitalWriteFast(ON, HIGH);
    digitalWriteFast(OFF, LOW);
}

void opto1callback()
{
    SwitchCoils(coil3, coil1);

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
    SwitchCoils(coil4, coil2);

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
    SwitchCoils(coil5, coil3);

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
    SwitchCoils(coil6, coil4);

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

    SwitchCoils(coil7, coil5);

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
    SwitchCoils(coil8, coil6);

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
    SwitchCoils(coil9, coil7);

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
    SwitchCoils(coil10, coil8);

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
    SwitchCoils(coil11, coil9);

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
    SwitchCoils(coil12, coil10);

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
    SwitchCoils(coil13, coil11);

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
    SwitchCoils(coil14, coil12);

#ifdef TestElectrical
    delay(1);
    opto13callback();
#else
    attachInterrupt(opto13, opto13callback, FALLING);
    detachInterrupt(opto12);
    opto12Active = false;
    opto13Active = true;
    myTimer.begin(timout, tim);
#endif
}
void opto13callback()
{
    SwitchCoils(coil15, coil13);

#ifdef TestElectrical
    delay(1);
    opto14callback();
#else
    attachInterrupt(opto14, opto14callback, FALLING);
    detachInterrupt(opto13);
    opto13Active = false;
    opto14Active = true;
    myTimer.begin(timout, tim);
#endif
}
void opto14callback()
{
    SwitchCoils(coil16, coil14);

#ifdef TestElectrical
    delay(1);
    opto15callback();
#else
    attachInterrupt(opto15, opto15callback, FALLING);
    detachInterrupt(opto14);
    opto14Active = false;
    opto15Active = true;
    myTimer.begin(timout, tim);
#endif
}
void opto15callback()
{

    SwitchCoils(coil17, coil15);

#ifdef TestElectrical
    delay(1);
    opto16callback();
#else
    attachInterrupt(opto16, opto16callback, FALLING);
    detachInterrupt(opto15);
    opto15Active = false;
    opto16Active = true;
    myTimer.begin(timout, tim);
#endif
}
void opto16callback()
{
    SwitchCoils(coil18, coil16);

#ifdef TestElectrical
    delay(1);
    opto17callback();
#else
    attachInterrupt(opto17, opto17callback, FALLING);
    detachInterrupt(opto16);
    opto16Active = false;
    opto17Active = true;
    myTimer.begin(timout, tim);
#endif
}
void opto17callback()
{
    SwitchCoils(coil19, coil17);

#ifdef TestElectrical
    delay(1);
    opto18callback();
#else
    attachInterrupt(opto18, opto18callback, FALLING);
    detachInterrupt(opto17);
    opto17Active = false;
    opto18Active = true;
    myTimer.begin(timout, tim);
#endif
}
void opto18callback()
{
    digitalWriteFast(coil18, LOW);

#ifdef TestElectrical
    delay(1);
    opto19callback();
#else
    attachInterrupt(opto19, opto19callback, FALLING);
    detachInterrupt(opto18);
    opto18Active = false;
    opto19Active = true;
    myTimer.begin(timout, tim);
#endif
}

void opto19callback()
{
    digitalWriteFast(coil19, LOW);

#ifdef TestElectrical
#else
    detachInterrupt(opto19);
    opto19Active = false;
#endif
    timout();
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

void DetachActiveInterrupts()
{
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
    if (opto13Active)
    {
        detachInterrupt(opto13);
        opto13Active = false;
    }
    if (opto14Active)
    {
        detachInterrupt(opto14);
        opto14Active = false;
    }
    if (opto15Active)
    {
        detachInterrupt(opto15);
        opto15Active = false;
    }
    if (opto16Active)
    {
        detachInterrupt(opto16);
        opto16Active = false;
    }
    if (opto17Active)
    {
        detachInterrupt(opto17);
        opto17Active = false;
    }
    if (opto18Active)
    {
        detachInterrupt(opto18);
        opto18Active = false;
    }
    if (opto19Active)
    {
        detachInterrupt(opto19);
        opto19Active = false;
    }
}

/*

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