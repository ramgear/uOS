/**
 ******************************************************************************
 * @file	os_task.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	18-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "os_task.h"
#include "os_cpu.h"
#include "os_list.h"
#include "os_time.h"
#include "os_isr.h"
#include "os_sched.h"
#include "os.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static os_tcb_t			sOS_TCBTasks[OS_TASK_NUM];
static os_tcb_list_t	sOS_TCBFreeList;
static os_tcb_list_t	sOS_TCBRdyList[OS_PRIO_NUM];
static os_tcb_list_t	sOS_TCBPendList;


/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
void
OS_Task_Init(void)
{
	os_tcb_t	*pltcb 	= sOS_TCBTasks;
	u32			i 		= OS_TASK_NUM;

	/* Initial variables */

	/* Add all TCB to free list on initial */
	while(i--)
	{
		OS_List_InsertTail(&sOS_TCBFreeList, pltcb++);
	}
}

os_tcb_t *
OS_Task_Create(
		 task_t				ptTask
		 ,stack_t			*ppStack
		 ,u32				puStkSize
	     ,os_priority_t		ptPrio
		 ,const char		*ppTaskName
		 )
{
	OS_CPU_SR_ALLOC();

	os_tcb_t	*pltcb;

	pltcb = sOS_TCBFreeList.pHead;

	if(pltcb != NULL)
	{
		OS_CPU_ENTER_CRITICAL();	/* Prevent from interrupt */

		/* Remove TCB from free list */
		OS_List_Remove(&sOS_TCBFreeList, pltcb);

		/* Initial Task Control Block */
		pltcb->tTask		= ptTask;
		pltcb->pStackBase	= ppStack;
		pltcb->pStack		= ppStack + (puStkSize - 1);
		pltcb->uStkSize		= puStkSize;
		pltcb->pTaskName	= ppTaskName;
		pltcb->tPrio		= ptPrio;
		pltcb->uDelay		= 0;

		/*
		 * Initial process stack frame.
		 * This function must implement in os_cpu.h due to it is processor specific.
		 */
		OS_CPU_InitStack(pltcb);

		/* Set ready priority */
		OS_Prio_SetReady(pltcb->tPrio, PRIO_SET);

		/* Add to ready list */
		OS_List_InsertPriority(&sOS_TCBRdyList[pltcb->tPrio], pltcb);

		OS_CPU_EXIT_CRITICAL();	/* Resume interrupt */
	}

	return pltcb;
}

/**
 * @brief	Task return function.
 * @details	This function is called if a task accidentally returns without deleting itself.
 * 			In other words, a task should either be an infinite loop or delete itself if it's done.
 * @param	None.
 * @note	Task should run infinite loop.
 */
void
OS_Task_Return (void)
{
	while(1)
	{
		OS_Time_Delay(OS_TIME_TICKS_PER_SEC);
	}
}

os_tcb_t *
OS_Task_GetTCBRdy(os_priority_t prio)
{
	return (sOS_TCBRdyList[prio].pHead);
}

os_tcb_list_t *
OS_Task_GetPendList(void)
{
	return (&sOS_TCBPendList);
}

void
OS_Task_SetTimeQuanta(os_tcb_t *pptcb, u32 ticks)
{
	pptcb->uTimeQuanta = ticks;
}

/*****************************END OF FILE**************************************/
