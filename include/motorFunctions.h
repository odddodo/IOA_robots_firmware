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
    M_Front.setRamping(MOTOR_RAMPING);
    M_Back.setRamping(MOTOR_RAMPING);
    halt();
}

void drive(int driveData[])
{
    int FB = driveData[0];
    int LR = driveData[1];
    int TRN = driveData[2];
    int SMAX = driveData[3];

    int MFL_speed = 127;
    int MFR_speed = 127;
    int MBL_speed = 127;
    int MBR_speed = 127;

    M_Front.motor(LEFT, MFL_speed);
    M_Front.motor(RIGHT, MFR_speed);
    M_Back.motor(LEFT, MBL_speed);
    M_Back.motor(RIGHT, MBR_speed);
}

void halt()
{
    M_Front.stop();
    M_Back.stop();
}

#endif