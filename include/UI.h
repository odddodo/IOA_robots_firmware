#ifndef UI_h
#define UI_h
#include <debug.h>
#include <Arduino.h>
#include <globals.h>

class UI
{
private:
  int UI_state;

  int ledState;
  int pwm_val;

public:
  UI();

  void toggle();
  void blink(int freq);
  void fade(int freq);
  void update_UI(int refTick);
  void setState(int newState);
};

#endif