/*----------------------------------------------------------------------------
 * Name:    RTX_Blinky.h
 * Purpose: Header for RTX_Blinky.c.
 *----------------------------------------------------------------------------*/

/************* DEFINITION	*************/
/* Change thread wakeup interval */
#define CHANGE_THR_WK_INTERVAL 1000u		//1000 ms

/*Check thread wakeup interval */
#define CHECK_THR_WK_INTERVAL 10u			//10 ms

/*
Shared data:	2. variable indicating pttern to display. A uint8 memory location (volatile variable)
*/
//extern volatile static uint8_t display_pattern;		

/************* INCLUDED FILES	*************/
//#include "Board_LED.h"                  // ::Board Support:LED
//#include "Board_Buttons.h"              // ::Board Support:Buttons
#include "stm32f10x.h"                  // Device header

/************* GLOBAL VARIABLES DEFINITION	*************/

/************* DECLARATION	*************/
																
														
/*
Shared data: 3. variable indicating error state. A binary variable. (volatile variabe)
*/																
volatile static uint8_t error_state = 0u;

/************* INITIALISATION	*************/
