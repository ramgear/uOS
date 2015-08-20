/**
 ******************************************************************************
 * @file	os.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	18-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OS_H_
#define OS_H_

/* Includes ------------------------------------------------------------------*/
#include "os_types.h"
#include "os_priority.h"
#include "os_core.h"
#include "os_list.h"
#include "os_task.h"
#include "os_cpu.h"
#include "os_time.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
#define	OS_TASK_IDLE_PRIO		(OS_PRIO_NUM - 1)
#define	OS_TASK_IDLE_STK_SIZE	128

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void
OS_Init(void);

void
OS_Start(void);

bool
OS_IsRunning(void);

extern u32				gOS_Running;

#ifdef __cplusplus
}
#endif

#endif /* OS_H_ */

/*****************************END OF FILE**************************************/
