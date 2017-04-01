/* 
 * File:   process.h
 * Author: Damien
 *
 * Created on March 27, 2017, 3:49 PM
 */

#ifndef PROCESS_H
#define	PROCESS_H

#ifdef	__cplusplus
extern "C" {
#endif

    
/* Times */
#define MAX_FILLTIME		((2*60+15)*SECOND)
#define MAX_DRAINTIME		((0*60+10)*SECOND)


void doFullClean();
void doCrapPick();


/**
 * doProcess function needs to be called every 1s
 */
void doProcess();


#ifdef	__cplusplus
}
#endif

#endif	/* PROCESS_H */

