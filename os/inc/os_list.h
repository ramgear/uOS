/**
 ******************************************************************************
 * @file	os_list.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	18-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 *
 * @addtogroup	OS
 * @{
 *
 * @addtogroup	OS_TCB_LIST	List for Task Control Block Management.
 * @{
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OS_LIST_H_
#define OS_LIST_H_

/* Includes ------------------------------------------------------------------*/
#include "os_task.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

void
OS_List_InsertHead (os_tcb_list_t *pplist, os_tcb_t *pptcb);

void
OS_List_InsertTail(os_tcb_list_t *pplist, os_tcb_t *pptcb);

void
OS_List_InsertPriority (os_tcb_list_t *pplist, os_tcb_t *pptcb);

void
OS_List_Remove (os_tcb_list_t *pplist, os_tcb_t *pptcb);

void
OS_List_MoveHeadFwd (os_tcb_list_t *pplist);

void
OS_List_MoveHeadBwd (os_tcb_list_t *pplist);


#ifdef __cplusplus
}
#endif

/** @} @} */

#endif /* OS_LIST_H_ */

/*****************************END OF FILE**************************************/
