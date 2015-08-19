
@********************************************************************************************************
@                                          PUBLIC FUNCTIONS
@********************************************************************************************************
	@ External references
    .extern  sOS_Running
    .extern  sOS_CurrentPrio
    .extern  sOS_HighRdyPrio
    .extern  spOS_CurentTCB
    .extern  spOS_HighRdyTCB
    .extern  OS_CPU_CtxSwHook
    .extern  OS_CPU_ExceptStkBase
    .extern  OS_CPU_StartHighRdy

	@ Functions declared in this file
    .global  OS_CPU_EnterCritical
    .global  OS_CPU_ExitCritical
    .global  OS_CPU_CtxSw
    .global  OS_CPU_LeadCountZeros
    .global  OS_CPU_TailCountZeros
    .global	 OS_CPU_StartHighRdy
    .global  OS_ISR_PendSV_Handler			@ PendSV ISR Handler

@********************************************************************************************************
@                                               EQUATES
@********************************************************************************************************

.equ NVIC_INT_CTRL,   0xE000ED04                              @ Interrupt control state register.
.equ NVIC_SYSPRI14,   0xE000ED22                              @ System priority register (priority 14).
.equ NVIC_PENDSV_PRI, 0xFF                                    @ PendSV priority value (lowest).
.equ NVIC_PENDSVSET,  0x10000000                              @ Value to trigger PendSV exception.

@********************************************************************************************************
@                                     CODE GENERATION DIRECTIVES
@********************************************************************************************************

.text
.align 2
.thumb
.syntax unified

@********************************************************************************************************
@                                   ENTER CRITICAL SECTION
@********************************************************************************************************
.thumb_func
OS_CPU_EnterCritical:
    MRS     R0, PRIMASK
	@PUSH	{R0}
    CPSID   I
    BX      LR

@********************************************************************************************************
@                                   EXIT CRITICAL SECTION
@********************************************************************************************************
.thumb_func
OS_CPU_ExitCritical:
	@POP		{R0}
    MSR     PRIMASK, R0
    BX      LR

@********************************************************************************************************
@                                   EXIT CRITICAL SECTION
@********************************************************************************************************
.thumb_func
OS_CPU_CtxSw:
    LDR     R0, =NVIC_INT_CTRL                                  @ Trigger the PendSV exception (causes context switch)
    LDR     R1, =NVIC_PENDSVSET
    STR     R1, [R0]
    BX      LR


.thumb_func
OS_CPU_LeadCountZeros:
        RBIT    R0, R0                          @ Reverse bits
        CLZ     R0, R0                          @ Count trailing zeros
        BX      LR

.thumb_func
OS_CPU_TailCountZeros:
        RBIT    R0, R0                          @ Reverse bits
        CLZ     R0, R0                          @ Count trailing zeros
        BX      LR

@********************************************************************************************************
@                                   START MULTITASKING
@********************************************************************************************************
.thumb_func
OS_CPU_StartHighRdy:
    LDR     R0, =NVIC_SYSPRI14                                  @ Set the PendSV exception priority
    LDR     R1, =NVIC_PENDSV_PRI
    STRB    R1, [R0]

    MOVS    R0, #0                                              @ Set the PSP to 0 for initial context switch call
    MSR     PSP, R0

    LDR     R0, =OS_CPU_ExceptStkBase                           @ Initialize the MSP to the OS_CPU_ExceptStkBase
    LDR     R1, [R0]
    MSR     MSP, R1

    LDR     R0, =sOS_Running                                    @ sOS_Running = TRUE
    MOVS    R1, #1
    STRB    R1, [R0]

    LDR     R0, =NVIC_INT_CTRL                                  @ Trigger the PendSV exception (causes context switch)
    LDR     R1, =NVIC_PENDSVSET
    STR     R1, [R0]

    CPSIE   I                                                   @ Enable interrupts at processor level

OSStartHang:
    B       OSStartHang                                         @ Should never get here

@********************************************************************************************************
@                                   HANDLE PendSV EXCEPTION
@********************************************************************************************************
.thumb_func
OS_ISR_PendSV_Handler:
    CPSID   I                                                   @ Prevent interruption during context switch
    MRS     R0, PSP                                             @ PSP is process stack pointer
    CBZ     R0, OS_ISR_PendSV_Handler_nosave                    @ Skip register save the first time

    SUBS    R0, R0, #0x20                                       @ Save remaining regs r4-11 on process stack
    STM     R0, {R4-R11}

    LDR     R1, =spOS_CurentTCB                                 @ spOS_CurentTCB->pStack = SP;
    LDR     R1, [R1]
    STR     R0, [R1]                                            @ R0 is SP of process being switched out

                                                                @ At this point, entire context of process has been saved
OS_ISR_PendSV_Handler_nosave:
    PUSH    {R14}                                               @ Save LR exc_return value
    LDR     R0, =OS_CPU_CtxSwHook                               @ OS_CPU_CtxSwHook();
    BLX     R0
    POP     {R14}

    LDR     R0, =sOS_CurrentPrio                                @ sOS_CurrentPrio = sOS_HighRdyPrio;
    LDR     R1, =sOS_HighRdyPrio
    LDRB    R2, [R1]
    STRB    R2, [R0]

    LDR     R0, =spOS_CurentTCB                                 @ spOS_CurentTCB  = spOS_HighRdyTCB;
    LDR     R1, =spOS_HighRdyTCB
    LDR     R2, [R1]
    STR     R2, [R0]

    LDR     R0, [R2]                                            @ R0 is new process SP; SP = spOS_HighRdyTCB->pStack;
    LDM     R0, {R4-R11}                                        @ Restore r4-11 from new process stack
    ADDS    R0, R0, #0x20
    MSR     PSP, R0                                             @ Load PSP with new process SP
    ORR     LR, LR, #0xF4                                       @ Ensure exception return uses process stack
    CPSIE   I
    BX      LR                                                  @ Exception return will restore remaining context

.end
