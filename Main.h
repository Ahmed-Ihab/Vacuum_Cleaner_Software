#ifndef __MAIN_H__
#define __MAIN_H__

#include <pic16f877a.h>


/* GPIO definitions */
/* GPIO Pins */
#define GPIO_PIN_0              (0)
#define GPIO_PIN_1              (1)
#define GPIO_PIN_2              (2)
#define GPIO_PIN_3              (3)
#define GPIO_PIN_4              (4)
#define GPIO_PIN_5              (5)
#define GPIO_PIN_6              (6)
#define GPIO_PIN_7              (7)

/* GPIO Port Registers redefinition */
#define GPIO_PORTA_DATA         (PORTA)
#define GPIO_PORTA_CONTROL      (TRISA)

#define GPIO_PORTB_DATA         (PORTB)
#define GPIO_PORTB_CONTROL      (TRISB)

#define GPIO_PORTC_DATA         (PORTC)
#define GPIO_PORTC_CONTROL      (TRISC)

#define GPIO_PORTD_DATA         (PORTD)
#define GPIO_PORTD_CONTROL      (TRISD)

#define GPIO_PORTE_DATA         (PORTE)
#define GPIO_PORTE_CONTROL      (TRISE)

/* GPIO direction setting */
#define GPIO_OUT                (0)
#define GPIO_IN                 (1)

/* GPIO port operations */
#define GPIO_InitPort(CONTROL, DIRECTION)   ((CONTROL) = (DIRECTION)?(~GPIO_OUT):(GPIO_OUT))
#define GPIO_WritePort(PORT, DATA)          ((PORT) = (DATA))
#define GPIO_ReadPort(PORT)                 (PORT)

/* GPIO port pin operations */
#define GPIO_InitPortPin(CONTROL, PIN, DIRECTION)   ((CONTROL) = (CONTROL & (~(1 << PIN)))|(DIRECTION << PIN))
#define GPIO_WritePortPin(PORT, PIN, DATA)          ((PORT) = (PORT & (~(1 << PIN)))|(DATA << PIN))
#define GPIO_ReadPortPin(PORT, PIN)                 (((PORT) & (1 << PIN)) >> (PIN))
/* End of code filling */





/* Timer 0 macros */
/* Fill missing code below */

/* End of code filling */
//Configuration of TIMER0:-
//----------------------------//

#define TIMER0_SET_PRESCALER_256	PS2 = 1;\
								    PS1 = 1;\
								    PS0 = 1;\
								    PSA = 0

#define TIMER0_GET_FLAG				(TMR0IF)
#define TIMER0_CLEAR_FLAG			(TMR0IF = 0)

//preloaded Value in Timer0 Register to have delay in millisecond
#define TIMER0_UPDATE_REGISTER(TIME)		(TMR0 = 256 - ((TIME) * 8))

#define TIMER0_ENABLE_INTERRUPT	    (TMR0IE = 1)
#define GLOBAL_INTERRUPT_ENABLE	    (GIE = 1)

#define TIMER0_ENABLE_CLOCK		    (T0CS = 0)
#define TIMER0_DISABLE_CLOCK		(T0CS = 1)

//Configuration of TIMER1:-
//----------------------------//

#define TIMER1_SET_PRESCALER_1	     T1CKPS1 = 0;\
								     T1CKPS0 = 0

#define TIMER1_GET_FLAG				 (TMR1IF)
#define TIMER1_CLEAR_FLAG			 (TMR1IF = 0)

#define TIMER1_SELECT_INTERNAL_CLOCK (TMR1CS=0)

#define TIMER1_ENABLE_INTERRUPT	     TMR1IE = 1;  PEIE=1


#define GLOBAL_INTERRUPT_ENABLE	     (GIE = 1)

#define TIMER1_ENABLE_CLOCK		     (TMR1ON = 1)
#define TIMER1_DISABLE_CLOCK		 (TMR1ON = 0)


//preloaded Value in Timer1 Register to have delay in Microsecond
#define TIMER1_UPDATE_REGISTER(TIME)		do\
                                            {\
                                                if ((TIME)== 55)\
                                                {\
                                                        TMR1L = 190;\
                                                        TMR1H = 255;\
                                                }\
                                                else\
                                                {\
                                                     ( TMR1L = ( (65536 - ((TIME) * 2)) % 256 ) );\
                                                     ( TMR1H = ( (65536 - ((TIME) * 2)) / 256 ) );\
                                                }\
                                             } while(0)


/* Standard data types */
typedef unsigned char tByte;
typedef unsigned int tWord;

#endif // __MAIN_H__
