/**
 ******************************************************************************
 * @file	os_cpu.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	18-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "os_cpu.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

stack_t   OS_CPU_ExceptStk[OS_CPU_EXCEPT_STK_SIZE];
stack_t  *OS_CPU_ExceptStkBase;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
void
OS_CPU_Init(void)
{
    u32   	size;
    stack_t	*pstk;

                                                                /* Clear exception stack for stack checking.            */
    pstk = OS_CPU_ExceptStk;
    size = OS_CPU_EXCEPT_STK_SIZE;
    while (size > 0u)
    {
        size--;
       *pstk++ = (stack_t)0;
    }

                                                                /* Align the ISR stack to 8-bytes                       */
    OS_CPU_ExceptStkBase = (stack_t *)&OS_CPU_ExceptStk[OS_CPU_EXCEPT_STK_SIZE];
    OS_CPU_ExceptStkBase = (stack_t *)((stack_t)(OS_CPU_ExceptStkBase) & 0xFFFFFFF8);
}

void
OS_CPU_InitStack(os_tcb_t *pptcb)
{
	stack_t	*pl_stk = pptcb->pStack;
	u32		ulTskSize = pptcb->uStkSize;

	/* Clear stack.
	 * STM32F4 with growing down stack.
	 */
	while(ulTskSize-- != 0)
		*(--pl_stk) = 0;

	/*
	 * Initial stack same as task context switch.
	 */
    pl_stk      = pptcb->pStack;                                 	/* Load stack pointer                                   */

    																/* Registers stacked as if auto-saved on exception      */
    *(--pl_stk) = (stack_t)0x01000000uL;                          	/* xPSR                                                 */
    *(--pl_stk) = (stack_t)pptcb->tTask;                            /* Entry Point                                          */
    *(--pl_stk) = (stack_t)OS_Task_Return;                         	/* R14 (LR)                                             */
    *(--pl_stk) = (stack_t)0x12121212uL;                          	/* R12                                                  */
    *(--pl_stk) = (stack_t)0x03030303uL;                          	/* R3                                                   */
    *(--pl_stk) = (stack_t)0x02020202uL;                          	/* R2                                                   */
    *(--pl_stk) = (stack_t)0x01010101uL;                          	/* R1                                                   */
    *(--pl_stk) = (stack_t)pptcb->pArg;                             /* R0 : argument                                        */

                                                                 	/* Remaining registers saved on process stack           */
    *(--pl_stk) = (stack_t)0x11111111uL;                          	/* R11                                                  */
    *(--pl_stk) = (stack_t)0x10101010uL;                          	/* R10                                                  */
    *(--pl_stk) = (stack_t)0x09090909uL;                          	/* R9                                                   */
    *(--pl_stk) = (stack_t)0x08080808uL;                          	/* R8                                                   */
    *(--pl_stk) = (stack_t)0x07070707uL;                          	/* R7                                                   */
    *(--pl_stk) = (stack_t)0x06060606uL;                          	/* R6                                                   */
    *(--pl_stk) = (stack_t)0x05050505uL;                          	/* R5                                                   */
    *(--pl_stk) = (stack_t)0x04040404uL;                          	/* R4                                                   */

#if (OS_CPU_ARM_FP_EN > 0u)
    *--pl_stk = (stack_t)0x02000000u;                         		/* FPSCR                                                */
                                                            		/* Initialize S0-S31 floating point registers           */
    *--pl_stk = (stack_t)0x41F80000u;                         		/* S31                                                  */
    *--pl_stk = (stack_t)0x41F00000u;                         		/* S30                                                  */
    *--pl_stk = (stack_t)0x41E80000u;                         		/* S29                                                  */
    *--pl_stk = (stack_t)0x41E00000u;                         		/* S28                                                  */
    *--pl_stk = (stack_t)0x41D80000u;                         		/* S27                                                  */
    *--pl_stk = (stack_t)0x41D00000u;                         		/* S26                                                  */
    *--pl_stk = (stack_t)0x41C80000u;                         		/* S25                                                  */
    *--pl_stk = (stack_t)0x41C00000u;                         		/* S24                                                  */
    *--pl_stk = (stack_t)0x41B80000u;                         		/* S23                                                  */
    *--pl_stk = (stack_t)0x41B00000u;                         		/* S22                                                  */
    *--pl_stk = (stack_t)0x41A80000u;                         		/* S21                                                  */
    *--pl_stk = (stack_t)0x41A00000u;                         		/* S20                                                  */
    *--pl_stk = (stack_t)0x41980000u;                         		/* S19                                                  */
    *--pl_stk = (stack_t)0x41900000u;                         		/* S18                                                  */
    *--pl_stk = (stack_t)0x41880000u;                         		/* S17                                                  */
    *--pl_stk = (stack_t)0x41800000u;                         		/* S16                                                  */
    *--pl_stk = (stack_t)0x41700000u;                         		/* S15                                                  */
    *--pl_stk = (stack_t)0x41600000u;                         		/* S14                                                  */
    *--pl_stk = (stack_t)0x41500000u;                         		/* S13                                                  */
    *--pl_stk = (stack_t)0x41400000u;                         		/* S12                                                  */
    *--pl_stk = (stack_t)0x41300000u;                         		/* S11                                                  */
    *--pl_stk = (stack_t)0x41200000u;                         		/* S10                                                  */
    *--pl_stk = (stack_t)0x41100000u;                        	 	/* S9                                                   */
    *--pl_stk = (stack_t)0x41000000u;                         		/* S8                                                   */
    *--pl_stk = (stack_t)0x40E00000u;                         		/* S7                                                   */
    *--pl_stk = (stack_t)0x40C00000u;                         		/* S6                                                   */
    *--pl_stk = (stack_t)0x40A00000u;                         		/* S5                                                   */
    *--pl_stk = (stack_t)0x40800000u;                         		/* S4                                                   */
    *--pl_stk = (stack_t)0x40400000u;                         		/* S3                                                   */
    *--pl_stk = (stack_t)0x40000000u;                         		/* S2                                                   */
    *--pl_stk = (stack_t)0x3F800000u;                         		/* S1                                                   */
    *--pl_stk = (stack_t)0x00000000u;                         		/* S0                                                   */
#endif

    /* Set back current stack pointer */
    pptcb->pStack = pl_stk;
}

void
OS_CPU_CtxSwHook(void)
{

}

/*****************************END OF FILE**************************************/
