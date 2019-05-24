#ifndef motorFunction_h
#define motorFunctions_h
#include <globals.h>
#include <SoftwareSerial.h>
#include <Sabertooth.h>
#include <fuzzyLogic.h>

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

double AGGR_PWR(double sp, double dir, double trn, double hlt)
{
    return fuzzyOR(fuzzyOR(sp, dir), fuzzyAND(trn, fuzzyNOT(hlt)));
}

void drive(int driveData[])
{
    int FB = driveData[0];
    int LR = driveData[1];
    int TRN = driveData[2];
    int SMAX = driveData[3];

    //translate crisp joystic values into fuzzy set membership degrees:

    double f_FWD = fuzzyGrade(FB, F_GRD_LO, F_GRD_HI);
    double f_FB_HLT = fuzzyTriangle(FB, F_TRI_LOL, F_TRI_HI, F_TRI_LOR);
    double f_BCK = fuzzyRevGrade(FB, F_REV_GRD_LO, F_REV_GRD_HI);
    double f_L = fuzzyRevGrade(LR, F_REV_GRD_LO, F_REV_GRD_HI);
    double f_FR_HLT = fuzzyTriangle(LR, F_TRI_LOL, F_TRI_HI, F_TRI_LOR);
    double f_R = fuzzyGrade(LR, F_GRD_LO, F_GRD_HI);
    double f_TL = fuzzyRevGrade(TRN, F_REV_GRD_LO, F_REV_GRD_HI);
    double f_T_HLT = fuzzyTriangle(TRN, F_TRI_LOL, F_TRI_HI, F_TRI_LOR);
    double f_TR = fuzzyGrade(TRN, F_GRD_LO, F_GRD_HI);

    //calculate speed and direction per motor:

    int MFL_speed = (int)(SMAX * AGGR_PWR(f_FWD, f_R, f_TR, f_T_HLT) + (-SMAX) * AGGR_PWR(f_BCK, f_L, f_TL, f_T_HLT));
    int MFR_speed = (int)(SMAX * AGGR_PWR(f_FWD, f_L, f_TL, f_T_HLT) + (-SMAX) * AGGR_PWR(f_BCK, f_R, f_TR, f_T_HLT));
    int MBL_speed = (int)(SMAX * AGGR_PWR(f_FWD, f_L, f_TR, f_T_HLT) + (-SMAX) * AGGR_PWR(f_BCK, f_R, f_TL, f_T_HLT));
    int MBR_speed = (int)(SMAX * AGGR_PWR(f_FWD, f_R, f_TL, f_T_HLT) + (-SMAX) * AGGR_PWR(f_BCK, f_L, f_TR, f_T_HLT));

    //drive the thing:

    if (DEBUG_MOTORS)
    {

        DEBUG("MFL:" + String(MFL_speed) + "_MFR:" + String(MFR_speed) + "_MBL:" + String(MBL_speed) + "_MBR:" + String(MBR_speed));
    }

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