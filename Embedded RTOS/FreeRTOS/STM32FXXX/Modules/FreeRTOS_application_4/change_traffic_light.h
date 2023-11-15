/*----------------------------------------------------------------------------
 * Name:    change_traffic_light.h
 * Purpose: Header file for change_traffic_light.c.
 *----------------------------------------------------------------------------*/

#include "Board_LED.h"                  // ::Board Support:LED
#include "Board_Buttons.h"              // ::Board Support:Buttons
#include "stm32f10x.h"                  // Device header
//#include "checkLightData.h"	//	check light variables
#include "check_traffic_light.h"

/************* GLOBAL VARIABLES DEFINITION	*************/
/*
Shared data: 1. structure storing pattern of LED. A structure
*/
struct pattern_of_LED {
	int forward[6];
	int wait[6];
	int reverse[6];
	int off[6];
};


/************* GLOBAL VARIABLES DEFINITION	*************/

// LED macros
#define LEDR1(x)		(((x < 1)) ? (LED_Off(0)) : (LED_On(0)))
#define LEDY1(x)		(((x < 1)) ? (LED_Off(1)) : (LED_On(1)))
#define LEDG1(x)		(((x < 1)) ? (LED_Off(2)) : (LED_On(2)))
#define LEDR2(x)		(((x < 1)) ? (LED_Off(3)) : (LED_On(3)))
#define LEDY2(x)		(((x < 1)) ? (LED_Off(4)) : (LED_On(4)))
#define LEDG2(x)		(((x < 1)) ? (LED_Off(5)) : (LED_On(5)))


/************* DECLARATION	*************/


	

/************* INITIALISATION	*************/
/*
Shared data: 1. structure storing pattern of LED. A structure
*/
static struct pattern_of_LED A = {	{	0,	0,	1,	1,	0,	0	},	// { R1=Off, Y1=Off, G1=On, R2=On, Y2=Off, G2=Off }
																		{	0,	1,	0,	0,	1,	0	},	// { R1=Off, Y1=On, G1=Off, R2=Off, Y2=On, G2=Off }
																		{	1,	0,	0,	0,	0,	1	},	// { R1=On, Y1=Off, G1=Off, R2=Off, Y2=Off, G2=On }
																		{	0,	0,	0,	0,	0,	0	}	// { R1=Off, Y1=Off, G1=Off, R2=Off, Y2=Off, G2=Off }
																	};