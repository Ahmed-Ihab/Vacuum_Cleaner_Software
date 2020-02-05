#include "Timer.h"
#include "Main.h"
#include "Port.h"
#include "SSD.h"
#include "SW.h"
#include "Vaccum_Cleaner.h"
#include "Motor.h"


//Private Global Variables
static tByte Degree_Counter=0 ;
static Trigger_flag = 0;
static tByte Pulse=0 ;

//Public Global Variables
//tByte Motor_Counter = 0;


void Motor_Init (void)
{
    GPIO_InitPortPin(TRIGGER_PORT_Control, TRIGGER_PULSE_PIN , GPIO_OUT);
    TIMER1_Init();
}


void Motor_Update(void)
{
   // static tByte Motor_Counter = 0;


     tByte Current_Angle = 0;


    // Check if it is time for the Motor_Update to run
        /*
           Motor_Counter += TIMER_OS_TICK_MS;

            if (Motor_Counter != MOTOR_PERIOD_MS)
            {
                return;
            }
            */

   // Motor_Counter = 0 ;

    Current_Angle = Vaccum_Cleaner_Get_Speed();

    while (1)
    {

    // Reload timer1
   // TIMER1_Start(&Motor_Counter);
    TIMER1_Start();

    while(TIMER1_GET_FLAG == 0);        //Polling on the Overflow Flag of Timer !

        Degree_Counter++;

        if ( ( (Current_Angle-2) <= Degree_Counter ) && (Degree_Counter <= Current_Angle ) ) // if( (Current_Angle-2) <= Degree_Counter <= Current_Angle )

            {


               if( Pulse < GATE_PULSE_ON )
                        {

                            GPIO_WritePortPin(TRIGGER_PORT_DATA,TRIGGER_PULSE_PIN,HIGH);
                            Pulse++;
                            continue;

                        }

                        else
                        {

                            GPIO_WritePortPin(TRIGGER_PORT_DATA,TRIGGER_PULSE_PIN,LOW);
                            Pulse=0;
                            Degree_Counter=0;
                           // Motor_Counter=0;
                            return ;
                        }
                        /*
                       if (Motor_Fire_Trigger_Pulse() == 1)
                       {
                           return;

                       }

                       else  //if (Motor_Fire_Trigger_Pulse() == 0)

                       {
                           continue;
                       }

                       */
            }



            else
            {
               continue ;
            }
    }

}


tByte Motor_Fire_Trigger_Pulse (void)
{
    static tByte Pulse=0 ;

     if( Pulse < GATE_PULSE_ON )
                {

                    GPIO_WritePortPin(TRIGGER_PORT_DATA,TRIGGER_PULSE_PIN,HIGH);
                    Pulse++;
                    Trigger_flag = 0;
                    return Trigger_flag;
                   // continue;

                }

                else
                {

                    GPIO_WritePortPin(TRIGGER_PORT_DATA,TRIGGER_PULSE_PIN,LOW);
                    Pulse=0;
                    Degree_Counter=0;
                    Trigger_flag = 1;
                    return Trigger_flag;
                }
}
