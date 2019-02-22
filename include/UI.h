#ifndef UI_h
#define UI_h
#include <debug.h>
#include <Arduino.h>
#include <globals.h>

class UI
{
private:
  int UI_state;

  int fadeFreq;
  int ledState;
  int pwm_val;
  bool rising;

public:
  UI();

  void toggle();
  void blink();
  void fade();
  void update_UI(int refTick);
  void setState(int newState);
};

#endif