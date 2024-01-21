/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2015 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name:    RTX_Blinky.c
 * Purpose: Spawns and schedules two threads. This file contans the main() function.
 *----------------------------------------------------------------------------*/

#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX

//#include "Board_LED.h"                  // ::Board Support:LED
//#include "Board_Buttons.h"              // ::Board Support:Buttons

#include "stm32f10x.h"                  // Device header

//#include "lightData.h"		// traffic light application variables
#include "RTX_Blinky.h"		// traffic light application variables

#include "check_traffic_light.h" //#include "check_traffic_light.c"	// file for function to check error adc values of current traffic light pattern
#include "change_traffic_light.h" //#include "change_traffic_light.c" // file for function to set and display traffic light pattern

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
osThreadId change_LED_handle, check_LED_handle;

osThreadId LEDThread1Handle, LEDThread2Handle;

/*
Shared data:	2. variable indicating pttern to display. A uint8 memory location (volatile variable)
*/
//volatile static uint8_t display_pattern = 0u;		
volatile static uint8_t display_pattern_memory_place = 0u;		

// Make pointer to read display pattern between threads
volatile static uint8_t *dispPtr = &display_pattern_memory_place;


/* Private function prototypes -----------------------------------------------*/
static void change_LED_thr (void const *argument);
static void check_LED_thr (void const *argument);

static void LED_Thread1(void const *argument);
static void LED_Thread2(void const *argument);

void check_ADC_error(uint8_t *);//(void);
uint8_t read_error_and_set_pattern(uint8_t *);//(void);
void display_pattern_to_LED(uint8_t);

/*----------------------------------------------------------------------------
 * SystemCoreClockConfigure: configure SystemCoreClock using HSI
                             (HSE is not populated on Nucleo board)
 *----------------------------------------------------------------------------*/
void SystemCoreClockConfigure(void) {

  RCC->CR |= ((uint32_t)RCC_CR_HSION);                     // Enable HSI
  while ((RCC->CR & RCC_CR_HSIRDY) == 0);                  // Wait for HSI Ready

  RCC->CFGR = RCC_CFGR_SW_HSI;                             // HSI is system clock
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);  // Wait for HSI used as system clock

  FLASH->ACR  = FLASH_ACR_PRFTBE;                          // Enable Prefetch Buffer
  FLASH->ACR |= FLASH_ACR_LATENCY;                         // Flash 1 wait state

  RCC->CFGR |= RCC_CFGR_HPRE_DIV1;                         // HCLK = SYSCLK
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;                        // APB1 = HCLK/2
  RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;                        // APB2 = HCLK

  RCC->CR &= ~RCC_CR_PLLON;                                // Disable PLL

  //  PLL configuration:  = HSI/2 * 12 = 48 MHz
  RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL);
  RCC->CFGR |=  (RCC_CFGR_PLLSRC_HSI_Div2 | RCC_CFGR_PLLMULL12);

  RCC->CR |= RCC_CR_PLLON;                                 // Enable PLL
  while((RCC->CR & RCC_CR_PLLRDY) == 0) __NOP();           // Wait till PLL is ready

  RCC->CFGR &= ~RCC_CFGR_SW;                               // Select PLL as system clock source
  RCC->CFGR |=  RCC_CFGR_SW_PLL;
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);  // Wait till PLL is system clock src
}

/* Thread 1 definition */
osThreadDef (change_LED_thr, osPriorityNormal, 1, 0);
osThreadDef (check_LED_thr, osPriorityNormal, 1, 0);

osThreadDef (LED_Thread1, osPriorityNormal, 1, 0);

/*----------------------------------------------------------------------------
 * main: initialize and start the system
 *----------------------------------------------------------------------------*/
int main (void) {
	
  osKernelInitialize ();                                   // initialize CMSIS-RTOS

  // initialize peripherals
  SystemCoreClockConfigure();                              // configure System Clock
  SystemCoreClockUpdate();

  LED_Initialize();                                        // LED Initialization
	
  /* Start change-LED thread */
	//change_LED_handle = osThreadCreate(osThread(change_LED_thr), NULL);
	
	/* Start check-LED thread */
	//check_LED_handle = osThreadCreate(osThread(check_LED_thr), NULL);
	
	/* Start thread 1 */
  LEDThread1Handle = osThreadCreate(osThread(LED_Thread1), NULL);
	

  /* Start thread 2 */
  //LEDThread2Handle = osThreadCreate(osThread(LED_Thread2), NULL);  

  /* Set thread 2 in suspend state */
  //TODO: 
	//osThreadSuspend(LEDThread2Handle); 
	//osThreadYield(LEDThread2Handle);

  osKernelStart ();                                        // start thread execution

  for (;;) {                                               // main must not be terminated!
		// nothing
  }
}

static void LED_Thread1(void const *argument) {
	//uint32_t count = 0;
  (void) argument;
	
	int32_t max_num1 = LED_GetCount();
  int32_t num1 = 0;//0;

  for (;;) {
		  /* Toggle LED2 on for 400ms off for 600ms*/
		//count = osKernelSysTick() + 6;//4;
		LED_On(num1);                                           // Turn specified LED on
		//while (count > osKernelSysTick()){};
			osDelay(400);

		//count = osKernelSysTick() + 9;//6;
		LED_Off(num1);                                          // Turn specified LED off
		//while (count > osKernelSysTick()){};// 
		osDelay(600);
		
    num1++;                                                 // Change LED number
    if (num1 >= max_num1) {
      num1 = 0;                                             // Restart with first LED
    }
  }
	
}



static void change_LED_thr(void const *argument) {
	//uint32_t count = 0;
	//count = osKernelSysTick() + CHANGE_THR_WK_INTERVAL;
	
	for (;;)
	{
	
	//turn on LED as per pattern (Read error and set display pattern)
	display_pattern_to_LED(read_error_and_set_pattern(dispPtr));//());
	
	//goto sleep
	osDelay(CHANGE_THR_WK_INTERVAL);
	//while (count > osKernelSysTick()){};// 
		
	}
}

static void check_LED_thr(void const *argument) {
	//uint32_t count = 0;
	//count = osKernelSysTick() + CHECK_THR_WK_INTERVAL;
	
	for (;;)
	{
	check_ADC_error(dispPtr);//();
	
	// goto sleep
	osDelay(CHECK_THR_WK_INTERVAL);
	//while (count > osKernelSysTick()){};// 
	}
}