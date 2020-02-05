#ifndef __SDD_H__
#define __SDD_H__

#include "Main.h"
#include "Port.h"
#define SSD_NULL_SPEED (-1)
#define SSD_LOW_SPEED  (0)
#define SSD_MID_SPEED  (1)
#define SSD_HIGH_SPEED (2)

/* Number of SSDs */
#define N_SSD           (3)


/* SSD_Update period */
#define SSD_PERIOD_MS   (10)

/* Number of SSD symbols */
#define N_SSD_SYMBOLS   (3)





typedef enum
{
  	SSD_LOW_SPEED_MODE = 0,
    SSD_MID_SPEED_MODE,
	SSD_HIGH_SPEED_MODE
}type_Enum_SSD_Selection;


/* SSD states */
typedef enum
{
    SSD_OFF = 0,
    SSD_ON
}type_Enum_SSD_State;

/* SSD symbols */
typedef enum
{
    SSD_LOWER_DASH = 0,
    SSD_LOWER_MID_DASH,
    SSD_LOWER_MID_UPPER_DASH,
    SSD_NULL

}type_Enum_SSD_Symbol;


void Display_Init(void);


void SSD_Init(type_Enum_SSD_Selection);
void SSD_Update(void);
void SSD_SetValue(type_Enum_SSD_Selection ssd, type_Enum_SSD_Symbol ssd_symbol);
type_Enum_SSD_Symbol SSD_GetValue(type_Enum_SSD_Selection ssd);
type_Enum_SSD_State SSD_GetState(type_Enum_SSD_Selection ssd);
void SSD_SetState(type_Enum_SSD_Selection ssd, type_Enum_SSD_State state);
void SSD_SetDotState(tByte state);


#endif // __SDD_H__
