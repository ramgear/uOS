/**
 ******************************************************************************
 * @file	os_time.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	18-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "os_time.h"
#include "os_task.h"
#include "os_cpu.h"
#include "stm32f4xx.h"
#include "os_isr.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
OS_Time_SysTickHook_t	OS_Time_SysTickHook = NULL;
u32 OSTimeTickCtr = 0;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
void
OS_Time_Init(void)
{
	SysTick_Config(OS_TIME_TICKS_PER_SEC);
}

void
OS_Time_Delay(u32 ticks)
{
	os_tcb_t	*pltcb = NULL;

	if (ticks > 0u)
	{
		OS_CPU_EnterCritical();
		//pltcb = spOS_CurentTCB;

		pltcb->uDelay = ticks;
		OS_Prio_SetReady(pltcb->tPrio, PRIO_CLR);
		OS_Prio_SetPending(pltcb->tPrio, PRIO_SET);

		OS_CPU_EnterCritical();

		OS_Sched_ReSched();
	}
}

/**
 * @brief	SysTick ISR handler.
 * @details	This function override weak function that define in ISR Vector Table.
 * @param	None.
 * @retval	None.
 */
void
OS_ISR_SysTick_Handler(void)
{
	OS_CPU_SR_ALLOC();

	OS_ISR_Enter();

	OS_CPU_ENTER_CRITICAL();
	OSTimeTickCtr++;
	OS_CPU_EXIT_CRITICAL();

	//OS_Task_Tick();

	ISR_SysTick_Handler();

	OS_ISR_Exit();
}

/*****************************END OF FILE**************************************/
