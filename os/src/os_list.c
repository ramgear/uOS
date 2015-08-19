/**
 ******************************************************************************
 * @file	os_list.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	18-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 *
 * @addtogroup	OS_TCB_LIST
 * @{
 */

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include "os_list.h"
#include "os_priority.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static inline bool
OS_List_IsEmpty(os_tcb_list_t *pplist);

static void
OS_List_InsertBefore (os_tcb_list_t *pplist, os_tcb_t *pptcb, os_tcb_t *pptcb_new);

static void
OS_List_InsertAfter (os_tcb_list_t *pplist, os_tcb_t *pptcb, os_tcb_t *pptcb_new);

/* Private functions ---------------------------------------------------------*/

/**
 * @brief	Check for empty list.
 * @param[in]	pplist:	Pointer to list.
 * @retval	None.
 */
static inline bool
OS_List_IsEmpty(os_tcb_list_t *pplist)
{
	return (pplist->count == 0);
}

/**
 * @brief	Insert new TCB to head of list and change to new head of list.
 * @param[in]	pplist:	Pointer to list to be inserted new TCB.
 * @param[in]	pptcb:	Pointer to TCB to be inserted.
 * @retval	None.
 */
void
OS_List_InsertHead (os_tcb_list_t *pplist, os_tcb_t *pptcb)
{
	OS_List_InsertBefore(pplist, pplist->pHead, pptcb);
	OS_List_MoveHeadBwd(pplist);
}

/**
 * @brief	Insert new TCB to tail of list and keep same head of list.
 * @param[in]	pplist:	Pointer to list to be inserted new TCB.
 * @param[in]	pptcb:	Pointer to TCB to be inserted.
 * @retval	None.
 */
void
OS_List_InsertTail(os_tcb_list_t *pplist, os_tcb_t *pptcb)
{
	OS_List_InsertBefore(pplist, pplist->pHead, pptcb);
}

/**
 * @brief	Insert TCB to list with always sorted highest priority first.
 * @param[in]	pplist:	Pointer to list to be inserted new TCB.
 * @param[in]	pptcb:	Pointer to TCB to be inserted.
 * @retval	None.
 */
void
OS_List_InsertPriority (os_tcb_list_t *pplist, os_tcb_t *pptcb)
{
	os_tcb_t 	*pltcb;

	if( !OS_List_IsEmpty(pplist) )
	{
		pltcb = pplist->pHead;

		while(
				( pltcb->pNext != pplist->pHead ) 			/* Check end cycle */
				&& ( OS_Prio_IsHigher(pltcb->tPrio, pptcb->tPrio) )	/* Check if still higher priority */
				)
		{
			/* Move to next TCB */
			pltcb = pltcb->pNext;
		}

		if( OS_Prio_IsHigher(pptcb->tPrio, pltcb->tPrio) )
		{
			/* Insert higher priority */
			OS_List_InsertBefore(pplist, pltcb, pptcb);

			/* Check if insert before first node */
			if(pltcb == pplist->pHead)
				OS_List_MoveHeadBwd(pplist);
		}
		else
		{
			/* Insert lower or equal priority */
			OS_List_InsertAfter(pplist, pltcb, pptcb);
		}
	}
	else
	{
		/* No element, insert to head */
		pplist->pHead = pptcb;
		pplist->pHead->pNext = pptcb;
		pplist->pHead->pPrev = pptcb;
		pplist->count++;
	}
}

/**
 * @brief	Insert TCB to list before specified TCB.
 * @param[in]	pplist:	Pointer to list to be inserted new TCB.
 * @param[in]	pptcb:	Pointer to TCB to be inserted before.
 * @param[in]	pptcb_new:	Pointer new to TCB to be inserted.
 * @retval	None.
 */
void
OS_List_InsertBefore (os_tcb_list_t *pplist, os_tcb_t *pptcb, os_tcb_t *pptcb_new)
{
	if(pptcb_new == NULL)
		return;		/* Cannot insert null TCB */

	if(!OS_List_IsEmpty(pplist))
	{
		pptcb->pPrev->pNext	= pptcb_new;
		pptcb_new->pPrev 	= pptcb->pPrev;
		pptcb->pPrev 		= pptcb_new;
		pptcb_new->pNext 	= pptcb;
	}
	else
	{
		/* List is empty then insert to head */
		pplist->pHead 			= pptcb_new;
		pplist->pHead->pNext 	= pptcb_new;
		pplist->pHead->pPrev 	= pptcb_new;
	}

	/* Increase number of element */
	pplist->count++;
}

/**
 * @brief	Insert TCB to list after specified TCB.
 * @param[in]	pplist:	Pointer to list to be inserted new TCB.
 * @param[in]	pptcb:	Pointer to TCB to be inserted after.
 * @param[in]	pptcb_new:	Pointer new to TCB to be inserted.
 * @retval	None.
 */
void
OS_List_InsertAfter (os_tcb_list_t *pplist, os_tcb_t *pptcb, os_tcb_t *pptcb_new)
{
	if(pptcb_new == NULL)
		return;		/* Cannot insert null TCB */

	if(!OS_List_IsEmpty(pplist))
	{
		pptcb->pNext->pPrev	= pptcb_new;
		pptcb_new->pNext 	= pptcb->pNext;
		pptcb->pNext 		= pptcb_new;
		pptcb_new->pPrev 	= pptcb;
	}
	else
	{
		/* List is empty then insert to head */
		pplist->pHead 			= pptcb_new;
		pplist->pHead->pNext 	= pptcb_new;
		pplist->pHead->pPrev 	= pptcb_new;
	}

	/* Increase number of element */
	pplist->count++;
}

/**
 * @brief	Insert TCB to list after specified TCB.
 * @param[in]	pplist:	Pointer to list to be inserted new TCB.
 * @param[in]	pptcb:	Pointer to TCB to be inserted after.
 * @param[in]	pptcb_new:	Pointer new to TCB to be inserted.
 * @retval	None.
 */
void
OS_List_Remove (os_tcb_list_t *pplist, os_tcb_t *pptcb)
{
	if(OS_List_IsEmpty(pplist) || pptcb == NULL)
		return;					/* Cannot remove from empty list or null element */

	if(--pplist->count != 0)
	{
		/* Still has element */
		if(pptcb == pplist->pHead)	/* Remove head ? */
			OS_List_MoveHeadFwd( pplist );

		pptcb->pPrev->pNext	= pptcb->pNext;
		pptcb->pNext->pPrev	= pptcb->pPrev;
	}
	else
	{
		/* Last one, set to empty list */
		pplist->pHead = NULL;
	}

	pptcb->pNext 		= NULL;
	pptcb->pPrev 		= NULL;
}

/**
 * @brief	Move head TCB to next.
 * @details	This is used by moving head to tail by simple move current head to next.
 * 			It is used by Cooperative Schedure to share time for other task in the same priority.
 * @param[in]	pplist:	Pointer to list to be moved.
 * @retval	None.
 */
void
OS_List_MoveHeadFwd (os_tcb_list_t *pplist)
{
	if(pplist->pHead != NULL)
		pplist->pHead = pplist->pHead->pNext;
}

/**
 * @brief	Move head TCB to previous.
 * @param[in]	pplist:	Pointer to list to be moved.
 * @retval	None.
 */
void
OS_List_MoveHeadBwd (os_tcb_list_t *pplist)
{
	if(pplist->pHead != NULL)
		pplist->pHead = pplist->pHead->pPrev;
}

/** @} */

/*****************************END OF FILE**************************************/
