/*----------------------------------------------------------------------------
 * Name:    change_traffic_light.c
 * Purpose: File for function to check error adc values of current traffic light pattern.
 *----------------------------------------------------------------------------*/

//#include "lightData.h"		// traffic light application variables
//#include "checkLightData.h"	//	check light variables
#include "check_traffic_light.h"
//#include "changeLightData.h"	//change light data variables
//#include "RTX_Blinky.h"
//extern static volatile int32_t adcR1, adcY1, adcG1, adcR2, adcY2, adcG2;

//extern volatile static uint8_t display_pattern;

void check_ADC_error(uint8_t *display_pattern1){
	
/**** check ADC ****/
	if (*display_pattern1 == 0u)	// forward
	{
		//check ADC of G1 and R2
		if ((adcG1 > greHi) | (adcG1 < greLo)){	
			errG1 = errG1 + 1;	//errG1++;
	}
		if ((adcR2 > redHi) | (adcR2 < redLo)){
			errR2 = errR2 + 1;
		}
	}
	
	if (*display_pattern1 == 1u)	// wait
	{
		if ((adcY1 > yelHi) | (adcY1 < yelLo)){
			errY1 = errY1+1;
		}
		if ((adcY2 > yelHi) | (adcY2 < yelLo)){
			errY2 = errY2+1;
		}
	}
	
	if (*display_pattern1 == 2u)	// reverse
	{
		//check ADC of G2 and R1
		if ((adcG2 > greHi) | (adcG2 < greLo)){	
			errG2 = errG2+1;
	}
		if ((adcR1 > redHi) | (adcR1 < redLo)){
			errR1 = errR1+1;
		}
	}

		
	//TODO: Set LED pattern
	
}