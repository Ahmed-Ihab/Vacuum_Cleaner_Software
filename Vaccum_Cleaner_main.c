
#include "Timer.h"
#include "Main.h"
#include "Port.h"
#include "SSD.h"
#include "SW.h"
#include "Vaccum_Cleaner.h"
#include "Motor.h"
#include "Led.h"


/*

#include "Display.h"

*/

tWord __at(0x2007) CONFIG = _HS_OSC & _WDT_OFF & _PWRTE_ON & _BODEN_OFF & _LVP_OFF & _CPD_OFF & _WRT_OFF & _DEBUG_OFF & _CP_OFF;

extern tByte Schdule_Running_FLag;


void main(void)
{


    // Run Initialization of Functions of each Module

    TESTING_PORT_Control = GPIO_OUT;        // this command is used to make PORT C as an OUTPUT for testing

    Display_Init ();
    SWITCH_Init();
    Vaccum_Cleaner_Init();
    Motor_Init();


    TIMER0_Init();
    TIMER0_Start();


    while(1)
    {



        if(Schdule_Running_FLag==1)
        {

             // Run Updates Functions of each Module
             //Note the Running updates function should be less than 10 ms which means to make sure that the Degree_Counter less than 182


                SSD_Update();
                Motor_Update();
                SWITCH_Update();
                Vaccum_Cleaner_Update();


                Schdule_Running_FLag = 0;

        }


    }

}

