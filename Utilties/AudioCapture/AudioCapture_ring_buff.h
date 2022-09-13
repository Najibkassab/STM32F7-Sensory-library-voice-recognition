/**
  ******************************************************************************
  * @file    AudioCapture_ring_buff.h
  * @author  MCD Application Team
  * @brief   Header for AudioCapture_ring_buff.c module
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

#ifndef _AUDIOCAPTURE_RING_BUFF_H
#define _AUDIOCAPTURE_RING_BUFF_H


#ifdef __cplusplus
extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/

#include "AudioCapture_conf.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint8_t      *pData;             //!< Pointer to start address of circ buffer
  uint8_t       nbBytesPerSample;  //!<  size of samples
  uint8_t       nbFrames;          //!<  number of frame of nbSamples size inside circular buffer
  uint32_t      nbSamples;         //!< Total size of circ buffer / Unit = Number of samples
  int16_t       readSampleIndex;   //!< Index of the sample to read inside circular buffer
  int16_t       writeSampleIndex;  //!< Index of the sample to write inside circular buffer
  int16_t       availableSamples;
} AudioCapture_ring_buff_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */



void     AudioCapture_ring_buff_reset(AudioCapture_ring_buff_t *pHdle);
void     AudioCapture_ring_buff_alloc(AudioCapture_ring_buff_t *pHdle);
void     AudioCapture_ring_buff_free(AudioCapture_ring_buff_t *pHdle);
void     AudioCapture_ring_buff_feed(AudioCapture_ring_buff_t *pHdle, uint8_t *pData, int16_t nbSamples);
uint8_t *AudioCapture_ring_buff_consume(AudioCapture_ring_buff_t *pHdle, uint32_t nbSamples);

#ifdef __cplusplus
}
#endif

#endif // _AUDIOCAPTURE_RING_BUFF_H

