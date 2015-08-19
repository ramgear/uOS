/**
 ******************************************************************************
 * @file	os_sched.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	18-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OS_SCHED_H_
#define OS_SCHED_H_

/* Includes ------------------------------------------------------------------*/
#include "os_types.h"
#include "os_task.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void
OS_Sched_Lock(void);

void
OS_Sched_Unlock(void);

bool
OS_Sched_IsLocking(void);

bool
OS_Sched_PrepareHighReady(void);

void
OS_Sched_TimeTickSched(void);

void
OS_Sched_RoundRobbin(os_tcb_list_t *pplist_rdy);

void
OS_Sched_ReSched(void);

#ifdef __cplusplus
}
#endif

#endif /* OS_SCHED_H_ */

/*****************************END OF FILE**************************************/
