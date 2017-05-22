/* 
 * File:   catgenie120.h
 * Author: Damien
 * Code refactoring
 *
 * Created on March 27, 2017, 3:15 PM
 * 
 * Originally from    
 * Robert Delien						      
 * Copyright (C) 2010, Clockwork Engineering		    
 */

#include <xc.h>


#ifndef CATGENIE120_H
#define	CATGENIE120_H

#ifdef	__cplusplus
extern "C" {
#endif

    
    
#ifdef _16F1939
/* Analog water sensor readout is NOT supported on a 16F877A */
/* On a 16F1939 it is optional */
#  define WATERSENSOR_ANALOG
#endif /* _16F1939 */

    
#define SHOVEL_SPEED_SEC    18 // time for shovel to go up or down;    
#define SHOVEL_MAX_POS (SHOVEL_SPEED_SEC*10)
#define WATER_THERSHOLD     520
#define SOAP_QTY_IN_100MS            100 // 10s = 1ml
    
#define TIMER_FREQ      195
#define DEBOUNCE        4000
    
    
/* EEPROM layout */
    // not implemented yet
#define NVM_VERSION		(0)
#define NVM_MODE		(1)
#define NVM_KEYUNDLOCK		(2)
#define NVM_BOXSTATE		(3)


/*
 * I/O Pins
 */


/* INPUT */
/* Buttons */
#define STARTBUTTON         (RB0 ? 0 : 1) 	/* Button Start/Pause */
#define SETUPBUTTON         (RB5 ? 0 : 1) /* Button Auto setup */

/* Sensors */
#define CATSENSOR_LED       LATC2
#define CATSENSOR           RB4
#define WATERSENSOR_LED     LATB2
#define WATERVALVE          RB3	/* Water sensor, directly controls Water valve (RL1) */
#define HEATSENSOR          RB1	/* Over heat detector (U4) */

   
    
/* OUTPUT */
/* Special purpose pins */
#define	UART_TXD        LATC6	
#define	UART_RXD    	LATC7
    
    
/* Indicators */
#define LED_1           LATC5
#define LED_2           LATA2 
#define LED_3           LATA3 
#define LED_4           LATA5
#define LED_ERROR       LATC0 
#define BEEPER          LATC1
#define LED_CARTRIDGE   LATE0 
#define LED_CAT         LATE1
#define LED_LOCKED      LATE2


/* Actuators */
#define WATERSENSORANALOG   RA1
#define	WATERVALVEPULLUP    LATD0
#define PUMP                LATD1
#define DRYER               LATD2
#define DOSAGE              LATD3
#define BOWL_CWCCW  		LATD4
#define BOWL_ONOFF          LATD5
#define SHOVEL_UPDOWN  		LATD6
#define SHOVEL_ONOFF   		LATD7


// output config   0b76543210
#define CONF_TRISA 0b11010011     // 1,2,3,5
#define CONF_TRISB 0b11111011     // 2
#define CONF_TRISC 0b00011000     // 0,1,5,6,7
#define CONF_TRISD 0b00000000     // all output
#define CONF_TRISE 0b11111000     // 0,1,2

    
    
    
void initHardware();

void shovelSetPinForDown();
void shovelSetPinForUp();
void shovelSetPinForStop();

void bowlGoCW();
void bowlGoCCW();
void bowlStop();

unsigned short measureWaterLevel(char doNewMeasurement);

#ifdef	__cplusplus
}
#endif

#endif	/* CATGENIE120_H */

