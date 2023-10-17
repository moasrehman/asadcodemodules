/**
Descrption:
	Simple LED blink exmple on STM32F103RXX MCU.
	
IDE-Version:
µVision V5.38.0.0
Copyright (C) 2022 ARM Ltd and ARM Germany GmbH. All rights reserved.

License Information:
Asad Rehman
Asad
LIC=----

Tool Version Numbers:
Toolchain:        MDK-Lite  Version: 5.38.0.0
Toolchain Path:    C:\Keil_v5\ARM\ARMCLANG\Bin
C Compiler:         ArmClang.exe        V6.19
Assembler:          Armasm.exe        V6.19
Linker/Locator:     ArmLink.exe        V6.19
Library Manager:    ArmAr.exe        V6.19
Hex Converter:      FromElf.exe        V6.19
CPU DLL:               SARMCM3.DLL          V5.38.0.0
Dialog DLL:         TARMSTM.DLL          V1.67.1.0
Target DLL:             UL2CM3.DLL           V1.164.8.0
Dialog DLL:         TARMSTM.DLL          V1.67.1.0

 */

/**
  @page GPIO_IOToggle GPIO IO Toggle example
  
  @verbatim
  ******************** (C) COPYRIGHT 2016 STMicroelectronics *******************
  * @file    GPIO/GPIO_IOToggle/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the GPIO IO Toggle example.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  @endverbatim

@par Example Description

How to configure and use GPIOs through the HAL API.

PA.05 IO (configured in output pushpull mode) toggles in a forever loop.
On STM32F103RB-Nucleo board this IO is connected to LED2.

In this example, HCLK is configured at 64 MHz.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - GPIO/GPIO_IOToggle/Inc/stm32f1xx_hal_conf.h    HAL configuration file
  - GPIO/GPIO_IOToggle/Inc/stm32f1xx_it.h          Interrupt handlers header file
  - GPIO/GPIO_IOToggle/Inc/main.h                  Header for main.c module  
  - GPIO/GPIO_IOToggle/Src/stm32f1xx_it.c          Interrupt handlers
  - GPIO/GPIO_IOToggle/Src/main.c                  Main program
  - GPIO/GPIO_IOToggle/Src/system_stm32f1xx.c      STM32F1xx system source file


@par Hardware and Software environment

  - This example runs on STM32F1xx devices.
    
  - This example has been tested with STM32F103RB-Nucleo board and can be
    easily tailored to any other supported device and development board.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
