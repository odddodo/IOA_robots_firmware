#ifndef routines_h
#define routines_h
#include <Ticker.h>
#include <UI.h>
#include <debug.h>

UI statusInd;
bool UI_on = false;

void update_UI();
void startup();

Ticker startupCounter(startup, 300, STARTUP_CYCLES); //power up cycle: give some time for the router to settle
Ticker UI_updater(update_UI, 4);                     //update ui every 4ms

void initRoutines()
{
    startupCounter.start();
    UI_updater.start();
}

void updateRoutines()
{
    startupCounter.update();

    if (UI_on)
    {
        UI_updater.update();
    }
}

void startup()
{

    DEBUG(".");
    statusInd.toggle();
    if (startupCounter.counter() > STARTUP_CYCLES - 1)
    {

        DEBUG("init done");
        UI_on = true;
        statusInd.setState(2);
    }
}

void update_UI()
{
    statusInd.update_UI(UI_updater.counter());
}

#endif