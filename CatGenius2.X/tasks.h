/* 
 * File:   tasks.h
 * Author: Damien
 *
 * Created on March 28, 2017, 10:31 AM
 */

#ifndef TASKS_H
#define	TASKS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define SHOVELGOUP      1
#define SHOVELGODOWN    2



void beep();
void beepFor(unsigned long timePer100Ms);

/* doTimedTasks needs to be called every 100ms
 */
void doTimedTasks();

/* doSubTasks needs to be called periodically 
 */
void doSubTasks();

void shovelStop();
char shovelGoDown();
char shovelGoUp();
char shovelGoPosition(unsigned short position);
void waterFill(); 
void waterStop();
void addSoap();
unsigned char isCatPresent();

#ifdef	__cplusplus
}
#endif

#endif	/* TASKS_H */

