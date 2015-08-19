/**
 ******************************************************************************
 * @file	os_isr_vectors.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	19-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "os_isr.h"
#include "cortexm/ExceptionHandlers.h"

/* Private typedef -----------------------------------------------------------*/
typedef void (*os_isr_t)(void);

/* Private define ------------------------------------------------------------*/
#define	OS_ISR_CORE_NBR		16
#define	OS_ISR_IRQ_NBR		82
#define	OS_ISR_TOTAL_NBR	(OS_ISR_CORE_NBR + OS_ISR_IRQ_NBR)

/* Private macro -------------------------------------------------------------*/
#define	OS_ISR(name)	(OS_ISR_##name)

#define	OS_ISR_ATT_WEAK_ALIAS(name)							\
	void 													\
 	__attribute__ ((section(".after_vectors"),weak))		\
	ISR_##name(void) 										\
	{														\
	}														\
															\
	void 													\
 	__attribute__ ((section(".after_vectors"),weak))									\
	OS_ISR_##name(void)										\
	{														\
		OS_ISR_Enter();										\
		ISR_##name();										\
		OS_ISR_Exit();										\
	}

/* Define Core Level ISR for Cortex-M4 */
/*OS_ISR_ATT_WEAK_ALIAS(Reset_Handler)
OS_ISR_ATT_WEAK_ALIAS(NMI_Handler)
OS_ISR_ATT_WEAK_ALIAS(HardFault_Handler)
OS_ISR_ATT_WEAK_ALIAS(MemManage_Handler)
OS_ISR_ATT_WEAK_ALIAS(BusFault_Handler)
OS_ISR_ATT_WEAK_ALIAS(UsageFault_Handler)
OS_ISR_ATT_WEAK_ALIAS(SVC_Handler)
OS_ISR_ATT_WEAK_ALIAS(DebugMon_Handler)*/
OS_ISR_ATT_WEAK_ALIAS(PendSV_Handler)
OS_ISR_ATT_WEAK_ALIAS(SysTick_Handler)

/* Define Chip Level ISR for STM32F4xx*/
OS_ISR_ATT_WEAK_ALIAS(WWDG_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(PVD_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(TAMP_STAMP_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(RTC_WKUP_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(FLASH_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(RCC_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(EXTI0_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(EXTI1_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(EXTI2_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(EXTI3_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(EXTI4_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(DMA1_Stream0_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(DMA1_Stream1_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(DMA1_Stream2_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(DMA1_Stream3_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(DMA1_Stream4_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(DMA1_Stream5_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(DMA1_Stream6_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(ADC_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(CAN1_TX_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(CAN1_RX0_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(CAN1_RX1_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(CAN1_SCE_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(EXTI9_5_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(TIM1_BRK_TIM9_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(TIM1_UP_TIM10_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(TIM1_TRG_COM_TIM11_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(TIM1_CC_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(TIM2_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(TIM3_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(TIM4_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(I2C1_EV_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(I2C1_ER_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(I2C2_EV_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(I2C2_ER_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(SPI1_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(SPI2_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(USART1_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(USART2_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(USART3_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(EXTI15_10_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(RTC_Alarm_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(OTG_FS_WKUP_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(TIM8_BRK_TIM12_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(TIM8_UP_TIM13_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(TIM8_TRG_COM_TIM14_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(TIM8_CC_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(DMA1_Stream7_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(FSMC_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(SDIO_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(TIM5_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(SPI3_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(UART4_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(UART5_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(TIM6_DAC_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(TIM7_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(DMA2_Stream0_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(DMA2_Stream1_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(DMA2_Stream2_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(DMA2_Stream3_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(DMA2_Stream4_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(ETH_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(ETH_WKUP_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(CAN2_TX_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(CAN2_RX0_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(CAN2_RX1_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(CAN2_SCE_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(OTG_FS_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(DMA2_Stream5_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(DMA2_Stream6_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(DMA2_Stream7_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(USART6_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(I2C3_EV_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(I2C3_ER_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(OTG_HS_EP1_OUT_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(OTG_HS_EP1_IN_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(OTG_HS_WKUP_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(OTG_HS_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(DCMI_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(CRYP_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(HASH_RNG_IRQHandler)
OS_ISR_ATT_WEAK_ALIAS(FPU_IRQHandler)

/* Private variables ---------------------------------------------------------*/
#if (OS_ISR_VECTOR_TABLE_EN != OS_DISABLE)
extern unsigned int _estack;

__attribute__ ((section(".isr_vector"),used))
os_isr_t	gOS_ISRVectorTable[] =
{
			  /* ISR Core Level - Cortex-M4 */
			  (os_isr_t) &_estack,                      // The initial stack pointer
			  Reset_Handler,                 	// The reset handler
			  NMI_Handler,                    	// The NMI handler
			  HardFault_Handler,                // The hard fault handler
			  MemManage_Handler,               	// The MPU fault handler
			  BusFault_Handler,            		// The bus fault handler
			  UsageFault_Handler,          		// The usage fault handler
		      0,                                        // Reserved
		      0,                                        // Reserved
		      0,                                        // Reserved
		      0,                                        // Reserved
			  SVC_Handler,                      // SVCall handler
			  DebugMon_Handler,             	// Debug monitor handler
		      0,                                        // Reserved
			  OS_ISR(PendSV_Handler),                  	// The PendSV handler
			  OS_ISR(SysTick_Handler),       			// The SysTick handler

			  /* ISR Chip Level - STM32F4xx */
			  OS_ISR(WWDG_IRQHandler),        			// Window WatchDog
			  OS_ISR(PVD_IRQHandler), 					// PVD through EXTI Line detection
			  OS_ISR(TAMP_STAMP_IRQHandler),  			// Tamper and TimeStamps through the EXTI line
			  OS_ISR(RTC_WKUP_IRQHandler),    			// RTC Wakeup through the EXTI line
			  OS_ISR(FLASH_IRQHandler),       			// FLASH
			  OS_ISR(RCC_IRQHandler), 					// RCC
			  OS_ISR(EXTI0_IRQHandler),       			// EXTI Line0
			  OS_ISR(EXTI1_IRQHandler),       			// EXTI Line1
			  OS_ISR(EXTI2_IRQHandler),       			// EXTI Line2
			  OS_ISR(EXTI3_IRQHandler),       			// EXTI Line3
			  OS_ISR(EXTI4_IRQHandler),       			// EXTI Line4
			  OS_ISR(DMA1_Stream0_IRQHandler),        	// DMA1 Stream 0
			  OS_ISR(DMA1_Stream1_IRQHandler),        	// DMA1 Stream 1
			  OS_ISR(DMA1_Stream2_IRQHandler),        	// DMA1 Stream 2
			  OS_ISR(DMA1_Stream3_IRQHandler),        	// DMA1 Stream 3
			  OS_ISR(DMA1_Stream4_IRQHandler),        	// DMA1 Stream 4
			  OS_ISR(DMA1_Stream5_IRQHandler),        	// DMA1 Stream 5
			  OS_ISR(DMA1_Stream6_IRQHandler),        	// DMA1 Stream 6
			  OS_ISR(ADC_IRQHandler), 					// ADC1

			  /* ISR Chip Level - STM32F407xx */
			  OS_ISR(CAN1_TX_IRQHandler),     			// CAN1 TX
			  OS_ISR(CAN1_RX0_IRQHandler),    			// CAN1 RX0
			  OS_ISR(CAN1_RX1_IRQHandler),    			// CAN1 RX1
			  OS_ISR(CAN1_SCE_IRQHandler),    			// CAN1 SCE
			  OS_ISR(EXTI9_5_IRQHandler),     			// External Line[9:5]s
			  OS_ISR(TIM1_BRK_TIM9_IRQHandler),       	// TIM1 Break and TIM9
			  OS_ISR(TIM1_UP_TIM10_IRQHandler),       	// TIM1 Update and TIM10
			  OS_ISR(TIM1_TRG_COM_TIM11_IRQHandler),  	// TIM1 Trigger and Commutation and TIM11
			  OS_ISR(TIM1_CC_IRQHandler),     			// TIM1 Capture Compare
			  OS_ISR(TIM2_IRQHandler),        			// TIM2
			  OS_ISR(TIM3_IRQHandler),        			// TIM3
			  OS_ISR(TIM4_IRQHandler),        			// TIM4
			  OS_ISR(I2C1_EV_IRQHandler),     			// I2C1 Event
			  OS_ISR(I2C1_ER_IRQHandler),     			// I2C1 Error
			  OS_ISR(I2C2_EV_IRQHandler),     			// I2C2 Event
			  OS_ISR(I2C2_ER_IRQHandler),     			// I2C2 Error
			  OS_ISR(SPI1_IRQHandler),        			// SPI1
			  OS_ISR(SPI2_IRQHandler),        			// SPI2
			  OS_ISR(USART1_IRQHandler),      			// USART1
			  OS_ISR(USART2_IRQHandler),      			// USART2
			  OS_ISR(USART3_IRQHandler),      			// USART3
			  OS_ISR(EXTI15_10_IRQHandler),   			// External Line[15:10]s
			  OS_ISR(RTC_Alarm_IRQHandler),   			// RTC Alarm (A and B) through EXTI Line
			  OS_ISR(OTG_FS_WKUP_IRQHandler), 			// USB OTG FS Wakeup through EXTI line
			  OS_ISR(TIM8_BRK_TIM12_IRQHandler),     	// TIM8 Break and TIM12
			  OS_ISR(TIM8_UP_TIM13_IRQHandler),       	// TIM8 Update and TIM13
			  OS_ISR(TIM8_TRG_COM_TIM14_IRQHandler),  	// TIM8 Trigger and Commutation and TIM14
			  OS_ISR(TIM8_CC_IRQHandler),     			// TIM8 Capture Compare
			  OS_ISR(DMA1_Stream7_IRQHandler),        	// DMA1 Stream7
			  OS_ISR(FSMC_IRQHandler),        			// FSMC
			  OS_ISR(SDIO_IRQHandler),        			// SDIO
			  OS_ISR(TIM5_IRQHandler),        			// TIM5
			  OS_ISR(SPI3_IRQHandler),        			// SPI3
			  OS_ISR(UART4_IRQHandler),      	 		// UART4
			  OS_ISR(UART5_IRQHandler),       			// UART5
			  OS_ISR(TIM6_DAC_IRQHandler),    			// TIM6 and DAC1&2 underrun errors
			  OS_ISR(TIM7_IRQHandler),        			// TIM7
			  OS_ISR(DMA2_Stream0_IRQHandler),        	// DMA2 Stream 0
			  OS_ISR(DMA2_Stream1_IRQHandler),        	// DMA2 Stream 1
			  OS_ISR(DMA2_Stream2_IRQHandler),        	// DMA2 Stream 2
			  OS_ISR(DMA2_Stream3_IRQHandler),        	// DMA2 Stream 3
			  OS_ISR(DMA2_Stream4_IRQHandler),        	// DMA2 Stream 4
			  OS_ISR(ETH_IRQHandler), 					// Ethernet
			  OS_ISR(ETH_WKUP_IRQHandler),    			// Ethernet Wakeup through EXTI line
			  OS_ISR(CAN2_TX_IRQHandler),     			// CAN2 TX
			  OS_ISR(CAN2_RX0_IRQHandler),    			// CAN2 RX0
			  OS_ISR(CAN2_RX1_IRQHandler),    			// CAN2 RX1
			  OS_ISR(CAN2_SCE_IRQHandler),    			// CAN2 SCE
			  OS_ISR(OTG_FS_IRQHandler),      			// USB OTG FS
			  OS_ISR(DMA2_Stream5_IRQHandler),        	// DMA2 Stream 5
			  OS_ISR(DMA2_Stream6_IRQHandler),        	// DMA2 Stream 6
			  OS_ISR(DMA2_Stream7_IRQHandler),        	// DMA2 Stream 7
			  OS_ISR(USART6_IRQHandler),      			// USART6
			  OS_ISR(I2C3_EV_IRQHandler),     			// I2C3 event
			  OS_ISR(I2C3_ER_IRQHandler),     			// I2C3 error
			  OS_ISR(OTG_HS_EP1_OUT_IRQHandler),      	// USB OTG HS End Point 1 Out
			  OS_ISR(OTG_HS_EP1_IN_IRQHandler),       	// USB OTG HS End Point 1 In
			  OS_ISR(OTG_HS_WKUP_IRQHandler), 			// USB OTG HS Wakeup through EXTI
			  OS_ISR(OTG_HS_IRQHandler),      			// USB OTG HS
			  OS_ISR(DCMI_IRQHandler),        			// DCMI
			  OS_ISR(CRYP_IRQHandler),      			// CRYP crypto
			  OS_ISR(HASH_RNG_IRQHandler),    			// Hash and Rng
			  OS_ISR(FPU_IRQHandler) 					// FPU
};
#endif

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
 * @brief	Default Handler.
 */
void
__attribute__((weak))
ISR_Default_Handler(void)
{
	/* Empty */
}

/*****************************END OF FILE**************************************/
