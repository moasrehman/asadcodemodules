/*----------------------------------------------------------------------------
 * Name:    change_traffic_light.c
 * Purpose: File for function to set and display traffic light pattern.
 *----------------------------------------------------------------------------*/

#include "stm32f10x.h"                  // Device header
//#include "lightData.h"		// traffic light application variables
//#include "changeLightData.h"	//change light data variables
#include "change_traffic_light.h"
//#include "checkLightData.h"	//	check light variables
//#include "RTX_Blinky.h"

#define magicErrorCountValue 10	

//extern volatile static uint8_t *display_pattern;

//Read error and set display pattern
uint8_t read_error_and_set_pattern(uint8_t *display_pattern)//(void)
{
	int8_t locerrorArray[NB_OF_LEDS];
	uint64_t bigErrorVariable = 0;
	
	for (int i = 0; i< NB_OF_LEDS; i++)
	{
		//read error status
		locerrorArray[i] = errArray[i];
		
		//reset error message
		errArray[i] = 0;
		
		//accuulate error
		bigErrorVariable = bigErrorVariable + locerrorArray[i];
		
	}
	
	//change display pattern varable as per error
	if (bigErrorVariable >= magicErrorCountValue)
	{
		if (*display_pattern == 1u)
		{
			*display_pattern = 3u;
		}else if (*display_pattern == 3u)
		{
			*display_pattern = 1u;
		}else 
		{
			*display_pattern = 1u;
		}
	}
	else //no error
	{
		*display_pattern++;
		
		if (*display_pattern >= 3u)
		{
			*display_pattern = 0u;
		}
	}
	
	return *display_pattern;
}

//turn on LED as per pattern.
void display_pattern_to_LED(uint8_t traffic_light_pattern)
{
	int8_t locLEDArray[NB_OF_LEDS];
	
	//copy pattern from structure
	switch (traffic_light_pattern)
	{
		case 0u:
			for (int j =0; j < NB_OF_LEDS; j++)
		{
			locLEDArray[j] = A.forward[j];
		}
		break;
		
		case 1u:
			for (int j =0; j < NB_OF_LEDS; j++)
		{
			locLEDArray[j] = A.wait[j];
		}
		break;
		
		case 2u:
			for (int j =0; j < NB_OF_LEDS; j++)
		{
			locLEDArray[j] = A.reverse[j];
		}
		break;
		
		case 3u:
			for (int j =0; j < NB_OF_LEDS; j++)
		{
			locLEDArray[j] = A.off[j];
		}
		break;
		
		default:
			break;
	}
	
	//turn on LED as per pattern.
	LEDR1(locLEDArray[0]);
	LEDY1(locLEDArray[1]);
	LEDG1(locLEDArray[2]);
	LEDR2(locLEDArray[3]);
	LEDY2(locLEDArray[4]);
	LEDG2(locLEDArray[5]);
}