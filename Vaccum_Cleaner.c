
#include "Main.h"
#include "Port.h"
#include "Timer.h"
#include "SW.h"
#include "Vaccum_Cleaner.h"
#include "SSD.h"


//#include "Display.h"




// Public Global variables Section

extern tByte Switch_Duration_Flag ;



// Private Global variables Section

static tByte Current_Speed = 0;
static tByte Target_Speed = 0;

static typed_Enum_Vaccum_Cleaner_mode Vaccum_Cleaner_mode ;
static typed_Enum_Vaccum_Cleaner_mode Vaccum_Cleaner_Display_mode ;

/*
tByte Vaccum_Cleaner_Dust= DUST_OFF;
tWord Vaccum_Cleaner_Dust_time = 0;
static tByte Vaccum_Cleaner_Dust_Flag = 0;
*/

static tByte Direction_Flag=-1 ;
static tByte Current_Flag ;

//Function Definition and Body

 void Vaccum_Cleaner_Init(void)
 {
     Vaccum_Cleaner_Display_mode = MEDIUM_MODE;
     Current_Speed = INITIAL_SPEED;
     Current_Flag = RUNNING;
     Target_Speed = MEDIUM_SPEED;


 }


 void Vaccum_Cleaner_Update(void)
{
    static tWord VC_Counter = 0;
    static tByte MODE_IN_DUST_MODE ;
    static tWord Dust_Duration = 0 ;



    /* Check if it is time for the Vaccum_Cleaner_Update to run */

    VC_Counter += TIMER_OS_TICK_MS;     // VC_Counter = Vaccum_CLeaner_Counter

    if (VC_Counter != VACCUM_ClEANER_PERIOD_MS)
    {
        return;
    }

    VC_Counter = 0;

    switch (Vaccum_Cleaner_mode)
    {

      case LOW_MODE:
        {

            if(Current_Flag == STABLE)
            {

                if (SWITCH_GetState(SWITCH_PLUS) == SWITCH_PRE_PRESSED)
                {
                       Current_Flag = RUNNING;

                       Target_Speed = MEDIUM_SPEED;
                }
            }

             if(Current_Flag == RUNNING)
            {
                Vaccum_Cleaner_Display_mode = MEDIUM_MODE;

                if(Current_Speed == Target_Speed)
                    {
                       Vaccum_Cleaner_mode = MEDIUM_MODE;
                       Current_Flag = STABLE;
                    }
                else
                {
                       Soft_Switch_increase();
                }

            }
        break;

        }


        case MEDIUM_MODE:
        {


            if(Current_Flag == STABLE)
            {

                if (SWITCH_GetState(SWITCH_PLUS) == SWITCH_PRE_PRESSED)
                {
                       Current_Flag = RUNNING;
                       Direction_Flag = INCREASING;
                       Target_Speed = HIGH_SPEED;

                }


                 if (SWITCH_GetState(SWITCH_MINUS) == SWITCH_PRE_PRESSED)
                {
                       Current_Flag = RUNNING;
                       Direction_Flag = DECREASING;
                       Target_Speed = LOW_SPEED;

                }

                  if (Switch_Duration_Flag == 1)
                   {
                         Vaccum_Cleaner_mode = DUST_MODE;
                         MODE_IN_DUST_MODE = MEDIUM_SPEED_MODE;
                          //Switch_Duration_Flag=0;
                    }

            }



            else if ( Current_Flag == RUNNING )
            {

              if(Direction_Flag==INCREASING)
                {
                        Vaccum_Cleaner_Display_mode = HIGH_MODE;
                        if(Current_Speed == Target_Speed)
                            {
                               Vaccum_Cleaner_mode = HIGH_MODE;
                                Current_Flag = STABLE ;

                            }
                        else
                        {
                               Soft_Switch_increase();
                        }

                }

             else if( Direction_Flag==DECREASING )
                {
                    Vaccum_Cleaner_Display_mode = LOW_MODE;
                        if(Current_Speed == Target_Speed)
                            {
                               Vaccum_Cleaner_mode = LOW_MODE;
                               Current_Flag = STABLE ;
                            }
                        else
                        {
                               Soft_Switch_decrease();
                        }

                }

            }

            break;

        }

        case HIGH_MODE:
        {

            if(Current_Flag == STABLE )
            {

                if (SWITCH_GetState(SWITCH_MINUS) == SWITCH_PRE_PRESSED)
                {
                       Current_Flag = RUNNING ;
                       Target_Speed = MEDIUM_SPEED;

                }

                if( Switch_Duration_Flag == 1 )
                    {
                         Vaccum_Cleaner_mode = DUST_MODE;
                         MODE_IN_DUST_MODE = HIGH_SPEED_MODE;
                         //Switch_Duration_Flag = 0;

                    }

            }

             if(Current_Flag == RUNNING )
            {
                Vaccum_Cleaner_Display_mode = MEDIUM_MODE;

                if(Current_Speed == Target_Speed)
                    {
                       Vaccum_Cleaner_mode = MEDIUM_MODE;
                       Current_Flag = STABLE ;
                    }
                else
                {
                       Soft_Switch_decrease();
                }

            }

            break;
        }


        case DUST_MODE:
        {

           switch (MODE_IN_DUST_MODE)
                    {
                        case MEDIUM_SPEED_MODE:
                        {
                                    Switch_Duration_Flag = 0;
                                    Target_Speed = LOW_SPEED;
                                    Vaccum_Cleaner_Display_mode = LOW_MODE;

                                   if (Current_Speed != Target_Speed)
                                   {
                                       Soft_Switch_decrease();


                                   }
                                    else
                                    {
                                      Vaccum_Cleaner_mode = LOW_MODE;
                                      Current_Flag = STABLE;




                                    }
                            break;

                        }

                        case HIGH_SPEED_MODE:
                        {
                                    Switch_Duration_Flag = 0;
                                    Target_Speed = MEDIUM_SPEED;
                                    Vaccum_Cleaner_Display_mode = MEDIUM_MODE;

                                   if (Current_Speed != Target_Speed)
                                   {
                                       Soft_Switch_decrease();


                                   }
                                    else
                                    {
                                      Vaccum_Cleaner_mode = MEDIUM_MODE;
                                      Current_Flag = STABLE;



                                    }

                                    break;
                        }


                        default:
                            {
                                break;
                            }

                    }

                break;

            }


        default:
        {
            break; //Do nothing
        }
  }
}


tByte Vaccum_Cleaner_Get_Speed(void)
{
    return Current_Speed ;
}


typed_Enum_Vaccum_Cleaner_mode Vaccum_Cleaner_Get_Mode (void)
{

       return Vaccum_Cleaner_Display_mode;
}


// Note= the Current speed should equal to target speed after visiting this function 50 times therefore the timing will be 80 ( vist one time function) x 50 = 4000 msec means 4 seconds


void  Soft_Switch_decrease (void)
{
     static tWord S_S_Counter_Dec =0;       // S_S_Counter_Dec = Soft_Switch_Counter_Dec

    /* Check if it is time for the Soft_Switch_decrease to run */
    S_S_Counter_Dec += TIMER_OS_TICK_MS;

    if (S_S_Counter_Dec != SOFT_SWITCH_TIME_PERIOD_MS)
    {
        return;
    }

    S_S_Counter_Dec = 0;
//    RC6 = 1 ^ RC6; // this pin is used for testing

    Current_Speed = Current_Speed + 1;
}



void  Soft_Switch_increase (void)
{
  static tWord S_S_Counter_Inc =0;   // S_S_Counter_Inc = Soft_Switch_Counter_Inc

    /* Check if it is time for the Soft_Switch_increase to run */
    S_S_Counter_Inc += TIMER_OS_TICK_MS;

    if (S_S_Counter_Inc != SOFT_SWITCH_TIME_PERIOD_MS)
    {
        return;
    }
   //  RC6 = 1 ^ RC6;  // this pin is used for testing
    S_S_Counter_Inc = 0;


    Current_Speed = Current_Speed - 1;

}
