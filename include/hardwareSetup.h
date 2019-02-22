#ifndef hardwareSetup_h
#define hardwareSetup_h
#include <Arduino.h>
#include <globals.h>

void initHardware()
{
    Serial.begin(9600);
    Serial.println("! serial ok !");

    pinMode(LEDPIN, OUTPUT);
}

#endif