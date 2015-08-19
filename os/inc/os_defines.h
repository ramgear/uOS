/**
 ******************************************************************************
 * @file	os_defines.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	18-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OS_DEFINES_H_
#define OS_DEFINES_H_

/* Includes ------------------------------------------------------------------*/

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
#define	OS_DISABLE		0
#define	OS_ENABLE		1

#define	OS_FALSE		0
#define	OS_TRUE			1

/* Exported macro ------------------------------------------------------------*/
#define	OS_SETBIT(val,bit)	(val |= (1 << (bit)))
#define	OS_CLRBIT(val,bit)	(val &= ~(1 << (bit)))

#ifdef __cplusplus
#define	OS_EXTERN_C	extern "C"
#else
#define	OS_EXTERN_C
#endif

/* Exported functions --------------------------------------------------------*/



#ifdef __cplusplus
}
#endif

#endif /* OS_DEFINES_H_ */

/*****************************END OF FILE**************************************/
