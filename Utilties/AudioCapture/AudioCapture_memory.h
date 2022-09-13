/**
  ******************************************************************************
  * @file    AudioCapture_memory.h
  * @author  MCD Application Team
  * @brief   Header for AudioCapture_memory.c module
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021(-2021) STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AUDIOCAPTURE_MEMORY_H
#define __AUDIOCAPTURE_MEMORY_H


#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <string.h>
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/


#define AUDIO_MEM_HEAP_FAST     (int32_t)1U
#define AUDIO_MEM_HEAP_SLOW     (int32_t)2U
#define AUDIO_MEM_HEAP_FASTB    (int32_t)3U
#define AUDIO_MEM_NOCACHED      (int32_t)4U


#if  defined ( __GNUC__ )
#ifndef __weak
#define __weak   __attribute__((weak))
#endif /* __weak */
#ifndef __packed
#define __packed __attribute__((__packed__))
#endif /* __packed */
#endif /* __GNUC__ */

/* In HS mode and when the DMA is used, all variables and data structures dealing
   with the DMA during the transaction process should be 4-bytes aligned */

#if defined   (__GNUC__)        /* GNU Compiler */
#define __ALIGN_END    __attribute__ ((aligned (4)))
#define __ALIGN_BEGIN
#else
#define __ALIGN_END
#if defined   (__CC_ARM)      /* ARM Compiler */
#define __ALIGN_BEGIN    __align(4)
#elif defined (__ICCARM__)    /* IAR Compiler */
#define __ALIGN_BEGIN
#elif defined  (__TASKING__)  /* TASKING Compiler */
#define __ALIGN_BEGIN    __align(4)
#endif /* __CC_ARM */
#endif /* __GNUC__ */

/* Exported functions ------------------------------------------------------- */
void *AudioMalloc(size_t const size, int32_t const type);
void   AudioFree(void *const pMemToFree, int32_t const type);

#ifdef __cplusplus
}
#endif

#endif /* __AUDIOCAPTURE_MEMORY_H */

