#ifndef motorFunction_h
#define motorFunctions_h
#include <globals.h>
#include <SoftwareSerial.h>
#include <Sabertooth.h>

SoftwareSerial softSerial(NOT_A_PIN, 3);
Sabertooth M_Front(128, softSerial);
Sabertooth M_Back(129, softSerial);
void halt();

void initMotors()
{
    softSerial.begin(SOFT_BAUDRATE);
    M_Front.autobaud();
    M_Back.autobaud();
    halt();
}

void drive(int driveData[])
{
}

void halt()
{
    M_Front.motor(1, 0);
    M_Front.motor(2, 0);
    M_Back.motor(1, 0);
    M_Back.motor(2, 0);
}

#endif