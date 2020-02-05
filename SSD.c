#include "Main.h"
#include "Port.h"
#include "Timer.h"
#include "SSD.h"
#include "Vaccum_Cleaner.h"
#include "Led.h"




/* SSD Symbols port data values */               //look up table for SSD
static tByte SSD_Data[N_SSD_SYMBOLS] =
{

    0b00001000,  //low speed (lower dash)
    0b01001000,  // mid speed ( lower and mid dash )
    0b01001001,  //high speed (Lower and mid and upper dash)
    0b00000000  //Null mode

};

//Private Global Variables for SSD

/* Current SSD to be updated */
static type_Enum_SSD_Selection SSD_current = SSD_LOW_SPEED ;  // initial SSD to be updated

/* SSD values */
static type_Enum_SSD_Symbol SSD_Values[N_SSD] ;    // create an array from enum tSSD_Symbol and have N_SSD elements and initialized them with SSD_NULL

//Private Functions for SSD

static void SSD_Out(type_Enum_SSD_Selection ssd, type_Enum_SSD_Symbol ssd_symbol);


void Display_Init (void)
{
    SSD_Init(SSD_HIGH_SPEED);
    SSD_Init(SSD_MID_SPEED);
    SSD_Init(SSD_LOW_SPEED);

    GPIO_InitPort(SSD_DATA_PORT_CR,GPIO_OUT);

     LED_Init(LED_DUST_MODE, LED_OFF);
}

void SSD_Init(type_Enum_SSD_Selection ssd)
{

    // Initialize SSD data pins


    switch (ssd)
    {

        case SSD_LOW_SPEED:
        {
            GPIO_InitPortPin(SSD_LOW_SPEED_CR,SSD_LOW_SPEED_PIN,GPIO_OUT);

            break;
        }

        case SSD_HIGH_SPEED:
        {
            GPIO_InitPortPin(SSD_HIGH_SPEED_CR,SSD_HIGH_SPEED_PIN,GPIO_OUT);
            break;
        }


          default:              //default case is the SSD_MID_SPEED
        {
            GPIO_InitPortPin(SSD_MID_SPEED_CR,SSD_MID_SPEED_PIN,GPIO_OUT);
            break;
        }

    }

    //SSD_Out(ssd , SSD_NULL);
    // Initialize SSD control pin and turn SSD OFF


}


void SSD_Update(void)
{
    static tWord SSD_counter = 0;
    static tByte SSD_Traverse = SSD_LOW_SPEED;
    static SSD_Previous_Current = SSD_NULL_SPEED ;
   // static tByte Dust_mode_flag = 0;

    /* Check if it is time for the SSD_Update to run */
     SSD_counter += TIMER_OS_TICK_MS;

    if (SSD_counter != SSD_PERIOD_MS)
    {
        return;
    }

    SSD_counter = 0;


    SSD_current = Vaccum_Cleaner_Get_Mode();


    switch (SSD_current)
    {
        case SSD_HIGH_SPEED :
        {
            switch (SSD_Traverse)
                    {
                        case SSD_LOW_SPEED :
                        {
                           SSD_SetValue(SSD_Traverse ,SSD_LOWER_DASH);
                           SSD_Out(SSD_Traverse, SSD_Values[SSD_Traverse]);

                            SSD_Traverse = SSD_MID_SPEED;
                            break;

                        }

                         case SSD_MID_SPEED :
                        {
                            SSD_SetValue(SSD_Traverse ,SSD_LOWER_MID_DASH);
                            SSD_Out(SSD_Traverse, SSD_Values[SSD_Traverse]);
                            SSD_Traverse = SSD_HIGH_SPEED;
                            break;

                        }

                         case SSD_HIGH_SPEED :
                        {
                            SSD_SetValue(SSD_Traverse ,SSD_LOWER_MID_UPPER_DASH);
                            SSD_Out(SSD_Traverse, SSD_Values[SSD_Traverse]);

                            SSD_Traverse = SSD_LOW_SPEED;
                            break;

                        }

                    }

                    break;

        }

         case SSD_MID_SPEED :
        {
                switch (SSD_Traverse)
                    {
                        case SSD_LOW_SPEED :
                        {
                            SSD_SetValue(SSD_Traverse ,SSD_LOWER_DASH);
                            SSD_Out(SSD_Traverse, SSD_Values[SSD_Traverse]);
                            SSD_Traverse = SSD_MID_SPEED;
                            break;

                        }

                         case SSD_MID_SPEED :
                        {
                            SSD_SetValue(SSD_Traverse ,SSD_LOWER_MID_DASH);
                            SSD_Out(SSD_Traverse, SSD_Values[SSD_Traverse]);
                            SSD_Traverse = SSD_LOW_SPEED;
                            break;

                        }

                    }

                    break;
        }



         case SSD_LOW_SPEED :

        {
            SSD_SetValue(SSD_current ,SSD_LOWER_DASH);
            SSD_Out(SSD_current, SSD_Values[SSD_current]);
            break;
        }


         default:
        {
            break;
        }
    }



    // This section is used to test each SSD individually
/*
    switch (SSD_current)
    {
        case SSD_HIGH_SPEED :
        {
                 SSD_SetValue(SSD_current ,SSD_LOWER_MID_UPPER_DASH);
                 SSD_Out(SSD_current, SSD_Values[SSD_current]);
            break;

        }

         case SSD_MID_SPEED :
        {
                SSD_SetValue(SSD_current ,SSD_LOWER_MID_DASH);
                SSD_Out(SSD_current, SSD_Values[SSD_current]);
            break;
        }

         case SSD_LOW_SPEED :
        {
            SSD_SetValue(SSD_current ,SSD_LOWER_DASH);
            SSD_Out(SSD_current, SSD_Values[SSD_current]);
            break;
        }
    }
*/

}







type_Enum_SSD_Symbol SSD_GetValue(type_Enum_SSD_Selection ssd)
{
        return SSD_Values[ssd] ;
}






type_Enum_SSD_State SSD_GetState(type_Enum_SSD_Selection ssd)
{
    type_Enum_SSD_State ret = SSD_OFF;

    switch (ssd)
    {
        case SSD_LOW_SPEED :
        {
            ret = GPIO_ReadPortPin(SSD_LOW_SPEED_DR,SSD_LOW_SPEED_PIN);
            break ;
        }

       case SSD_MID_SPEED :
        {
            ret = GPIO_ReadPortPin(SSD_MID_SPEED_DR,SSD_MID_SPEED_PIN);
            break ;
        }

       case SSD_HIGH_SPEED :
        {
            ret = GPIO_ReadPortPin(SSD_HIGH_SPEED_DR,SSD_HIGH_SPEED_PIN);
            break ;
        }

         default:
        {
            break;
        }

    }
    /* End of your code!*/
    return ret;

}

void SSD_SetState(type_Enum_SSD_Selection ssd, type_Enum_SSD_State state)
{
    switch (ssd)
    {
        case SSD_LOW_SPEED:
        {
            GPIO_WritePortPin(SSD_LOW_SPEED_DR ,SSD_LOW_SPEED_PIN , state  );

            break;
        }

        case SSD_MID_SPEED:
        {
           GPIO_WritePortPin(SSD_MID_SPEED_DR ,SSD_MID_SPEED_PIN , state  );

            break;
        }

       case SSD_HIGH_SPEED:
        {
            GPIO_WritePortPin(SSD_HIGH_SPEED_DR ,SSD_HIGH_SPEED_PIN , state  );

            break;
        }



        default:
        {
            break;
        }

    }

}







void SSD_SetValue(type_Enum_SSD_Selection ssd, type_Enum_SSD_Symbol ssd_symbol)
{
    SSD_Values[ssd]= ssd_symbol ;
}


static  void SSD_Out(type_Enum_SSD_Selection ssd, type_Enum_SSD_Symbol ssd_symbol)
{

    /* Turn off SSDs */

    SSD_SetState(SSD_HIGH_SPEED,SSD_OFF);
    SSD_SetState(SSD_MID_SPEED, SSD_OFF);
    SSD_SetState(SSD_LOW_SPEED, SSD_OFF);

    /* Output ssd_symbol on selected ssd */

    GPIO_WritePort(SSD_DATA_PORT_DR , SSD_Data[ssd_symbol]);

    /* Turn ssd ON */
    SSD_SetState(ssd , SSD_ON);
    /* End of your code!*/

}
