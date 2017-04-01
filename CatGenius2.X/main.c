/* 
 * File:   main.c
 * Author: Damien
 *
 * Created on March 27, 2017, 3:43 PM
 * 
 * Based on original Catgenius project
 * Code refactored, simplified and logic redone
 * work with xc8 compiler
 */


// PIC16F1939 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection (XT Oscillator, Crystal/resonator connected between OSC1 and OSC2 pins)
#pragma config WDTE = ON        // Watchdog Timer Enable (WDT enabled)
#pragma config PWRTE = OFF       // Power-up Timer Enable (PWRT enabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable (All VCAP pin functionality is disabled)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = HI        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), high trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#include "catgenie120.h"
#include "process.h"
#include "tasks.h"
#include "businesslogic.h"

void initTimer();

unsigned char timer100ms=0;
unsigned char timerSec=0;
unsigned char timerMin=0;
unsigned char timerHour=0;

int main(int argc, char** argv) 
{
    initHardware();
    initTimer();
    beep();
    
    nPOR = 1;
	nBOR = 1;

    while (1)
    {
        doSubTasks();
        CLRWDT();
    }
    return (EXIT_SUCCESS);
}



void processTimers()
{
    static char timer50ms=0;
    
    timer50ms++;
    
    if (timer50ms == 2)
    {
        timer50ms = 0;
        
        doTimedTasks();
        doBusinessLogicTask();
    
        timer100ms++;
    };


    if (timer100ms == 10)
    {
        timer100ms = 0;
        doProcess();

        timerSec++;
    }
        
    if (timerSec == 60)
    {
        timerSec = 0;
        timerMin++;
    }
    
    if (timerMin == 60)
    {
        timerMin = 0;
        
        hourInterrupt(timerHour);
        
        timerHour++;
    }
    
    if (timerHour == 24)
    {
        timerHour = 0;
    }
}


void interrupt Timer0_ISR()
{
    if(TMR0IF && TMR0IE) 
    {                                     // if timer flag is set & interrupt enabled
        TMR0 -= TIMER_FREQ;               // reload the timer - 250uS per interrupt
        TMR0IF = 0;                  // clear the interrupt flag 
        
        processTimers();
    }
}


void initTimer()
{
	/* Select Fosc/4 as source */
	TMR0CS = 0;
    
	/* Set prescaler to 1:8 */
    PSA = 0;
    OPTION_REGbits.PS = 0b111;

	/* Disable timer 1 external oscillator */
	T1OSCEN = 0;
	/* Disable synchronized clock */
	nT1SYNC = 1;
    
    TMR0 -= TIMER_FREQ;
	/* Switch on timer 1 */

	/* Enable timer 1 interrupt */
    TMR0IF = 0;
	TMR0IE = 1;
}

