
#ifndef __Vaccum_Cleaner_H__
#define __Vaccum_Cleaner_H__
#include "Main.h"

//Defines Macros
#define VACCUM_ClEANER_PERIOD_MS      (20)
#define SOFT_SWITCH_TIME_PERIOD_MS    (80)

#define INITIAL_SPEED  170
#define LOW_SPEED      135
#define MEDIUM_SPEED   90
#define MID_SPEED      90
#define HIGH_SPEED     45



#define  LOW_MODE           0
#define  MEDIUM_MODE        1
#define  HIGH_MODE          2
#define  DUST_MODE          3

#define DUST_ON         1
#define DUST_OFF        0

#define STABLE          1
#define RUNNING         0

#define INCREASING      1
#define DECREASING      0


typedef enum
{
 LOW_SPEED_MODE,
 MEDIUM_SPEED_MODE,
 HIGH_SPEED_MODE,
 DUST_SENSOR_MODE

}typed_Enum_Vaccum_Cleaner_mode;



void 	 Vaccum_Cleaner_Init(void);
void	 Vaccum_Cleaner_Update(void);
tByte Vaccum_Cleaner_Get_Speed(void);
typed_Enum_Vaccum_Cleaner_mode Vaccum_Cleaner_Get_Mode (void);

void Soft_Switch_increase (void);
void Soft_Switch_decrease (void);



#endif
