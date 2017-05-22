
#include "catgenie120.h"



void initWaterSensor();

// Functions
void initHardware()
{
    // enable interrupt
    GIE = 1;
    
    // disable analog input
    ANSELA = 0;
    ANSELB = 0;
    //ANSELB = 0b00001000; // for analog input on water level sensor
    
    ANSELD = 0;
    ANSELE = 0;
    
    // pull up resistors
    nWPUEN = 0;
    WPUB = ~(0 | (1 << 3)); /* Enable pull-up resitors on all pins individually, except for WATERVALVE */
	WPUE = 0x00;
    
    // reset all pins
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;
    LATD = 0x00;
    LATE = 0x00;
            
    // setup pin direction
    TRISA = CONF_TRISA;
    TRISB = CONF_TRISB;
    TRISC = CONF_TRISC;
    TRISD = CONF_TRISD;
    TRISE = CONF_TRISE;
    
    
    PUMP = 0;
    DRYER = 0;
    DOSAGE = 0;
    WATERVALVEPULLUP = 0;

    shovelSetPinForStop();
    bowlStop();
    
    // disabled initWaterSensor();
}

// disabled for now, not tested as digital version works fine
/*
void initWaterSensor() // by R. Delien, refactored Damien
{
	// Power-up AD circuitry 
	ADCON0bits.ADON = 1;
	// Select input channel 
	ADCON0bits.CHS = 9;

	// Set output format to right-justified data 
	ADCON1bits.ADFM = 1;
	// Set conversion clock to internal RC oscillator 
	ADCON1bits.ADCS = 7;

	// Set negative reference to Vss, positive reference to Vdd 
	ADCON1bits.ADNREF = 0;
	ADCON1bits.ADPREF = 0;
}


#define PROCESS_RESULT   1

unsigned short measureWaterLevel(char doNewMeasurement)
{
    static unsigned short result=0;
    static char state=0;
    
	switch (state) 
    {
        default:
            WATERSENSOR_LED = 0;
            if (doNewMeasurement)
            {
                WATERSENSOR_LED = 1;
                ADCON0bits.GO = 1;
                state = PROCESS_RESULT;
            }
            break;
            

        case PROCESS_RESULT:
            if (ADCON0bits.nDONE)
                break;
                    
            // Read out the IR sensor analoguely (lower value == more light reflected == no water detected) 
            result = ADRES;
            state = 0;
	}
    
    return result;
}
*/
void shovelSetPinForUp()
{
    SHOVEL_ONOFF = 1;
    SHOVEL_UPDOWN = 0;  
}
void shovelSetPinForDown()
{
    SHOVEL_ONOFF = 1;
    SHOVEL_UPDOWN = 1;
}
void shovelSetPinForStop()
{
    SHOVEL_ONOFF = 0;
}

void bowlGoCW()
{
    BOWL_CWCCW = 1;
    BOWL_ONOFF = 1;
}
void bowlGoCCW()
{
    BOWL_CWCCW = 0;
    BOWL_ONOFF = 1;
}

void bowlStop()
{
    BOWL_ONOFF = 0;
}




