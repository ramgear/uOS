/**
 ******************************************************************************
 * @file	os_time.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	18-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OS_TIME_H_
#define OS_TIME_H_

/* Includes ------------------------------------------------------------------*/
#include "os_types.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
typedef void (*OS_Time_SysTickHook_t)(void);

/* Exported constants --------------------------------------------------------*/
#if !defined(OS_TIME_TICKS_PER_SEC)
#define	OS_TIME_TICKS_PER_SEC	100
#endif

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void
OS_Time_Init(void);

void
OS_Time_Delay(u32 ticks);

void
OS_Time_SysTick(void);

extern OS_Time_SysTickHook_t	OS_Time_SysTickHook;
extern u32 OSTimeTickCtr;

#ifdef __cplusplus
}
#endif

#endif /* OS_TIME_H_ */

/*****************************END OF FILE**************************************/
