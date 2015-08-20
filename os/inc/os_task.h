/**
 ******************************************************************************
 * @file	os_task.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	18-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OS_TASK_H_
#define OS_TASK_H_

/* Includes ------------------------------------------------------------------*/
#include "os_types.h"
#include "os_priority.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/

typedef	void (*task_t)(void *parg);
typedef	OS_DATA	stack_t;

 /**
  * @brief	Task Control Block type.
  */
 typedef struct os_tcb_t
 {
	 /* List control variables */
	 struct os_tcb_t   *pNext;             /* Pointer to next     TCB in the TCB list */
	 struct os_tcb_t   *pPrev;             /* Pointer to previous TCB in the TCB list */

	 stack_t			*pStack;

	 task_t				tTask;
	 stack_t			*pStackBase;
	 u32				uStkSize;
	 const char			*pTaskName;
     os_priority_t		tPrio;
     void				*pArg;
     u32				uDelay;
     u32				uTimeQuanta;
     u32				uTimeRemain;

 } os_tcb_t;

typedef struct
{
	os_tcb_t	*pHead;
	u32			count;
} os_tcb_list_t;

/* Exported constants --------------------------------------------------------*/
#if !defined(OS_TASK_USER_NUM)
#define	OS_TASK_USER_NUM	6
#endif

#define	OS_TASK_OS_NUM		1
#define	OS_TASK_NUM			(OS_TASK_USER_NUM + OS_TASK_OS_NUM)

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void
OS_Task_Init(void);

os_tcb_t *
OS_Task_Create(
		 task_t				ptTask
		 ,stack_t			*ppStack
		 ,u32				puStkSize
	     ,os_priority_t		ptPrio
		 ,const char		*ppTaskName
		 );

void
OS_Task_Return (void);

os_tcb_t *
OS_Task_GetTCBRdy(os_priority_t prio);

os_tcb_list_t *
OS_Task_GetPendList(void);

void
OS_Task_AddRdyList (os_tcb_t *pptcb);

#ifdef __cplusplus
}
#endif

#endif /* OS_TASK_H_ */

/*****************************END OF FILE**************************************/
