#ifndef hardwareSetup_h
#define hardwareSetup_h
#include <Arduino.h>
#include <globals.h>

void initHardware()
{
    Serial.begin(DEBUG_BAUDRATE);
    Serial.println("! serial ok !");

    pinMode(LEDPIN, OUTPUT);
}

#endif