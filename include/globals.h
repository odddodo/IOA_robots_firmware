#ifndef globals_h
#define globals_h
//all the settings here

#define LEDPIN 6

#define STARTUP_CYCLES 25
#define DEBUG_BAUDRATE 9600
#define DEBUG_UI 0
#define DEBUG_ROUTINES 0
#define DEBUG_UDP 0
#define DEBUG_MOTORS 0
#define DEBUG_CMD_MSGS 1

#define SOFT_BAUDRATE 9600
#define MOTOR_RAMPING 30 //intermediate setting

#define LEFT 1
#define RIGHT 2

#define FWD 127
#define BCK -127

#define F_GRD_LO 100
#define F_GRD_HI 190
#define F_REV_GRD_LO 10
#define F_REV_GRD_HI 100
#define F_TRI_LOL 50
#define F_TRI_HI 100
#define F_TRI_LOR 150

#define REPLY_BUFF_SIZE 11
#define NO_MASTER "?%*&#!$"

#endif