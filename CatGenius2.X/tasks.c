
#include "tasks.h"
#include "catgenie120.h"
#include "process.h"
#include "businesslogic.h"

#include <xc.h>

#define SHOVELUP        1
#define SHOVELDOWN      2
#define SHOVELMID       3
#define SHOVELMOVING    4


#define SHOVELSTOP      0

unsigned long beepcnt = 0;
unsigned short waterLevel = 0;
unsigned char catPresent = 0;

unsigned short shovelTargetPosition=0;
unsigned short shovelCurrentPosition=0;
unsigned char shovelLocation = SHOVELUP;
unsigned char shovelStatus = SHOVELSTOP;
unsigned char fillingWater=0;
unsigned char fillingSoap=0;

char processStartButton();
char processSetupButton();

void checkCatSensorTask();
void addSoapTask();
void shovelGoPositionTask();
void doSafetyTask();
void doBeeperTask();
void waterFillTask();
// Processes
/* doEvents() function handles all the events and needs to be precisely
 * called every 100ms
 */
void doTimedTasks()
{
    static unsigned short timer=0;
    timer++;
    
    if (waterLevel >= WATER_THERSHOLD) LED_3 = 1;
    else LED_3 = 0;
    
    /* disabled for now as digital version works fine
    if (!(timer % 10)) // measure water level every 1s
        waterLevel = measureWaterLevel(1);
    else
        measureWaterLevel(0);
    */
    
    if (!(timer % 11))
        checkCatSensorTask();
    
    doBeeperTask();
    shovelGoPositionTask();
    waterFillTask();
    addSoapTask();
}

/* 
 * doSubTasks() function needs to be periodically called
 */
void doSubTasks()
{
    if (processStartButton()) onStartPressed();
    if (processSetupButton()) onSetupPressed();
    
    doSafetyTask();
}
void doSafetyTask()
{
    
}

void doBeeperTask()
{
    if (beepcnt > 0)
    {
        beepcnt--; 
        BEEPER = 1;
    } else {
        BEEPER = 0;
    }
}

void waterStop()
{
    WATERSENSOR_LED = 0;
    fillingWater=0;
}
void waterFill()
{
    WATERSENSOR_LED = 1;
    fillingWater=4;
}
void waterFillTask()
{
    if (fillingWater >= 2) fillingWater--; // make sure the LED has enough time to switch on
    else {
        if (fillingWater)
        {
            if (WATERSENSORANALOG == 1)
            {
                fillingWater = 0;
                WATERVALVEPULLUP = 0;
            } else {
                WATERVALVEPULLUP = 1;
            }
        } else {
            WATERVALVEPULLUP = 0;
            WATERSENSOR_LED = 0;
        }
    }
}

void addSoap()
{
    fillingSoap = SOAP_QTY_IN_100MS;
}

void addSoapTask()
{
    if (fillingSoap > 0)
    {
        fillingSoap--;
        DOSAGE = 1;
    } else {
        DOSAGE = 0;
    }
}



/* 
 * needs to be called every 100ms
*/
void shovelGoPositionTask()
{
    if (shovelTargetPosition > shovelCurrentPosition)
    {   // shovel lower than position
        shovelCurrentPosition++;
        shovelSetPinForDown();
    }
    else if (shovelTargetPosition < shovelCurrentPosition)
    {   // shovel lower than position
        shovelCurrentPosition--;
        shovelSetPinForUp();
    }
    else
    {
        shovelStop();
    }
}

/** go to the position and return 1 once there
 */
char shovelGoPosition(unsigned short position)
{
    shovelTargetPosition = position;
    if (shovelTargetPosition == shovelCurrentPosition) return 1;
    else return 0;
}
char shovelGoUp()
{
    shovelGoPosition(5); // give some slack to avoid tension. If needed to go totally up, use position 0
    if (shovelTargetPosition == shovelCurrentPosition) return 1;
    else return 0;
}
char shovelGoDown()
{
    shovelGoPosition(SHOVEL_SPEED_SEC*10);
    if (shovelTargetPosition == shovelCurrentPosition) return 1;
    else return 0;
}
void shovelStop()
{
    shovelGoPosition(shovelCurrentPosition);
    shovelStatus = SHOVELSTOP;
    shovelSetPinForStop();
}


void beepFor(unsigned long timePer100Ms)
{
    beepcnt = timePer100Ms;
}

void beep()
{
    beepcnt = 5;
}


char processSetupButton()
{
    static unsigned long dbc=0;
    
    if (dbc > 0) dbc--;
    else if ((SETUPBUTTON == 1))
    {
        dbc = DEBOUNCE;
        return 1;
    } 
    return 0;
}

char processStartButton()
{
    static unsigned long dbc=0;
    
    if (dbc > 0) dbc--;
    else if ((STARTBUTTON == 1))
    {
        dbc = DEBOUNCE;
        return 1;
    } 
    return 0;
}


unsigned char isCatPresent()
{
    return catPresent;
}

void checkCatSensorTask()
{
    volatile int i =0;
    CATSENSOR_LED = 1;
    for (i=0; i<20; i++) ; // small delay
    catPresent = CATSENSOR ? 1 : 0;
    LED_CAT = catPresent;
    CATSENSOR_LED = 0;
}