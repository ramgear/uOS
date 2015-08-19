/**
 ******************************************************************************
 * @file	os_sched.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	19-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "os_sched.h"
#include "os_cpu.h"
#include "os_list.h"
#include "os_isr.h"
#include "os.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static u32	sSchedNestingCtr	= 0u;

static os_tcb_t	*sOS_CurTCB = NULL;
static os_tcb_t	*sOS_HRdyTCB = NULL;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
inline void
OS_Sched_Lock(void)
{
	OS_CPU_SR_ALLOC();

	OS_CPU_ENTER_CRITICAL();
	++sSchedNestingCtr;
	OS_CPU_EXIT_CRITICAL();
}

inline void
OS_Sched_Unlock(void)
{
	OS_CPU_SR_ALLOC();

	OS_CPU_ENTER_CRITICAL();
	--sSchedNestingCtr;
	OS_CPU_EXIT_CRITICAL();
}

inline bool
OS_Sched_IsLocking(void)
{
	return (sSchedNestingCtr != 0);
}

bool
OS_Sched_PrepareHighReady(void)
{
	os_priority_t cur;
	os_priority_t high;

	if(OS_Prio_IsHigherRdy())
	{
		cur = OS_Prio_GetCurrentPriority();
		high = OS_Prio_GetHighRdy();

		sOS_HRdyTCB = NULL;
		return true;
	}

	return false;
}

void
OS_Sched_TimeTickSched(void)
{
	os_tcb_list_t *pllist;
	os_tcb_list_t *pllist_rdy;
	os_tcb_t *pltcb;
	u32	count;

	OS_CPU_SR_ALLOC();

	/* Check OS running */
	if(!OS_IsRunning())
		return;

	/* Check if call from ISR */
	if(OS_ISR_IsNesting())
		return;

	/* Check if scheduler is locked */
	if(OS_Sched_IsLocking())
		return;

	OS_CPU_ENTER_CRITICAL();

	pllist	= OS_Task_GetPendList();
	count = pllist->count;
	pltcb	= pllist->pHead;

	while(count-- != 0)
	{
		if(--pltcb->uDelay == 0)
		{
			/* No need to wait anymore */
			OS_List_Remove(pllist, pltcb);	/* Remove from pending list */

			OS_Task_AddRdyList(pltcb);		/* Add to ready list */
		}

		/* Move to next TCB */
		pltcb = pltcb->pNext;
	}

	OS_CPU_EXIT_CRITICAL();

	OS_Sched_ReSched();	/* Re-scheduler */
}

void
OS_Sched_ReSched(void)
{
	OS_CPU_SR_ALLOC();

	/* Check OS running */
	if(!OS_IsRunning())
		return;

	/* Check if call from ISR */
	if(OS_ISR_IsNesting())
		return;

	/* Check if scheduler is locked */
	if(OS_Sched_IsLocking())
		return;

	OS_CPU_ENTER_CRITICAL();

	if(OS_Sched_PrepareHighReady())	/* Higher priority ready ? */
	{
		/* Perform context switch */
		OS_CPU_CtxSw();
	}

	OS_CPU_EXIT_CRITICAL();

}

void
OS_Sched_RoundRobbin( os_tcb_list_t *pplist_rdy )
{
	OS_CPU_SR_ALLOC();

	/* Check OS running */
	if(!OS_IsRunning())
		return;

	/* Check if call from ISR */
	if(OS_ISR_IsNesting())
		return;

	/* Check if scheduler is locked */
	if(OS_Sched_IsLocking())
		return;

	OS_CPU_ENTER_CRITICAL();

	if(pplist_rdy->count != 0)
	{
		if(--pplist_rdy->pHead->uTimeRemain == 0 )
		{
			/* Reload time quanta */
			pplist_rdy->pHead->uTimeRemain = pplist_rdy->pHead->uTimeQuanta;

			/* Move to next ready TCB */
			OS_List_MoveHeadFwd(pplist_rdy);
		}
	}

	OS_CPU_EXIT_CRITICAL();

	OS_Sched_ReSched();		/* Re-scheduler */
}

/*****************************END OF FILE**************************************/
