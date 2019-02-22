#ifndef routines_h
#define routines_h
#include <Ticker.h>
#include <UI.h>

void update_UI();

UI statusIndicator;
Ticker UI_updater(update_UI, 500, 10);

void initRoutines()
{
    UI_updater.start();
}

void updateRoutines()
{
    UI_updater.update();
}

void update_UI()
{
    statusIndicator.toggle();
}

#endif