/**
 ******************************************************************************
 * @file	os_priority.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	18-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OS_PRIORITY_H_
#define OS_PRIORITY_H_

/* Includes ------------------------------------------------------------------*/
#include "os_types.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
 typedef u8	os_priority_t;

 typedef enum
 {
	 PRIO_CLR	= OS_FALSE,
	 PRIO_SET	= OS_TRUE,
 } os_prio_stat_t;

/* Exported constants --------------------------------------------------------*/

#if !defined(OS_PRIO_NUM)
#define	OS_PRIO_NUM		32
#endif

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

 boolean
 OS_Prio_IsValid(os_priority_t prio);

 os_priority_t
 OS_Prio_GetHighRdy(void);

 os_priority_t
 OS_Prio_GetCurrentPriority(void);

 boolean
 OS_Prio_IsHigherRdy(void);

 boolean
 OS_Prio_IsHigher(os_priority_t left, os_priority_t right);

 void
 OS_Prio_SetReady(os_priority_t prio, os_prio_stat_t stat);

 void
 OS_Prio_SetPending(os_priority_t prio, os_prio_stat_t stat);


#ifdef __cplusplus
}
#endif

#endif /* OS_PRIORITY_H_ */

/*****************************END OF FILE**************************************/
