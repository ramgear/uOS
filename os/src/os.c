/**
 ******************************************************************************
 * @file	os.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	18-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "os.h"
#include "os_cpu.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
u32				gOS_Running;
os_priority_t	sOS_HighRdyPrio;
os_priority_t	sOS_CurrentPrio;
os_tcb_t		*spOS_CurentTCB;
os_tcb_t		*spOS_HighRdyTCB;
u32				sOS_IdleCtr;

static stack_t sOSIdleStk[OS_TASK_IDLE_STK_SIZE];

/* Private function prototypes -----------------------------------------------*/

void
OS_IdleTask(void *arg);

/* Private functions ---------------------------------------------------------*/

void
OS_Init(void)
{

	OS_Task_Init();

	OS_CPU_Init();

	gOS_Running		= OS_FALSE;
	sOS_CurrentPrio	= 0;
	sOS_HighRdyPrio	= 0;
	spOS_CurentTCB	= NULL;
	spOS_HighRdyTCB	= NULL;
	sOS_IdleCtr		= 0;

	OS_Task_Create(
			OS_IdleTask
			, sOSIdleStk
			, OS_TASK_IDLE_STK_SIZE
			, OS_TASK_IDLE_PRIO
			, "OS Idle Task"
			);
}

void
OS_Start(void)
{
	gOS_Running		= OS_TRUE;

	sOS_HighRdyPrio	= OS_Prio_GetHighRdy();
	sOS_CurrentPrio	= sOS_HighRdyPrio;
	spOS_HighRdyTCB	= OS_Task_GetTCBRdy(sOS_CurrentPrio);
	spOS_CurentTCB	= spOS_HighRdyTCB;

	OS_CPU_StartCtxSw();
}

void
OS_IdleTask(void *arg)
{
	(void)arg;

	while(OS_TRUE)
	{
		sOS_IdleCtr++;
	}
}

bool
OS_IsRunning(void)
{
	return (gOS_Running != OS_FALSE);
}

/*****************************END OF FILE**************************************/
