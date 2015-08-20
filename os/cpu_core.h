/**
 ******************************************************************************
 * @file	cpu_core.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	20-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CPU_CORE_H_
#define CPU_CORE_H_

#ifdef __cplusplus
 extern "C" {
#endif

#ifdef __cplusplus
  #define   __I__     volatile             /*!< Defines 'read only' permissions                 */
#else
  #define   __I__     volatile const       /*!< Defines 'read only' permissions                 */
#endif
#define     __O__     volatile             /*!< Defines 'write only' permissions                */
#define     __IO_     volatile             /*!< Defines 'read / write' permissions              */


 /*
  * ************************************************************************************************
  * CPU Types
  * ************************************************************************************************
  */
 /**
  * @brief	General CPU types define.
  */
 typedef            void        CPU_VOID;
 typedef            char        CPU_CHAR;                        /*  8-bit character                                     */
 typedef  unsigned  char        CPU_BOOLEAN;                     /*  8-bit boolean or logical                            */
 typedef  unsigned  char        CPU_INT08U;                      /*  8-bit unsigned integer                              */
 typedef    signed  char        CPU_INT08S;                      /*  8-bit   signed integer                              */
 typedef  unsigned  short       CPU_INT16U;                      /* 16-bit unsigned integer                              */
 typedef    signed  short       CPU_INT16S;                      /* 16-bit   signed integer                              */
 typedef  unsigned  int         CPU_INT32U;                      /* 32-bit unsigned integer                              */
 typedef    signed  int         CPU_INT32S;                      /* 32-bit   signed integer                              */
 typedef  unsigned  long  long  CPU_INT64U;                      /* 64-bit unsigned integer                              */
 typedef    signed  long  long  CPU_INT64S;                      /* 64-bit   signed integer                              */

 typedef            float       CPU_FP32;                        /* 32-bit floating point                                */
 typedef            double      CPU_FP64;                        /* 64-bit floating point                                */

 typedef  volatile  CPU_INT08U  CPU_REG08;                       /*  8-bit register                                      */
 typedef  volatile  CPU_INT16U  CPU_REG16;                       /* 16-bit register                                      */
 typedef  volatile  CPU_INT32U  CPU_REG32;                       /* 32-bit register                                      */
 typedef  volatile  CPU_INT64U  CPU_REG64;                       /* 64-bit register                                      */

 /**
  * @brief	Using CPU types define.
  * 		Must define as CPU using for OS.
  */
 typedef			CPU_REG32	CPU_REG;
 typedef			CPU_INT32U	CPU_DATA;

 /*
  * ************************************************************************************************
  * CPU Core Registers
  * ************************************************************************************************
  */

 /**
  * @brief	Structure type to access the Nested Vectored Interrupt Controller (NVIC).
  */
 typedef struct
 {
	 CPU_REG ISER[8];                 /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register           */
	 CPU_REG RESERVED0[24];
	 CPU_REG ICER[8];                 /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register         */
	 CPU_REG RSERVED1[24];
	 CPU_REG ISPR[8];                 /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register          */
	 CPU_REG RESERVED2[24];
	 CPU_REG ICPR[8];                 /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register        */
	 CPU_REG RESERVED3[24];
	 CPU_REG IABR[8];                 /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register           */
	 CPU_REG RESERVED4[56];
	 CPU_REG08  IP[240];              /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
	 CPU_REG RESERVED5[644];
	 CPU_REG STIR;                    /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register     */
 }  CPU_REG_NVIC_Type;


 /**
  * @brief  Structure type to access the System Control Block (SCB).
  */
 typedef struct
 {
	CPU_REG CPUID;                   /*!< Offset: 0x000 (R/ )  CPUID Base Register                                   */
	CPU_REG ICSR;                    /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register                  */
	CPU_REG VTOR;                    /*!< Offset: 0x008 (R/W)  Vector Table Offset Register                          */
	CPU_REG AIRCR;                   /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register      */
	CPU_REG SCR;                     /*!< Offset: 0x010 (R/W)  System Control Register                               */
	CPU_REG CCR;                     /*!< Offset: 0x014 (R/W)  Configuration Control Register                        */
	CPU_REG08 SHP[12];               /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
	CPU_REG SHCSR;                   /*!< Offset: 0x024 (R/W)  System Handler Control and State Register             */
	CPU_REG CFSR;                    /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register                    */
	CPU_REG HFSR;                    /*!< Offset: 0x02C (R/W)  HardFault Status Register                             */
	CPU_REG DFSR;                    /*!< Offset: 0x030 (R/W)  Debug Fault Status Register                           */
	CPU_REG MMFAR;                   /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register                      */
	CPU_REG BFAR;                    /*!< Offset: 0x038 (R/W)  BusFault Address Register                             */
	CPU_REG AFSR;                    /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register                       */
	CPU_REG PFR[2];                  /*!< Offset: 0x040 (R/ )  Processor Feature Register                            */
	CPU_REG DFR;                     /*!< Offset: 0x048 (R/ )  Debug Feature Register                                */
	CPU_REG ADR;                     /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register                            */
	CPU_REG MMFR[4];                 /*!< Offset: 0x050 (R/ )  Memory Model Feature Register                         */
	CPU_REG ISAR[5];                 /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register                   */
	CPU_REG RESERVED0[5];
	CPU_REG CPACR;                   /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register                   */
 } CPU_REG_SCB_Type;


#define CPU_REG_SCB_ICSR_PENDSVSET_POS             28                                             /*!< SCB ICSR: PENDSVSET Position */
#define CPU_REG_SCB_ICSR_PENDSVSET_MSK             (1UL << SCB_ICSR_PENDSVSET_Pos)                /*!< SCB ICSR: PENDSVSET Mask */

 /**
  * @brief  Structure type to access the System Timer (SysTick).
  */
 typedef struct
 {
	CPU_REG CTRL;                    /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
	CPU_REG LOAD;                    /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register       */
	CPU_REG VAL;                     /*!< Offset: 0x008 (R/W)  SysTick Current Value Register      */
	CPU_REG CALIB;                   /*!< Offset: 0x00C (R/ )  SysTick Calibration Register        */
 } CPU_REG_SysTick_Type;

 /*
  * ************************************************************************************************
  * CPU Core Memory mapping
  * ************************************************************************************************
  */
 /* Memory mapping of Cortex-M4 Hardware */
 #define CPU_REG_SCS_BASE			(0xE000E000UL)						/*!< System Control Space Base Address  */
 #define CPU_REG_SysTick_BASE		(CPU_REG_SCS_BASE +  0x0010UL)		/*!< SysTick Base Address               */
 #define CPU_REG_NVIC_BASE			(CPU_REG_SCS_BASE +  0x0100UL)		/*!< NVIC Base Address                  */
 #define CPU_REG_SCB_BASE			(CPU_REG_SCS_BASE +  0x0D00UL)		/*!< System Control Block Base Address  */

 #define CPU_REG_SCB				((CPU_REG_SCB_Type       *)CPU_REG_SCB_BASE      )   /*!< SCB configuration struct           */
 #define CPU_REG_SysTick			((CPU_REG_SysTick_Type   *)CPU_REG_SysTick_BASE  )   /*!< SysTick configuration struct       */
 #define CPU_REG_NVIC				((CPU_REG_NVIC_Type      *)CPU_REG_NVIC_BASE     )   /*!< NVIC configuration struct          */

 /*
  * ************************************************************************************************
  * CPU Core Functions
  * ************************************************************************************************
  */
 /**
  * @brief	Set Process Stack Pointer (PSP).
  * 		This function assigns the given value to the Process Stack Pointer (PSP).
  * @param [in]    topOfProcStack  Process Stack Pointer value to set
  */
 static inline void
 __attribute__((always_inline))
 CPU_CORE_SetPSP(register CPU_DATA topOfProcStack)
 {
 	__asm volatile ("MSR psp,%0\n" : : "r" (topOfProcStack) );
 }

 /**
  * @brief	Get Process Stack Pointer (PSP).
  * 		This function returns the current value of the Process Stack Pointer (PSP).
  */
 static inline CPU_DATA
 __attribute__((always_inline))
 CPU_CORE_GetPSP(void)
 {
	  register CPU_DATA result;

	  __asm volatile ("MRS %0, psp\n"  : "=r" (result) );

	  return(result);
 }
 /**
  * @brief	Set Main Stack Pointer (MSP).
  * 		This function assigns the given value to the Main Stack Pointer (MSP).
  * @param [in]    topOfProcStack  Process Stack Pointer value to set
  */
 static inline void
 __attribute__((always_inline))
 CPU_CORE_SetMSP(register CPU_DATA topOfProcStack)
 {
 	__asm volatile ("MSR msp,%0\n" : : "r" (topOfProcStack) );
 }

 /**
  * @brief	Get Process Stack Pointer (MSP).
  * 		This function returns the current value of the Main Stack Pointer (MSP).
  */
 static inline CPU_DATA
 __attribute__((always_inline))
 CPU_CORE_GetMSP(void)
 {
	  register CPU_DATA result;

	  __asm volatile ("MRS %0, msp\n"  : "=r" (result) );

	  return(result);
 }

 static inline void
 __attribute__((always_inline))
 CPU_CORE_SetLR(register CPU_DATA lr)
 {
 	__asm volatile ("MOV lr,%0\n" : : "r" (lr) );
 }

 static inline CPU_DATA
 __attribute__((always_inline))
 CPU_CORE_GetLR(void)
 {
	  register CPU_DATA result;

	  __asm volatile ("MOV %0, lr\n"  : "=r" (result) );

	  return(result);
 }


 void
 CPU_CORE_SystemInit(void);

 void
 CPU_CORE_SysTickInit(CPU_DATA FreqHz, CPU_DATA Prio);

 CPU_DATA
 CPU_CORE_GetClkFreq(void);

 void
 CPU_CORE_PendSVInit(CPU_DATA Prio);

 static inline void
 __attribute__((always_inline))
 CPU_CORE_SetPendSVIntEn(void)
 {
	 CPU_REG_SCB->ICSR |= (1UL << 24);
 }

 static inline CPU_DATA
 __attribute__((always_inline))
 CPU_CORE_SaveRemainReg(register CPU_DATA stk_ptr)
 {
	  __asm volatile ("STMFD %0!, {r4-r11}\n" : "+r" (stk_ptr) );

	  return(stk_ptr);
 }

 static inline CPU_DATA
 __attribute__((always_inline))
 CPU_CORE_RestoreRemainReg(register CPU_DATA stk_ptr)
 {
	  __asm volatile ("STMFD %0!, {r4-r11}\n" : "+r" (stk_ptr) );

	  return(stk_ptr);
 }

#ifdef __cplusplus
}
#endif

#endif /* CPU_CORE_H_ */

/*****************************END OF FILE**************************************/
