/**
  ******************************************************************************
  * @file    AudioCapture_pdm2pcm.h
  * @author  MCD Application Team
  * @brief   Header for AudioCapture_pdm2pcm.c module
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
#ifndef __AUDIOCAPTURE_PDM2PCM_H
#define __AUDIOCAPTURE_PDM2PCM_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "AudioCapture.h"
#include "pdm2pcm_glo.h"


/* Global variables ---------------------------------------------------------*/
extern PDM_Filter_Handler_t PDM1_filter_handler;
extern PDM_Filter_Config_t PDM1_filter_config;

/* PDM2PCM init function */
void MX_PDM2PCM_Init(void);


/* PDM2PCM process function */
uint8_t MX_PDM2PCM_Process(uint16_t *PDMBuf, uint16_t *PCMBuf);

#ifdef __cplusplus
}
#endif
#endif /*__PDM2PCM_H */




