/**
  ******************************************************************************
  * @file    AudioCapture.h
  * @author  MCD Application Team
  * @brief   Header for AudioCapture_*.c module
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

#ifndef _AUDIOCAPTURE_CONF_H
#define _AUDIOCAPTURE_CONF_H


#ifdef __cplusplus
extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include "stdint.h"
#include "stm32f7xx_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
#define UTIL_AUDIO_IN_FREQUENCY                   (16000U)
#define AUDIO_CAPTURE_IT_MS                        15U
#define AUDIO_CAPTURE_MEMORY_SECTION_HW_BUFFERS    ".NOCACHE_Section"

#ifdef __cplusplus
}
#endif

#endif // _MICCAPTURE_H


