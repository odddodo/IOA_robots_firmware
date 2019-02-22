#include <UI.h>

UI::UI()
{

    ledState = LOW;
    UI_state = 0;
}

void UI::update_UI(int refTick)
{

    switch (UI_state)
    {
    case 0:
        DEBUG("whatever state");
        break;
    case 1:
        DEBUG("another state");
        break;
    default:
        DEBUG("default state");
        break;
    }
}

void UI::toggle()
{
    ledState = !ledState;
    digitalWrite(LEDPIN, ledState);
    DEBUG("toggled");
}

void UI::fade(int freq)
{
}

void UI::blink(int freq)
{
}

void UI::setState(int newState)
{
    UI_state = newState;
}
