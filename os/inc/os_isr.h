/**
 ******************************************************************************
 * @file	os_isr.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	19-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OS_ISR_H_
#define OS_ISR_H_

/* Includes ------------------------------------------------------------------*/
#include "os_types.h"

/* Preprocessors -------------------------------------------------------------*/

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
#if !defined(OS_ISR_VECTOR_TABLE_EN)
#define	OS_ISR_VECTOR_TABLE_EN		OS_ENABLE
#endif

/* Exported macro ------------------------------------------------------------*/

#define	OS_ISR_HANDLER(name)	OS_EXTERN_C void ISR_##name(void)

#define	OS_ISR_EXTERN(name)							\
	extern void ISR_##name(void);

/* Exported functions --------------------------------------------------------*/

 /* Define Core Level ISR for Cortex-M4 */
 OS_ISR_EXTERN(Reset_Handler)
 OS_ISR_EXTERN(NMI_Handler)
 OS_ISR_EXTERN(HardFault_Handler)
 OS_ISR_EXTERN(MemManage_Handler)
 OS_ISR_EXTERN(BusFault_Handler)
 OS_ISR_EXTERN(UsageFault_Handler)
 OS_ISR_EXTERN(SVC_Handler)
 OS_ISR_EXTERN(DebugMon_Handler)
 OS_ISR_EXTERN(PendSV_Handler)
 OS_ISR_EXTERN(SysTick_Handler)

 /* Define Chip Level ISR for STM32F4xx*/
 OS_ISR_EXTERN(WWDG_IRQHandler)
 OS_ISR_EXTERN(PVD_IRQHandler)
 OS_ISR_EXTERN(TAMP_STAMP_IRQHandler)
 OS_ISR_EXTERN(RTC_WKUP_IRQHandler)
 OS_ISR_EXTERN(FLASH_IRQHandler)
 OS_ISR_EXTERN(RCC_IRQHandler)
 OS_ISR_EXTERN(EXTI0_IRQHandler)
 OS_ISR_EXTERN(EXTI1_IRQHandler)
 OS_ISR_EXTERN(EXTI2_IRQHandler)
 OS_ISR_EXTERN(EXTI3_IRQHandler)
 OS_ISR_EXTERN(EXTI4_IRQHandler)
 OS_ISR_EXTERN(DMA1_Stream0_IRQHandler)
 OS_ISR_EXTERN(DMA1_Stream1_IRQHandler)
 OS_ISR_EXTERN(DMA1_Stream2_IRQHandler)
 OS_ISR_EXTERN(DMA1_Stream3_IRQHandler)
 OS_ISR_EXTERN(DMA1_Stream4_IRQHandler)
 OS_ISR_EXTERN(DMA1_Stream5_IRQHandler)
 OS_ISR_EXTERN(DMA1_Stream6_IRQHandler)
 OS_ISR_EXTERN(ADC_IRQHandler)
 OS_ISR_EXTERN(CAN1_TX_IRQHandler)
 OS_ISR_EXTERN(CAN1_RX0_IRQHandler)
 OS_ISR_EXTERN(CAN1_RX1_IRQHandler)
 OS_ISR_EXTERN(CAN1_SCE_IRQHandler)
 OS_ISR_EXTERN(EXTI9_5_IRQHandler)
 OS_ISR_EXTERN(TIM1_BRK_TIM9_IRQHandler)
 OS_ISR_EXTERN(TIM1_UP_TIM10_IRQHandler)
 OS_ISR_EXTERN(TIM1_TRG_COM_TIM11_IRQHandler)
 OS_ISR_EXTERN(TIM1_CC_IRQHandler)
 OS_ISR_EXTERN(TIM2_IRQHandler)
 OS_ISR_EXTERN(TIM3_IRQHandler)
 OS_ISR_EXTERN(TIM4_IRQHandler)
 OS_ISR_EXTERN(I2C1_EV_IRQHandler)
 OS_ISR_EXTERN(I2C1_ER_IRQHandler)
 OS_ISR_EXTERN(I2C2_EV_IRQHandler)
 OS_ISR_EXTERN(I2C2_ER_IRQHandler)
 OS_ISR_EXTERN(SPI1_IRQHandler)
 OS_ISR_EXTERN(SPI2_IRQHandler)
 OS_ISR_EXTERN(USART1_IRQHandler)
 OS_ISR_EXTERN(USART2_IRQHandler)
 OS_ISR_EXTERN(USART3_IRQHandler)
 OS_ISR_EXTERN(EXTI15_10_IRQHandler)
 OS_ISR_EXTERN(RTC_Alarm_IRQHandler)
 OS_ISR_EXTERN(OTG_FS_WKUP_IRQHandler)
 OS_ISR_EXTERN(TIM8_BRK_TIM12_IRQHandler)
 OS_ISR_EXTERN(TIM8_UP_TIM13_IRQHandler)
 OS_ISR_EXTERN(TIM8_TRG_COM_TIM14_IRQHandler)
 OS_ISR_EXTERN(TIM8_CC_IRQHandler)
 OS_ISR_EXTERN(DMA1_Stream7_IRQHandler)
 OS_ISR_EXTERN(FSMC_IRQHandler)
 OS_ISR_EXTERN(SDIO_IRQHandler)
 OS_ISR_EXTERN(TIM5_IRQHandler)
 OS_ISR_EXTERN(SPI3_IRQHandler)
 OS_ISR_EXTERN(UART4_IRQHandler)
 OS_ISR_EXTERN(UART5_IRQHandler)
 OS_ISR_EXTERN(TIM6_DAC_IRQHandler)
 OS_ISR_EXTERN(TIM7_IRQHandler)
 OS_ISR_EXTERN(DMA2_Stream0_IRQHandler)
 OS_ISR_EXTERN(DMA2_Stream1_IRQHandler)
 OS_ISR_EXTERN(DMA2_Stream2_IRQHandler)
 OS_ISR_EXTERN(DMA2_Stream3_IRQHandler)
 OS_ISR_EXTERN(DMA2_Stream4_IRQHandler)
 OS_ISR_EXTERN(ETH_IRQHandler)
 OS_ISR_EXTERN(ETH_WKUP_IRQHandler)
 OS_ISR_EXTERN(CAN2_TX_IRQHandler)
 OS_ISR_EXTERN(CAN2_RX0_IRQHandler)
 OS_ISR_EXTERN(CAN2_RX1_IRQHandler)
 OS_ISR_EXTERN(CAN2_SCE_IRQHandler)
 OS_ISR_EXTERN(OTG_FS_IRQHandler)
 OS_ISR_EXTERN(DMA2_Stream5_IRQHandler)
 OS_ISR_EXTERN(DMA2_Stream6_IRQHandler)
 OS_ISR_EXTERN(DMA2_Stream7_IRQHandler)
 OS_ISR_EXTERN(USART6_IRQHandler)
 OS_ISR_EXTERN(I2C3_EV_IRQHandler)
 OS_ISR_EXTERN(I2C3_ER_IRQHandler)
 OS_ISR_EXTERN(OTG_HS_EP1_OUT_IRQHandler)
 OS_ISR_EXTERN(OTG_HS_EP1_IN_IRQHandler)
 OS_ISR_EXTERN(OTG_HS_WKUP_IRQHandler)
 OS_ISR_EXTERN(OTG_HS_IRQHandler)
 OS_ISR_EXTERN(DCMI_IRQHandler)
 OS_ISR_EXTERN(CRYP_IRQHandler)
 OS_ISR_EXTERN(HASH_RNG_IRQHandler)
 OS_ISR_EXTERN(FPU_IRQHandler)

void
OS_ISR_Enter(void);

void
OS_ISR_Exit(void);

bool
OS_ISR_IsNesting(void);

#ifdef __cplusplus
}
#endif

#endif /* OS_ISR_H_ */

/*****************************END OF FILE**************************************/
