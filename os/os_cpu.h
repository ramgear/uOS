/**
 ******************************************************************************
 * @file	os_cpu.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	18-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OS_CPU_H_
#define OS_CPU_H_

/* Includes ------------------------------------------------------------------*/
#include "os_types.h"
#include "os_task.h"
#include "os_types.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

#if  !defined(OS_CPU_EXCEPT_STK_SIZE)
#define  OS_CPU_EXCEPT_STK_SIZE    			128u          /* Default exception stack size is 128 OS_STK entries */
#endif

#if  !defined(OS_CPU_CFG_SYSTICK_PRIO)
#define  OS_CPU_CFG_SYSTICK_PRIO           	0u
#endif

/* Exported macro ------------------------------------------------------------*/
#define OS_CPU_SR_ALLOC()			u32 cpu_sr;
#define	OS_CPU_ENTER_CRITICAL()		cpu_sr = OS_CPU_EnterCritical();
#define	OS_CPU_EXIT_CRITICAL()		OS_CPU_ExitCritical(cpu_sr);

/* Exported functions --------------------------------------------------------*/

void
OS_CPU_Init(void);

 /**
  * @brief	Initial task stack frame.
  * @details	This function will initial stack frame in order as same as processor enter exception mode.
  * @param	None.
  * @retval	None.
  */
void
OS_CPU_InitStack(os_tcb_t *pptcb);

/**
 * @brief	Enter critical section to prevent interrupt.
 * @details	This function will save priority mask register to stack and disable interrupt.
 * @param	None.
 * @retval	None.
 *
 * @note	This function is implemented in assembly to access low level register.
 */
u32
OS_CPU_EnterCritical(void);

/**
 * @brief	Exit from critical section.
 * @details	This function will restore priority mask register from stack and enable interrupt.
 * @param	None.
 * @retval	None.
 *
 * @note	This function is implemented in assembly to access low level register.
 */
void
OS_CPU_ExitCritical(u32 sr);

/**
 * @brief	Perform context switch.
 * @details	This function triggers the PendSV exception which is where the real work is done.
 * @param	None.
 * @retval	None.
 *
 * @note	This function is implemented in assembly to access low level register.
 */
void
OS_CPU_CtxSw(void);


u32
OS_CPU_LeadCountZeros(u32 data);

u32
OS_CPU_TailCountZeros(u32 data);

void
OS_CPU_CtxSwHook(void);

void
OS_CPU_StartHighRdy(void);

/**
 * @brief	Handle PendSV Exception.
 * @details	This function will handle exception that triggered to request task context switch.
 * @param	None.
 * @retval	None.
 *
 * @note	This function is implemented in assembly to access low level register.
 */
void
OS_CPU_PendSVHandler(void);

void
OS_CPU_SysTickHandler(void);

os_tcb_t
OS_CPU_GetTCBRdy(os_priority_t prio);

extern  stack_t   OS_CPU_ExceptStk[OS_CPU_EXCEPT_STK_SIZE];
extern  stack_t  *OS_CPU_ExceptStkBase;

#ifdef __cplusplus
}
#endif

#endif /* OS_CPU_H_ */

/*****************************END OF FILE**************************************/
