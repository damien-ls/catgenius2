

#include "process.h"
#include "tasks.h"
#include "catgenie120.h"

#define WAIT_FOR_STEP(x, y) case x: \
    if (!y); break; \
    state++; break;


#define PICK_CRAP 1
#define WASH      2


#define NOTHING   0
#define FULLCLEAN 1
#define CRAPPICK  2

int currentWork = NOTHING;


char doFullCleaningTask(unsigned short *nextCallSeconds);

char shovelGoUpShake();
char doPickUpCrap(unsigned short *nextCallSeconds);
char doEmptyWater(unsigned short *nextCallSeconds);
char doWash(unsigned short *nextCallSeconds);
char doDry(unsigned short *nextCallSeconds);

/**
 * This function should be called every 1s
 */
void doProcess()
{
    
    static unsigned short timer=0;
    
    if (timer > 1) {
        timer--;
    } else {
        switch (currentWork)
        {
            default:
                currentWork = NOTHING;
                break;

            case FULLCLEAN:
                if (!doFullCleaningTask(&timer)) break;
                beepFor(30);
                currentWork = NOTHING;
                break;

            case CRAPPICK:
                if (!doPickUpCrap(&timer)) break;
                beepFor(30);
                currentWork=NOTHING;
                break;
        }
    
    }
}

void doCrapPick()
{
    currentWork = CRAPPICK;
}
void doFullClean()
{
    currentWork = FULLCLEAN;
}
// return 1 when finished, should be called every 1s
char doFullCleaningTask(unsigned short *nextCallSeconds)
{
    static unsigned char state = 0;

    switch (state)
    {
        default:
            state = 0;
            if (!doPickUpCrap(nextCallSeconds)) break;
            state++;

        case 1:
            if (!doWash(nextCallSeconds)) break;
            state++;

        case 2:
            if (!doDry(nextCallSeconds)) break;
            state++;
            return 1;
    }
    
    return 0;
}

// return 1 when finished, should be called every 1s
char doDry(unsigned short *nextCallSeconds)
{
    static unsigned char state = 0;
    static unsigned char subpross=0;
    switch (state)
    {
        default:
            state = 0;
            subpross = 10;
            DRYER = 1;
            bowlGoCW();
            
        case 1:
            shovelGoPosition(SHOVEL_MAX_POS - 20);
            *nextCallSeconds = 50;
            state++;
            break;

        case 2:
            shovelGoDown();
            *nextCallSeconds = 50;
            state++;
            break;

        case 3:
            shovelGoPosition(SHOVEL_MAX_POS - 40);
            *nextCallSeconds = 10;
            state++;
            break;
            
        case 4:
            shovelGoPosition(SHOVEL_MAX_POS - 20);
            *nextCallSeconds = 50;
            state++;
            break;
            
        case 5:
            shovelGoDown();
            *nextCallSeconds = 50;

            if (subpross)
            {
                subpross--;
                state = 1;
            } else {
                state++;
            }
            break;
            
        case 6: // levelling
            shovelGoPosition(SHOVEL_MAX_POS - 25);
            *nextCallSeconds = 60;
            state++;
            break;
            
        case 7: 
            DRYER = 0;
            if (!shovelGoUpShake()) break;
            shovelGoUp();
            bowlStop();
            state++;
            return 1;
    }
    return 0;
}
// return 1 when finished, should be called every 1s
char doWash(unsigned short *nextCallSeconds)
{
    static unsigned char state = 0;
    
    switch (state)
    {
        default: // first remove the pee
            state = 0;
            waterFill();
            *nextCallSeconds = 5;
            state++;
            break;
            
        case 1:
            PUMP = 1;
            waterStop();
            *nextCallSeconds = 7;
            state++;
            break;
            
        case 2:
            PUMP = 0;
            waterFill();
            bowlGoCW();
            addSoap();
            state++;
            break;
            
        case 3:
            if (!shovelGoDown()) break;
            *nextCallSeconds = 180;
            state++;
            break;
    
        case 4:
            if (!doEmptyWater(nextCallSeconds)) break;
            waterFill();
            *nextCallSeconds = 180;
            state++;
            break;
     
        case 5:
            if (!doEmptyWater(nextCallSeconds)) break;
            state++;
            return 1;
    }
    return 0;
}


// return 1 when finished, should be called every 1s
char doEmptyWater(unsigned short *nextCallSeconds)
{
    static unsigned char state = 0;
    
    switch (state)
    {
        default:
            state=0;
            PUMP = 1;
            *nextCallSeconds = 45;
            break;
    
        case 1:
            PUMP = 0;
            *nextCallSeconds = 45;
            break;
            
        case 2:
            PUMP = 1;
            *nextCallSeconds = 45;
            break;
            
        case 3:
            PUMP = 0;
            *nextCallSeconds = 45;
            break;
            
        case 4:
            PUMP = 1;
            *nextCallSeconds = 60;
            break;
           
        case 5:
            PUMP = 0;
            state++;
            return 1;
    }
    
    state++;
    return 0;
}


// return 1 when finished, should be called every 1s
char doPickUpCrap(unsigned short *nextCallSeconds)
{
    static unsigned char state = 0;
    *nextCallSeconds = 1;
    
    switch (state)
    {
        default:
            state = 0;
            bowlGoCCW();
            if (!shovelGoDown()) break;
            *nextCallSeconds = 60; 
            state++;
            break;
            
        case 1:
            if (!shovelGoUpShake()) break;
            state++;
            
        case 2:
            if (!shovelGoDown()) break;
            *nextCallSeconds = 60; 
            state++;
            break;
            
        case 3:
            if (!shovelGoUpShake()) break;
            shovelGoUp(); // release pressure
            bowlStop();
            state++;
            return 1;
    }
        
    return 0;
}

char shovelGoUpShake()
{
    static unsigned char state = 0;
    switch (state)
    {
        default:
            state = 0;
            if (!shovelGoPosition(SHOVEL_MAX_POS / 3)) return 0;
            state++;
            
        case 1:
            if (!shovelGoPosition((SHOVEL_MAX_POS / 4)*3)) return 0;
            state++; 
            
        case 2:
            if (!shovelGoPosition(SHOVEL_MAX_POS / 3)) return 0;
            state++;
            
        case 3:
            if (!shovelGoPosition((SHOVEL_MAX_POS / 4)*3)) return 0;
            state++; 
            
        case 4:
            if (!shovelGoPosition(SHOVEL_MAX_POS / 3)) return 0;
            state++;
            
        case 5:
            if (!shovelGoPosition((SHOVEL_MAX_POS / 4)*3)) return 0;
            state++; 
            
        case 6:
            if (!shovelGoPosition(0)) return 0;
            state++;
    }
    return 1;
}