#include <Arduino.h>
#include <debug.h>
#include <hardwareSetup.h>
#include <routines.h>

int debugging_enabled = 1;

void setup()
{
  DEBUG("alive!");
  initHardware();
  initUDPServer();
  initRoutines();
}

void loop()
{
  updateRoutines();
}