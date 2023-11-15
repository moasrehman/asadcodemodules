/*----------------------------------------------------------------------------
 * Name:    README.txt
 * Purpose: Contains documentation of the project.
 *----------------------------------------------------------------------------*/

Description:
A traffic light fault detection system.

Algorithm:
Thread 1: Wakes up after certain time <thread_1_interval>, checks error variable and changes LED pattern.
Thread 2: Checks up on ADC value at a regular interval <thread_2_interval> shorter than thread 1 interval*. Sets error variable to asses state of error.
*(atleast 1/10th but closer to ADC conversion complete interval. Greater than AC conversion cmplete intercal. or  as soon as ADC conversion completes: a non RTOS system.)

Shared data:
1. structure storing pattern of LED. A structure
2. variable indicating pttern to display. A uint8 memory location (volatile variable)
3. variable indicating error state. A binary variable. (volatile variabe)
thread_1_interval = 1 s
thread_2_interval = 10 ms

Revision:
v0.1: two threads operating in parallel, switching LED, sharing data.

Abstract to original example:
-----------------------------
Note: (Blinky example on FreeRTOS website is made for ARM Compiler Version 5.0 the current ARM compiler at this time is Version 6.0. Both have different infrastructure. ARM Compiler 6 brings together the modern LLVM compiler infrastructure. ARM Compiler 6 is based on a new technology it is only partially compatible with previous ARM Compiler Versions (5 and before).
for more refer: Migrate ARM Compiler 5 to ARM Compiler 6 guide at https://www.keil.com/appnotes/files/apnt_298.pdf)

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
