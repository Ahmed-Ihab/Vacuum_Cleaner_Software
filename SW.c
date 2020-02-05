#include "Main.h"
#include "Port.h"
#include "Timer.h"
#include "SW.h"



/* Number of samples per SW */
#define N_SAMPLES      (2)

#define N_SWITCHES      (3)

/* SW voltage level */
#define SWITCH_PRESSED_LEVEL        (0)
#define SWITCH_RELEASED_LEVEL       (1)


tByte Switch_Duration_Flag = 0;

/* Switch info: samples, state */

//Declaration and Definition of Structure
typedef struct
{
    tByte SWITCH_samples[N_SAMPLES];
    type_Enum_SWITCH_State SWITCH_state;
}type_Struct_Switch_Info;


/* Switch info */

//Static Global Variables Sections
static type_Struct_Switch_Info Switch_Info[N_SWITCHES];

//Definition and body of Functions
void SWITCH_Init(void)
{
    tByte index = 0;

    /* Add your code here! */
    /* Initialize switches as inputs */
    // Make all the Switches Pin as input Pins
    GPIO_InitPortPin(SWITCH_PLUS_PORT_CR, SWITCH_PLUS_PIN, GPIO_IN);
    GPIO_InitPortPin(SWITCH_MINUS_PORT_CR, SWITCH_MINUS_PIN, GPIO_IN);
    GPIO_InitPortPin(SWITCH_DUST_PORT_CR, SWITCH_DUST_PIN, GPIO_IN);

    // initialize All the Switches States in the beginning as Switch Released
    /* Initialize switches info */
    for (index = SWITCH_PLUS; index < N_SWITCHES; index++)
    {
        /* Initialize switch samples */
        Switch_Info[index].SWITCH_samples[0] = SWITCH_RELEASED_LEVEL;
        Switch_Info[index].SWITCH_samples[1] = SWITCH_RELEASED_LEVEL;

        /* Initialize sw state */
        Switch_Info[index].SWITCH_state = SWITCH_RELEASED;

    }
    /* End of your code!*/
}


type_Enum_SWITCH_State SWITCH_GetState(type_Enum_SWITCH_Selection Switch)
{
    /* Add your code here! */
    /* return SWITCH state */
    return Switch_Info[Switch].SWITCH_state;
    /* End of your code!*/
}


void SWITCH_Update(void)
{
    static tWord SWITCH_counter = 0;
    tByte index = 0;

    /* Check if it is time for the SWITCH_Update to run */
    SWITCH_counter += TIMER_OS_TICK_MS;

    if (SWITCH_counter != SWITCH_PERIOD_MS)
        {
        return;
        }

    SWITCH_counter = 0;

    /* Update switches states */
    for (index = SWITCH_PLUS; index < N_SWITCHES; index++)
    {
        /* Add your code here! */
        /* Update and take Switch samples */
        Switch_Info[index].SWITCH_samples[0] = Switch_Info[index].SWITCH_samples[1];


        if (index == SWITCH_PLUS)
        {
            Switch_Info[index].SWITCH_samples[1] = GPIO_ReadPortPin(SWITCH_PLUS_PORT_DR, SWITCH_PLUS_PIN);
        }
        else if (index == SWITCH_MINUS)
        {
            Switch_Info[index].SWITCH_samples[1] = GPIO_ReadPortPin(SWITCH_MINUS_PORT_DR, SWITCH_MINUS_PIN);
        }
        else if (index == SWITCH_DUST)
        {
            Switch_Info[index].SWITCH_samples[1] = GPIO_ReadPortPin(SWITCH_DUST_PORT_DR, SWITCH_DUST_PIN);
        }
        else
        {
            /* Do nothing should not be here !! */
        }

        /* After Taking Switch Samples, Update Switch state */

        switch(Switch_Info[index].SWITCH_state)
        {

            case SWITCH_RELEASED:
                /* Go to pre-pressed state if needed */
                if ((Switch_Info[index].SWITCH_samples[0] == SWITCH_PRESSED_LEVEL) &&
                    (Switch_Info[index].SWITCH_samples[1] == SWITCH_PRESSED_LEVEL))
                {
                    Switch_Info[index].SWITCH_state = SWITCH_PRE_PRESSED;
                }
                else
                {
                    /* Do nothing */
                }
                break;
            case SWITCH_PRE_PRESSED:
                /* Go to pressed state if needed  */
                if (Switch_Info[index].SWITCH_samples[1] == SWITCH_PRESSED_LEVEL)
                {
                    Switch_Info[index].SWITCH_state = SWITCH_PRESSED;
                }

                else
                {
                    /* Do nothing */
                }
                break;
            case SWITCH_PRESSED:
                /* Go to pre-released state if needed */
                if ((Switch_Info[index].SWITCH_samples[0] == SWITCH_RELEASED_LEVEL) &&
                    (Switch_Info[index].SWITCH_samples[1] == SWITCH_RELEASED_LEVEL))
                {
                    Switch_Info[index].SWITCH_state = SWITCH_PRE_RELEASED;
                }
                else
                {
                    /* Do nothing */
                }
                break;
            case SWITCH_PRE_RELEASED:
                /* Go to released state if needed */
                if (Switch_Info[index].SWITCH_samples[1] == SWITCH_RELEASED_LEVEL)
                {
                    Switch_Info[index].SWITCH_state = SWITCH_RELEASED;
                } else
                {
                    /* Do nothing */
                }
                break;
            /* Should not be here */
            default:
                break;
        }
    }

        Switch_Cal_time ( SWITCH_DUST);
}


 void Switch_Cal_time (type_Enum_SWITCH_Selection Switch)       //Switch_Calculate_Press_time_Function
{
    static tWord Switch_Duration_Cal=0;         //Switch_Duration_Cal = Switch_Duration_Calculate_Pressed_Time

    if (SWITCH_GetState(Switch) == SWITCH_PRESSED)
    {
        Switch_Duration_Cal += SWITCH_PERIOD_MS;

        //if( ( Switch_Duration == SWITCH_PRESSED_TIME_PERIOD_MS ) && (Switch_Duration_Flag == 0) )
        if( Switch_Duration_Cal == SWITCH_PRESSED_TIME_PERIOD_MS )
        {
            Switch_Duration_Flag = 1 ;
            Switch_Duration_Cal = 0 ;
            return ;
        }

        return ;
    }

    else
        {
            Switch_Duration_Cal = 0 ;
            return ;
        }
}

/*
tByte Switch_Cal_time ()
{
     tWord Switch_pressed_time = 0;

    static tWord Pressed_time = 0;  //Pressed_time = Switch_counter_Pressed_time

        RC6^=1;  //test pin

       Pressed_time += SWITCH_PERIOD_MS;

        if (Pressed_time != SWITCH_PRESSED_TIME_PERIOD_MS)
            {
            return 0;
            }
        Switch_pressed_time = Pressed_time;
        Pressed_time = 0;

        return Switch_pressed_time ;


}
*/
