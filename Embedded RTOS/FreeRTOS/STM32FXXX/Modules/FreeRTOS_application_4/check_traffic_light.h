/*----------------------------------------------------------------------------
 * Name:    check_traffic_light.h
 * Purpose: Header file for check_traffic_light.c.
 *----------------------------------------------------------------------------*/

/* LED operating voltage threshold */
#define redLo	100
#define yelLo	70
#define greLo	50
#define redHi		2500
#define yelHi		2700
#define greHi		3000

#define NB_OF_LEDS	6

#include "stm32f10x.h"                  // Device header

//#include "lightData.h"		// traffic light application variables

//#include "Board_LED.h"                  // ::Board Support:LED
//#include "Board_Buttons.h"              // ::Board Support:Buttons

static int8_t errArray[NB_OF_LEDS];	//errR1, errY1, errG1, errR2, errY2, errG2;

/************* INLINE DEFINITIONS	*************/
#define errR1 errArray[0]
#define errY1 errArray[1]
#define errG1 errArray[2]
#define errR2 errArray[3]
#define errY2 errArray[4]
#define errG2 errArray[NB_OF_LEDS-1]

/************* DECLARATION	*************/

/* Variables to store adc values of different lights */
static volatile int32_t adcR1, adcY1, adcG1, adcR2, adcY2, adcG2;

/* 
	Variable indicating pttern to display. A uint8 memory location (volatile variable)
*/
//extern volatile static uint8_t display_pattern;


