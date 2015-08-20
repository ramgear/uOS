/**
 ******************************************************************************
 * @file	cpu.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	20-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CPU_H_
#define CPU_H_

#include "cpu_core.h"

#ifdef __cplusplus
 extern "C" {
#endif

 /*
  * ************************************************************************************************
  * CPU Registers
  * ************************************************************************************************
  */

 /**
   * @brief Reset and Clock Control
   */
 typedef struct
 {
	 CPU_REG CR;            /*!< RCC clock control register,                                  Address offset: 0x00 */
	 CPU_REG PLLCFGR;       /*!< RCC PLL configuration register,                              Address offset: 0x04 */
	 CPU_REG CFGR;          /*!< RCC clock configuration register,                            Address offset: 0x08 */
	 CPU_REG CIR;           /*!< RCC clock interrupt register,                                Address offset: 0x0C */
	 CPU_REG AHB1RSTR;      /*!< RCC AHB1 peripheral reset register,                          Address offset: 0x10 */
	 CPU_REG AHB2RSTR;      /*!< RCC AHB2 peripheral reset register,                          Address offset: 0x14 */
	 CPU_REG AHB3RSTR;      /*!< RCC AHB3 peripheral reset register,                          Address offset: 0x18 */
	 CPU_REG RESERVED0;     /*!< Reserved, 0x1C                                                                    */
	 CPU_REG APB1RSTR;      /*!< RCC APB1 peripheral reset register,                          Address offset: 0x20 */
	 CPU_REG APB2RSTR;      /*!< RCC APB2 peripheral reset register,                          Address offset: 0x24 */
	 CPU_REG RESERVED1[2];  /*!< Reserved, 0x28-0x2C                                                               */
	 CPU_REG AHB1ENR;       /*!< RCC AHB1 peripheral clock register,                          Address offset: 0x30 */
	 CPU_REG AHB2ENR;       /*!< RCC AHB2 peripheral clock register,                          Address offset: 0x34 */
	 CPU_REG AHB3ENR;       /*!< RCC AHB3 peripheral clock register,                          Address offset: 0x38 */
	 CPU_REG RESERVED2;     /*!< Reserved, 0x3C                                                                    */
	 CPU_REG APB1ENR;       /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x40 */
	 CPU_REG APB2ENR;       /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x44 */
	 CPU_REG RESERVED3[2];  /*!< Reserved, 0x48-0x4C                                                               */
	 CPU_REG AHB1LPENR;     /*!< RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50 */
	 CPU_REG AHB2LPENR;     /*!< RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54 */
	 CPU_REG AHB3LPENR;     /*!< RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58 */
	 CPU_REG RESERVED4;     /*!< Reserved, 0x5C                                                                    */
	 CPU_REG APB1LPENR;     /*!< RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60 */
	 CPU_REG APB2LPENR;     /*!< RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64 */
	 CPU_REG RESERVED5[2];  /*!< Reserved, 0x68-0x6C                                                               */
	 CPU_REG BDCR;          /*!< RCC Backup domain control register,                          Address offset: 0x70 */
	 CPU_REG CSR;           /*!< RCC clock control & status register,                         Address offset: 0x74 */
	 CPU_REG RESERVED6[2];  /*!< Reserved, 0x78-0x7C                                                               */
	 CPU_REG SSCGR;         /*!< RCC spread spectrum clock generation register,               Address offset: 0x80 */
	 CPU_REG PLLI2SCFGR;    /*!< RCC PLLI2S configuration register,                           Address offset: 0x84 */

 } CPU_REG_RCC_Type;

 /*
  * ************************************************************************************************
  * CPU Memory mapping
  * ************************************************************************************************
  */
 /**
   * @brief Peripheral_memory_map
   */
 #define CPU_FLASH_BASE				((CPU_DATA)0x08000000) /*!< FLASH(up to 1 MB) base address in the alias region                         */
 #define CPU_CCMDATARAM_BASE		((CPU_DATA)0x10000000) /*!< CCM(core coupled memory) data RAM(64 KB) base address in the alias region  */
 #define CPU_SRAM1_BASE				((CPU_DATA)0x20000000) /*!< SRAM1(112 KB) base address in the alias region                             */
 #define CPU_SRAM2_BASE            	((CPU_DATA)0x2001C000) /*!< SRAM2(16 KB) base address in the alias region                              */
 #define CPU_SRAM3_BASE            	((CPU_DATA)0x20020000) /*!< SRAM3(64 KB) base address in the alias region                              */
 #define CPU_PERIPH_BASE           	((CPU_DATA)0x40000000) /*!< Peripheral base address in the alias region                                */
 #define CPU_BKPSRAM_BASE          	((CPU_DATA)0x40024000) /*!< Backup SRAM(4 KB) base address in the alias region                         */
 #define CPU_FSMC_R_BASE           	((CPU_DATA)0xA0000000) /*!< FSMC registers base address                                                */
 #define CPU_CCMDATARAM_BB_BASE    	((CPU_DATA)0x12000000) /*!< CCM(core coupled memory) data RAM(64 KB) base address in the bit-band region  */
 #define CPU_SRAM1_BB_BASE         	((CPU_DATA)0x22000000) /*!< SRAM1(112 KB) base address in the bit-band region                             */
 #define CPU_SRAM2_BB_BASE         	((CPU_DATA)0x2201C000) /*!< SRAM2(16 KB) base address in the bit-band region                              */
 #define CPU_SRAM3_BB_BASE         	((CPU_DATA)0x22020000) /*!< SRAM3(64 KB) base address in the bit-band region                              */
 #define CPU_PERIPH_BB_BASE        	((CPU_DATA)0x42000000) /*!< Peripheral base address in the bit-band region                                */
 #define CPU_BKPSRAM_BB_BASE       	((CPU_DATA)0x42024000) /*!< Backup SRAM(4 KB) base address in the bit-band region                         */
 #define CPU_FLASH_END             	((CPU_DATA)0x080FFFFF) /*!< FLASH end address */
 #define CPU_CCMDATARAM_END        	((CPU_DATA)0x1000FFFF) /*!< CCM data RAM end address */

 /*!< Peripheral memory map */
 #define CPU_APB1PERIPH_BASE       	CPU_PERIPH_BASE
 #define CPU_APB2PERIPH_BASE       	(CPU_PERIPH_BASE + 0x00010000)
 #define CPU_AHB1PERIPH_BASE       	(CPU_PERIPH_BASE + 0x00020000)
 #define CPU_AHB2PERIPH_BASE       	(CPU_PERIPH_BASE + 0x10000000)

 /* Legacy defines */
 #define CPU_SRAM_BASE             	CPU_SRAM1_BASE
 #define CPU_SRAM_BB_BASE          	CPU_SRAM1_BB_BASE

 /*!< AHB1 peripherals */
 #define CPU_RCC_BASE              	(CPU_AHB1PERIPH_BASE + 0x3800)

 #define CPU_REG_RCC               	((CPU_REG_RCC_Type *) CPU_RCC_BASE)

#ifdef __cplusplus
}
#endif

#endif /* CPU_H_ */

/*****************************END OF FILE**************************************/
