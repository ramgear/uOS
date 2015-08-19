/**
 ******************************************************************************
 * @file	os_types.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	18-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OS_TYPES_H_
#define OS_TYPES_H_

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include "os_defines.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/

 typedef unsigned char  boolean;
 typedef unsigned char  u8;                    /* Unsigned  8 bit quantity                           */
 typedef signed   char  s8;                    /* Signed    8 bit quantity                           */
 typedef unsigned short u16;                   /* Unsigned 16 bit quantity                           */
 typedef signed   short s16;                   /* Signed   16 bit quantity                           */
 typedef unsigned int   u32;                   /* Unsigned 32 bit quantity                           */
 typedef signed   int   s32;                   /* Signed   32 bit quantity                           */
 typedef float          f32;                   /* Single precision floating point                    */
 typedef double         f64;                   /* Double precision floating point                    */

#if !defined(NULL)
#define NULL	0
#endif

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/



#ifdef __cplusplus
}
#endif

#endif /* OS_TYPES_H_ */

/*****************************END OF FILE**************************************/
