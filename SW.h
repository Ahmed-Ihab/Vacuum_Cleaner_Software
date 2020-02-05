#ifndef __SW_H__
#define __SW_H__

#define SWITCH_PRESSED_TIME_PERIOD_MS (3000)

/* SWITCH_Update period */
#define SWITCH_PERIOD_MS   (20)

typedef enum
{
    SWITCH_PLUS,
    SWITCH_MINUS,
    SWITCH_DUST
}type_Enum_SWITCH_Selection;

typedef enum
{
    SWITCH_RELEASED,
    SWITCH_PRE_PRESSED,
    SWITCH_PRESSED,
    SWITCH_PRE_RELEASED
}type_Enum_SWITCH_State;

void SWITCH_Init(void);
type_Enum_SWITCH_State SWITCH_GetState(type_Enum_SWITCH_Selection );
void SWITCH_Update(void);
//tByte Switch_Calculate_Pressed_time (void);
void Switch_Cal_time (type_Enum_SWITCH_Selection );
//tByte Switch_Cal_time (void);

#endif // __SW_H__
