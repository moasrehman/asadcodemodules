Description:
An RTOS example to blink LED. modified from RTX blinky example. Added calls from examples for Nucleo-F103RB board on FreeRTOS website(read side note). Currently this examples launches a thread in which an LED is blinked forever.

Side note: 
(Blinky example on FreeRTOS website is made for ARM Compiler Version 5.0 the current ARM compiler at this time is Version 6.0. Both have different infrastructure. ARM Compiler 6 brings together the modern LLVM compiler infrastructure. ARM Compiler 6 is based on a new technology it is only partially compatible with previous ARM Compiler Versions (5 and before).
for more refer: Migrate ARM Compiler 5 to ARM Compiler 6 guide at https://www.keil.com/appnotes/files/apnt_298.pdf)

Abstract to original example:
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
