#ifndef __LED_H__
#define __LED_H__

#define LED_DUST_MODE (0)

typedef enum
{
    LED_1,
    LED_2,
    LED_3,
    LED_4
}tLED;

typedef enum
{
   LED_OFF = 0,
   LED_ON  = 1
}tLED_State;


void LED_Init(tLED led, tLED_State state);
void LED_SetState(tLED led, tLED_State state);
tLED_State LED_GetState(tLED led);
void LED_Toggle(tLED led);

#endif // __LED_H__
