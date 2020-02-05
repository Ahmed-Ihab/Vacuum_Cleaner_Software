#ifndef __TIMER_H__
#define __TIMER_H__
#include "Main.h"
#include "Port.h"

#define TIMER_INTERRUPT_ENABLE	    /* 0 --> Interrupts disabled */
									/* 1 --> Interrupts enabled */

#define TIMER_OS_TICK_MS		(10) /* HCF(P1, P2, ..., PN) */
//#define ONE_DEGREE_TIME         (55)
#define TIMER_0_ON              (182)

#define HIGH                    (1)
#define LOW                     (0)

//i used this pins for testing the output of each pulse
#define TESTING_PORT_Control    (TRISC)
#define TESTING_PORT_DATA       (PORTC)

#define Timer_OS_TICK_PORT_CONTROL  (TRISC)
#define Timer_OS_TICK_PORT_DATA     (PORTC)

#define TIMER_OS_TICK_PIN       (2)



void TIMER0_Init(void);
void TIMER0_Start(void);
tByte TIMER0_CheckOverFlow(void);
void TIMER0_Stop(void);

void TIMER1_Init(void);
//void TIMER1_Start(tByte *);
void TIMER1_Start(void);
tByte TIMER1_CheckOverFlow(void);
void TIMER1_Stop(void);


//void TIMER_Update(void) __interrupt 1; // ISR @  vector 1
void TIMER_Update(void) __interrupt 0;  // This function Interrupt is used to run the OS which run the Update functions in each Module

#endif
