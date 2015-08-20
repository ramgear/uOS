/**
 ******************************************************************************
 * @file	cpu_core.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	20-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "cpu.h"
#include "stm32f4xx_hal.h"

/**
  * @brief  Setup the microcontroller system
  *         Initialize the FPU setting, vector table location and External memory
  *         configuration.
  * @param  None
  * @retval None
  */
void
CPU_CORE_SystemInit(void)
{
	SystemInit();
}

/**
 * @brief	System Tick Configuration
 * @details	The function initializes the System Timer and its interrupt, and starts the System Tick Timer.
 *			Counter is in free running mode to generate periodic interrupts.
 *
 * @param [in]	FreqHz	Tick frequency in Hz.
 * @retval	None.
 */
void
CPU_CORE_SysTickInit(CPU_DATA FreqHz, CPU_DATA Prio)
{
	CPU_DATA cpu_clk_freq;
	CPU_DATA ticks = 0;

	cpu_clk_freq = CPU_CORE_GetClkFreq();
	ticks = cpu_clk_freq / FreqHz - 1;

	if ((ticks) > SysTick_LOAD_RELOAD_Msk)  return;      /* Reload value impossible */

	SysTick->LOAD  = ticks;                                  /* set reload register */
	NVIC_SetPriority (SysTick_IRQn, Prio);  					/* set Priority for Systick Interrupt */
	SysTick->VAL   = 0;                                          /* Load the SysTick Counter Value */
	SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
	                   SysTick_CTRL_TICKINT_Msk   |
	                   SysTick_CTRL_ENABLE_Msk;                    /* Enable SysTick IRQ and SysTick Timer */
}

/**
  * @brief  Returns the HCLK frequency
  * @note   Each time HCLK changes, this function must be called to update the
  *         right HCLK value. Otherwise, any configuration based on this function will be incorrect.
  *
  * @note   The SystemCoreClock CMSIS variable is used to store System Clock Frequency
  *         and updated within this function
  * @retval HCLK frequency
  */
CPU_DATA
CPU_CORE_GetClkFreq(void)
{
	return HAL_RCC_GetHCLKFreq();;
}

void
CPU_CORE_PendSVInit(CPU_DATA Prio)
{
	NVIC_SetPriority(PendSV_IRQn, Prio);
}

/*****************************END OF FILE**************************************/
