#include <UI.h>

UI::UI()
{
    ledState = LOW;
}

void UI::toggle()
{
    ledState = !ledState;
    digitalWrite(LEDPIN, ledState);
    DEBUG("toggled");
}
