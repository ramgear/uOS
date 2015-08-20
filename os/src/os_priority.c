/**
 ******************************************************************************
 * @file	os_priority.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	18-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "os_priority.h"
#include "os_cpu.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define	OS_PRIO_BITS_NUM	32

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

static u32				sOS_PrioMaskRdy;
static u32				sOS_PrioMaskPend;

os_priority_t	gOS_CurrentPrio = OS_PRIO_NUM;
os_priority_t	gOS_HighRdyPrio = OS_PRIO_NUM;

/* Private function prototypes -----------------------------------------------*/
u32	OS_CPU_TailCountZeros(u32);

/* Private functions ---------------------------------------------------------*/

boolean
OS_Prio_IsValid(os_priority_t prio)
{
	return (prio < OS_PRIO_NUM);
}

os_priority_t
OS_Prio_GetHighRdy(void)
{
	 return OS_CPU_TailCountZeros(sOS_PrioMaskRdy);
}

 /**
  * @brief	Check if left has higher priority than left (Lower value is higher priority).
  */
 boolean
 OS_Prio_IsHigher(os_priority_t left, os_priority_t right)
 {
	 return (left < right);
 }

 void
 OS_Prio_SetReady(os_priority_t prio, os_prio_stat_t stat)
 {
	 /* Mask flag */
	 if(stat != PRIO_CLR)
		 OS_SETBIT(sOS_PrioMaskRdy, prio);
	 else
		 OS_CLRBIT(sOS_PrioMaskRdy, prio);
 }

 void
 OS_Prio_SetPending(os_priority_t prio, os_prio_stat_t stat)
 {
	 /* Mask flag */
	 if(stat != PRIO_CLR)
		 OS_SETBIT(sOS_PrioMaskPend, prio);
	 else
		 OS_CLRBIT(sOS_PrioMaskPend, prio);
 }

 os_priority_t
 OS_Prio_GetCurrentPriority(void)
 {
	 return gOS_CurrentPrio;
 }

 boolean
 OS_Prio_IsHigherRdy(void)
 {
	 gOS_HighRdyPrio = OS_Prio_GetHighRdy();

	 return OS_Prio_IsHigher(gOS_HighRdyPrio, gOS_CurrentPrio);
 }

/*****************************END OF FILE**************************************/
