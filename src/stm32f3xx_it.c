/**
  ******************************************************************************
  * @file    stm32f3xx_it.c
  * @author  Ac6
  * @version V1.0
  * @date    02-Feb-2015
  * @brief   Default Interrupt Service Routines.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#ifdef USE_RTOS_SYSTICK
#include <cmsis_os.h>
#endif
#include "stm32f3xx_it.h"

/* typedef -------------------------------------------------------------------*/
/* define --------------------------------------------------------------------*/
/* macro ---------------------------------------------------------------------*/
/* variables -----------------------------------------------------------------*/
/* function prototypes -------------------------------------------------------*/
void (*sx1276_dio0_isr) (void);


/* functions -----------------------------------------------------------------*/


/******************************************************************************/
/*            	  	    Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles SysTick Handler, but only if no RTOS defines it.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
#ifdef USE_RTOS_SYSTICK
	osSystickHandler();
#endif
}

void
NMI_Handler(void)
{
  while (1)
    {
      ;  // halt program
    }
}

void
HardFault_Handler(void)
{
  while (1)
    {
      ;  // halt program
    }
}

void
MemManage_Handler(void)
{
  while (1)
    {
      ;  // halt program
    }
}

void
BusFault_Handler(void)
{
  while (1)
    {
      ;  // halt program
    }
}

void
UsageFault_Handler(void)
{
  while (1)
    {
      ;  // halt program
    }
}

void
SVC_Handler(void)
{
  while (1)
    {
      ;  // halt program
    }
}

void
DebugMon_Handler(void)
{
  while (1)
    {
      ;  // halt program
    }
}

void
PendSV_Handler(void)
{
  while (1)
    {
      ;  // halt program
    }
}

void
EXTI3_IRQHandler (void)
{
  sx1276_dio0_isr ();
}
