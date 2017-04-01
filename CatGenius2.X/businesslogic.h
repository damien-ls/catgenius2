/* 
 * File:   businesslogic.h
 * Author: Damien
 *
 * Created on March 28, 2017, 4:16 PM
 */

#ifndef BUSINESSLOGIC_H
#define	BUSINESSLOGIC_H

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * doBusinessLogicTask() handles timed task and needs to be called 
 * every 100ms 
 */
void doBusinessLogicTask();
    
void onStartPressed();
void onSetupPressed();

void hourInterrupt(unsigned char hour);

#ifdef	__cplusplus
}
#endif

#endif	/* BUSINESSLOGIC_H */

