#include <UI.h>

UI::UI()
{

    fadeFreq = 1;
    ledState = LOW;
    UI_state = 0;
    pwm_val = 0;
    rising = true;
}

void UI::update_UI(int refTick)
{

    switch (UI_state)
    {
    case 0:
        if (DEBUG_UI)
        {
            DEBUG("whatever state");
        }

        break;
    case 1:
        if (DEBUG_UI)
        {
            DEBUG("another state");
        }

        if (refTick % fadeFreq == 0)
        {
            toggle();
        }
        break;
    case 2:
        if (refTick % fadeFreq == 0)
        {
            fade();
        }
        if (DEBUG_UI)
        {
            DEBUG(pwm_val);
        }

        break;
    default:
        if (DEBUG_UI)
        {
            DEBUG("default state");
        }

        break;
    }
}

void UI::toggle()
{
    ledState = !ledState;
    digitalWrite(LEDPIN, ledState);
    if (DEBUG_UI)
    {
        DEBUG("toggled");
    }
}

void UI::fade()
{
    if (pwm_val < 255 && pwm_val > 0)
    {
        if (rising)
        {
            pwm_val++;
        }
        else
        {
            pwm_val--;
        }
    }
    else if (pwm_val == 255)
    {
        rising = false;
        pwm_val--;
    }
    else if (pwm_val == 0)
    {
        rising = true;
        pwm_val++;
    }
    analogWrite(LEDPIN, pwm_val);
}

void UI::blink()
{
}

void UI::setState(int newState)
{
    UI_state = newState;
}
