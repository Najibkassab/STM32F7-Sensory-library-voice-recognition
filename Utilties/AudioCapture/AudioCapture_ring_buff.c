/**
  ******************************************************************************
  * @file    AudioCapture_rin_buff.c
  * @author  MCD Application Team
  * @brief   handles ping pong buffer of large size fed by smaller ones
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

/* Includes ------------------------------------------------------------------*/
#include "AudioCapture_ring_buff.h"
#include "AudioCapture.h"
#include "AudioCapture_memory.h"
#include "stdio.h"

/* Global variables ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Functions Definition ------------------------------------------------------*/

//#define RING_BUFFER_INSTRUMENTATION
#ifdef RING_BUFFER_INSTRUMENTATION
static uint32_t consumeCount = 0;
static uint32_t feedCount = 0;
#endif

/**
  * @brief  reset all field of the handler
  * @param  Handler of the ring buffer
  * @retval None
  */
void AudioCapture_ring_buff_reset(AudioCapture_ring_buff_t *pHdle)
{
  memset(pHdle, 0, sizeof(AudioCapture_ring_buff_t));
  pHdle->pData = NULL;
}

/**
  * @brief  Allocate buffer as function of info inside the handler fields
  * @param  Handler of the ring buffer
  * @retval None
  */
void AudioCapture_ring_buff_alloc(AudioCapture_ring_buff_t *pHdle)
{
  pHdle->pData = AudioMalloc((size_t)pHdle->nbSamples * pHdle->nbBytesPerSample * pHdle->nbFrames, 0);
}

/**
  * @brief  Free buffer
  * @param  Handler of the ring buffer
  * @retval None
  */
void AudioCapture_ring_buff_free(AudioCapture_ring_buff_t *pHdle)
{
  AudioFree(pHdle->pData, 0);
}

/**
  * @brief  Update read index of data bufer as function of given number of samples and returns new data pointer
  * @param  Handler of the ring buffer
  * @param  number of samples
  * @retval data pointer
  */
uint8_t *AudioCapture_ring_buff_consume(AudioCapture_ring_buff_t *pHdle, uint32_t nbSamples)
{
#ifdef RING_BUFFER_INSTRUMENTATION
  consumeCount++;
#endif
  uint8_t  *pDestData = NULL;
  int16_t s16_nbSamples = (int16_t)nbSamples;
  __disable_irq();
  if (pHdle->availableSamples >= s16_nbSamples)
  {
    pDestData =  pHdle->pData + ((uint32_t)pHdle->nbBytesPerSample * (uint32_t)pHdle->readSampleIndex);
    pHdle->readSampleIndex = (pHdle->readSampleIndex + s16_nbSamples) % ((int16_t)pHdle->nbSamples * (int16_t) pHdle->nbFrames);
    pHdle->availableSamples -= s16_nbSamples;
  }
  __enable_irq();
  return pDestData;
}

/**
* @brief  write new data inside buffer, update write index as function of given number of samples
* @param  Handler of the ring buffer
* @param  pointer on data to be written inside the ring buffer
* @param  number of samples
* @retval None
*/
void AudioCapture_ring_buff_feed(AudioCapture_ring_buff_t *pHdle, uint8_t *pData, int16_t nbSamples)
{
#ifdef RING_BUFFER_INSTRUMENTATION
  feedCount++;
  uint32_t feedCountCheck = feedCount%100;
  if (feedCountCheck==0) {
    printf("Ring buffer: feed=%d, consume=%d avail=%d\n", feedCount, consumeCount, pHdle->availableSamples);
  }
#endif
  if ((pData != NULL) && (pHdle->pData != NULL))
  {
    if ((pHdle->availableSamples + nbSamples) > ((int16_t)pHdle->nbSamples * (int16_t)pHdle->nbFrames))
    {
      printf("Audio capture => Overrun\n");
    }
    else
    {
      uint8_t *pDestData = pHdle->pData + ((uint32_t)pHdle->nbBytesPerSample * (uint32_t) pHdle->writeSampleIndex);
      memcpy(pDestData, pData, ((uint32_t)pHdle->nbBytesPerSample * (uint32_t) nbSamples));
      pHdle->writeSampleIndex = (pHdle->writeSampleIndex + nbSamples) % ((int16_t)pHdle->nbSamples * (int16_t)pHdle->nbFrames);
      pHdle->availableSamples += nbSamples;
    }
  }
  else
  {
    printf("Audio capture => Error, NULL pointer\n");
  }
}
