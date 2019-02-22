#ifndef UI_h
#define UI_h
#include <debug.h>
#include <Arduino.h>
#include <globals.h>

class UI
{
  private:
    int ledState;

  public:
    UI();

    void toggle();
    void blink(int freq);
    void fade(int freq);
};

#endif