#include "Timer.h"
#include "Main.h"
#include "Port.h"
#include "SSD.h"
#include "SW.h"
#include "Vaccum_Cleaner.h"
#include "Motor.h"

/*

#include "Display.h"

*/



// Public_Global_Variables Section
tByte Schdule_Running_FLag = 0;

//extern tByte Motor_Counter;


void TIMER0_Init(void)
{
    GPIO_InitPortPin(Timer_OS_TICK_PORT_CONTROL , TIMER_OS_TICK_PIN , GPIO_OUT);
	TIMER0_SET_PRESCALER_256;
	TIMER0_DISABLE_CLOCK;

}

void TIMER0_Start(void)
{
	TIMER0_CLEAR_FLAG;
    TIMER0_UPDATE_REGISTER(TIMER_OS_TICK_MS);
    TIMER0_ENABLE_INTERRUPT;
	GLOBAL_INTERRUPT_ENABLE;
	TIMER0_ENABLE_CLOCK;
}

tByte TIMER0_CheckOverFlow(void)
{
	return TIMER0_GET_FLAG;
}

void TIMER0_Stop(void)
{
	/* Add your code here! */
	TIMER0_DISABLE_CLOCK;
	/* End of your code!*/
}

//-------------------------------------------------------//

void TIMER1_Init(void)
{
	/* Add your code here! */
	TIMER1_SET_PRESCALER_1;
    TIMER1_SELECT_INTERNAL_CLOCK;
    TIMER1_DISABLE_CLOCK;

	//TRISC=0x00;
	//RC0=0;
	/* End of your code!*/
}

void TIMER1_Start(void)
{

    TIMER1_DISABLE_CLOCK;
	TIMER1_CLEAR_FLAG;

    TIMER1_UPDATE_REGISTER(ONE_DEGREE_TIME);
	/*
	if(*Motor_Counter == 10)
    {
      TIMER1_UPDATE_REGISTER(ONE_DEGREE_TIME);
      RC5^=1;
    }

    else if(*Motor_Counter == 20)
    {
     TMR1L = 220;
     TMR1H = 255;
     *Motor_Counter=0;
    }
    */

    //GLOBAL_INTERRUPT_ENABLE;
    //TIMER1_ENABLE_INTERRUPT;

	TIMER1_ENABLE_CLOCK;

}

tByte TIMER1_CheckOverFlow(void)
{

	return TIMER1_GET_FLAG;

}

void TIMER1_Stop(void)
{

	TIMER1_DISABLE_CLOCK;

}


// This below function Interrupt is used to run the OS which run the Update functions in each Module

void TIMER_Update(void) __interrupt 0
{
      static tByte TIMER_OS_TICK_PIN_value=HIGH ;

    /* Reload timer0 */
	TIMER0_CLEAR_FLAG;
	TIMER0_UPDATE_REGISTER(TIMER_OS_TICK_MS);

    Schdule_Running_FLag=1;

    GPIO_WritePortPin(Timer_OS_TICK_PORT_DATA,TIMER_OS_TICK_PIN,TIMER_OS_TICK_PIN_value);

    TIMER_OS_TICK_PIN_value = 1 ^ TIMER_OS_TICK_PIN_value ;

    /*
          SSD_Update();
          SWITCH_Update();
          Vaccum_Cleaner_Update();
          Motor_Update();
    */

}
