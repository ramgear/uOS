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

os_tcb_t	*gOS_CurrentTCB = NULL;
os_tcb_t	*gOS_HighRdyTCB = NULL;

extern os_priority_t gOS_HighRdyPrio;
extern os_priority_t gOS_CurrentPrio;

/* Private function prototypes -----------------------------------------------*/
void
OS_Sched_ChkCtxWs(void);

void
OS_Sched_RoundRobin( void );

/* Private functions ---------------------------------------------------------*/
inline void
OS_Sched_Lock(void)
{
	++sSchedNestingCtr;
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

void
OS_Sched_TimeTickSched(void)
{
	os_tcb_list_t *pllist;
	os_tcb_t *pltcb;
	u32	count;

	OS_CPU_SR_ALLOC();

	/* Check OS running */
	if(!OS_IsRunning())
		return;

	OS_CPU_ENTER_CRITICAL();

	/* Check delay pending task */
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

	/* Yield Round Robin task */
	OS_Sched_RoundRobin();

	OS_CPU_EXIT_CRITICAL();

	OS_Sched_ChkCtxWs();
}

void
OS_Sched_RoundRobin( void )
{
	OS_CPU_SR_ALLOC();

	OS_CPU_ENTER_CRITICAL();

	os_tcb_list_t *pllist = OS_Task_GetRdyList(gOS_CurrentPrio);

	if(pllist->count != 0)
	{
		if(--pllist->pHead->uTimeRemain == 0 )
		{
			/* Reload time quanta */
			pllist->pHead->uTimeRemain = pllist->pHead->uTimeQuanta;

			/* Move to next ready TCB */
			OS_List_MoveHeadFwd(pllist);
		}
	}

	OS_CPU_EXIT_CRITICAL();
}

void
OS_Sched_ChkCtxWs(void)
{
	if(OS_Prio_IsHigherRdy())
	{
		gOS_HighRdyTCB = OS_Task_GetTCBRdy(gOS_HighRdyPrio);
		OS_CPU_CtxSw();
	}
}

/*****************************END OF FILE**************************************/
