#ifndef routines_h
#define routines_h
#include <Ticker.h>
#include <UI.h>
#include <allTheTalking.h>
#include <debug.h>

UI statusInd;

bool UI_on = false;
bool UDP_on = false;

void update_UI();
void startup();
void handle_UDP_talking();

Ticker startupCounter(startup, 100, STARTUP_CYCLES); //power up cycle: give 25s for the router to settle
Ticker UI_updater(update_UI, 4);                     //update ui every 4ms
Ticker UDP_listener(handleIncommmingPackets, 10);    //handle incomming messages every 10ms
Ticker UDP_talker(handleReplies, 100);

void initRoutines()
{
    startupCounter.start();
    UI_updater.start();
    UDP_listener.start();
    UDP_talker.start();
}

void updateRoutines()
{
    startupCounter.update();

    if (UI_on)
    {
        UI_updater.update();
    }

    if (UDP_on)
    {
        UDP_listener.update();
        UDP_talker.update();
    }
}

void startup()
{

    if (DEBUG_ROUTINES)
        DEBUG(".");
    statusInd.toggle();

    if (startupCounter.counter() > STARTUP_CYCLES - 1)
    {
        UI_on = true;
        UDP_on = true;
        statusInd.setState(2);
        if (DEBUG_ROUTINES)
            DEBUG("init done");
    }
}

void update_UI()
{
    statusInd.update_UI(UI_updater.counter());
}

#endif