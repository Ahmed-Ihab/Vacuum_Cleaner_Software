

#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "Main.h"
#include "Port.h"



#define ONE_DEGREE_TIME    (55)

#define MOTOR_PERIOD_MS    (10)


#define GATE_PULSE_ON      (2)

#define TRIGGER_PORT_Control    (TRISC)
#define TRIGGER_PORT_DATA       (PORTC)
#define TRIGGER_PULSE_PIN          (1)


// Prototype of the Public Function

void Motor_Init (void);
void Motor_Update (void);
tByte Motor_Fire_Trigger_Pulse (void);


#endif // __MOTOR_H__
