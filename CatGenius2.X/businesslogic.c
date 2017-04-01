
#include "businesslogic.h"
#include "tasks.h"
#include "process.h"
#include "catgenie120.h"


unsigned char fullWashPerHour=2;
unsigned char doWashInXSec=0;

void attemptFullClean();
void displayLED();

void doBusinessLogicTask()
{
    static unsigned int timer;
    timer++;
    
    displayLED();

    
    if (doWashInXSec > 0)
    {
        doWashInXSec--;
        if (doWashInXSec == 0)
        {
            attemptFullClean();
        }
    }
}

void onStartPressed()
{
    beep();
    doFullClean();
}
void onSetupPressed()
{
    beep();
    fullWashPerHour++;
    if (fullWashPerHour > 4) fullWashPerHour = 0;
}

void attemptFullClean()
{
    if (isCatPresent())
        doWashInXSec = 60;
    else 
        doFullClean();
}

void hourInterrupt(unsigned char hour)
{
    switch (fullWashPerHour)
    {
        case 1:
            if (hour == 0) attemptFullClean();
            break;
            
        case 2:
            if (!(hour % 12)) attemptFullClean();
            break;
            
        case 3:
            if (!(hour % 8)) attemptFullClean();
            break;
            
        case 4:
            if (!(hour % 6)) attemptFullClean();
            break;
    }
}


void displayLED()
{
    LED_1 = 0;
    LED_2 = 0;
    LED_3 = 0;
    LED_4 = 0;
    
    switch (fullWashPerHour)
    {
        case 1: LED_1 = 1; break;
        case 2: LED_2 = 1; break;
        case 3: LED_3 = 1; break;
        case 4: LED_4 = 1; break;
    }
}

