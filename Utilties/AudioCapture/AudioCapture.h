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

#ifndef _AUDIOCAPTURE_H
#define _AUDIOCAPTURE_H


#ifdef __cplusplus
extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include "AudioCapture_ring_buff.h"
#include "AudioCapture_conf.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
#define AUDIO_CAPTURE_PCM_BUFF_SIZE_SAMPLES (AUDIO_CAPTURE_IT_MS * UTIL_AUDIO_IN_FREQUENCY/1000U) /* ms */

#if !defined(UNUSED)
#define UNUSED(x) ((void)(x))
#endif

/* Exported variables --------------------------------------------------------*/
extern int16_t PCM_Buffer[AUDIO_CAPTURE_PCM_BUFF_SIZE_SAMPLES];
extern UART_HandleTypeDef *pHuart;
/* Exported functions ------------------------------------------------------- */
void AudioCapture_SetRingBuffer(AudioCapture_ring_buff_t *pHdle);
int AudioCapture_start(void *pHdleAudioIp);
void AudioCapture_process(int16_t *pData, uint16_t nbSamples);

#ifdef __cplusplus
}
#endif

#endif // _AUDIOCAPTURE_RING_BUFF_H


