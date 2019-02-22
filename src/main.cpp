#include <Arduino.h>
#include <debug.h>
#include <hardwareSetup.h>

void setup()
{
  initHardware();
}

void loop()
{
  DEBUG("hello");
}