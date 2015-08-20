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
#include "stm32f4xx.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

#if !defined(OS_CPU_STACK_GROWING_DOWN)
#define	OS_CPU_STACK_GROWING_DOWN	1U				/*!< Using stack growing down */
#endif

#if !defined(OS_CPU_PENDSV_PRIO)
#define	OS_CPU_PENDSV_PRIO			0xFF			/*!< Set Pend SV priority (0xFF is lowest) */
#endif

#if (__FPU_USED > 0U)
#define	OS_CPU_FP_EN				OS_ENABLE		/*!< Set enable floating point */
#else
#define	OS_CPU_FP_EN				OS_DISABLE		/*!< Set disable floating point */
#endif

/* Private macro -------------------------------------------------------------*/
#if (OS_CPU_STACK_GROWING_DOWN == OS_ENABLE)
#define	OS_CPU_STK_PUSH(stk)	(--stk)
#define	OS_CPU_STK_POP(stk)		(stk++)
#else
#define	OS_CPU_STK_PUSH(stk)	(++stk)
#define	OS_CPU_STK_POP(stk)		(stk--)
#endif

/* Private variables ---------------------------------------------------------*/

stack_t   OS_CPU_ExceptStk[OS_CPU_EXCEPT_STK_SIZE];
stack_t  *OS_CPU_ExceptStkBase;

extern u32				gOS_Running;
extern os_priority_t	gOS_CurrentPrio;
extern os_priority_t	gOS_HighRdyPrio;
extern os_tcb_t			*gOS_CurrentTCB;
extern os_tcb_t			*gOS_HighRdyTCB;

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
	stack_t	*pl_stk = NULL;
	u32		ulTskSize = pptcb->uStkSize;

#if (OS_CPU_STACK_GROWING_DOWN == OS_ENABLE)
	pptcb->pStack += ulTskSize;		/* Point to last emtry of stack on growing down direction */
#endif

	/* Clear stack.
	 */
	pl_stk = pptcb->pStack;
	while(ulTskSize-- != 0)
		*OS_CPU_STK_PUSH(pl_stk) = 0;

	/*
	 * Initial stack same as task context switch.
	 */
    pl_stk	= pptcb->pStack;                                 						/* Load stack pointer                                   */

    																				/* Registers stacked as if auto-saved on exception      */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x01000000uL;                          		/* xPSR - Set bit 28 to 1 for thumb mode                */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)pptcb->tTask;                            	/* PC - Set program counter to task address             */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)OS_Task_Return;                         	/* R14 (LR)                                             */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x12121212uL;                          		/* R12                                                  */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x03030303uL;                          		/* R3                                                   */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x02020202uL;                          		/* R2                                                   */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x01010101uL;                          		/* R1                                                   */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)pptcb->pArg;                             	/* R0 : argument                                        */

                                                                 					/* Remaining registers saved on process stack           */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x11111111uL;                          		/* R11                                                  */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x10101010uL;                          		/* R10                                                  */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x09090909uL;                          		/* R9                                                   */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x08080808uL;                          		/* R8                                                   */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x07070707uL;                          		/* R7                                                   */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x06060606uL;                          		/* R6                                                   */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x05050505uL;                          		/* R5                                                   */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x04040404uL;                          		/* R4                                                   */

#if (OS_CPU_FP_EN != OS_DISABLE)
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x02000000u;                         		/* FPSCR                                                */
                                                            						/* Initialize S0-S31 floating point registers           */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x41F80000u;                         		/* S31                                                  */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x41F00000u;                         		/* S30                                                  */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x41E80000u;                         		/* S29                                                  */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x41E00000u;                         		/* S28                                                  */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x41D80000u;                         		/* S27                                                  */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x41D00000u;                         		/* S26                                                  */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x41C80000u;                         		/* S25                                                  */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x41C00000u;                         		/* S24                                                  */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x41B80000u;                         		/* S23                                                  */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x41B00000u;                         		/* S22                                                  */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x41A80000u;                         		/* S21                                                  */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x41A00000u;                         		/* S20                                                  */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x41980000u;                         		/* S19                                                  */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x41900000u;                         		/* S18                                                  */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x41880000u;                         		/* S17                                                  */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x41800000u;                         		/* S16                                                  */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x41700000u;                         		/* S15                                                  */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x41600000u;                         		/* S14                                                  */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x41500000u;                         		/* S13                                                  */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x41400000u;                         		/* S12                                                  */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x41300000u;                         		/* S11                                                  */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x41200000u;                         		/* S10                                                  */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x41100000u;                        	 	/* S9                                                   */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x41000000u;                         		/* S8                                                   */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x40E00000u;                         		/* S7                                                   */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x40C00000u;                         		/* S6                                                   */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x40A00000u;                         		/* S5                                                   */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x40800000u;                         		/* S4                                                   */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x40400000u;                         		/* S3                                                   */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x40000000u;                         		/* S2                                                   */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x3F800000u;                         		/* S1                                                   */
    *OS_CPU_STK_PUSH(pl_stk) = (stack_t)0x00000000u;                         		/* S0                                                   */
#endif

    /* Set back current stack pointer */
    pptcb->pStack = pl_stk;
}

void OS_CPU_StartCtxSw(void)
{
	/* Set PendSV Priority */
	CPU_CORE_PendSVInit(OS_CPU_PENDSV_PRIO);

	/* Set Process Stack Pointer to 0 */
	CPU_CORE_SetPSP(0);

	/* Set Main Stack Pointer */
	CPU_CORE_SetMSP((CPU_DATA)OS_CPU_ExceptStk);

	/* Set OS Running flag */
	gOS_Running = OS_TRUE;

	/* Set Pend SV interrupt enable */
	CPU_CORE_SetPendSVIntEn();

	/* Enable interrupt */
	OS_CPU_IntEn();
}

/**
 * @brief	Perform context switch.
 * @details	This function triggers the PendSV exception which is where the real work is done.
 */
#define OS_CPU_CtxSw()	CPU_CORE_SetPendSVIntEn()

void
OS_ISR_PendSV_Handler(void)
{
	register stack_t *stk;
	register CPU_DATA lr;

	/* Disable interrupt */
	OS_CPU_IntDis();

	/* Get current process stack pointer */
	stk = (stack_t *)CPU_CORE_GetPSP();

	/* Save remaining registers (r4-r11) to stack */
	stk = (stack_t *)CPU_CORE_SaveRemainReg((CPU_DATA)stk);

	/* Switch to higher priority */
	gOS_CurrentPrio = gOS_HighRdyPrio;
	gOS_CurrentTCB = gOS_HighRdyTCB;

	gOS_CurrentTCB->pStack = (stack_t *)CPU_CORE_RestoreRemainReg((CPU_DATA)gOS_CurrentTCB->pStack);
	CPU_CORE_SetPSP((CPU_DATA)gOS_CurrentTCB->pStack);

	/* Get current link return */
	lr = CPU_CORE_GetLR();
	lr |= 0xF4;

	/* Enable interrupt */
	OS_CPU_IntEn();
}

/*****************************END OF FILE**************************************/
