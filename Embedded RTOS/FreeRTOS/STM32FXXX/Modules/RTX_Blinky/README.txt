Description:
RTOS blinky example application.

Abstract
The 'RTX_Blinky' project is a simple CMSIS RTOS Kernel based example for
ST 'STM32F103RB' microcontroller using ST 'Nucleo-F103RB' Evaluation Board.
Compliant to Cortex Microcontroller Software Interface Standard (CMSIS).

Example functionality:
 - Clock Settings:
   - XTAL    = HSI     =  8.00 MHz
   - SYSCLK  =           48.00 MHz

 - one LED blinks.
 - blinking is paused while holding down the USER button.


The Blinky example is available in different targets:

  STM32F103 Flash:    configured for on-chip Flash
                      (used for production or target debugging)

  STM32F103 RAM:      configured for on-chip RAM
                      (used for target debugging)
