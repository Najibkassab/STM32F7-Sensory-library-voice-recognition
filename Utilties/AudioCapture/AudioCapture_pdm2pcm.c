/**
  ******************************************************************************
  * @file    AudioCapture_pdm2pcm.c
  * @author  MCD Application Team
  * @brief   Converts audio samples
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
#include "AudioCapture_pdm2pcm.h"

/* Global variables ---------------------------------------------------------*/
PDM_Filter_Handler_t PDM1_filter_handler;
PDM_Filter_Config_t PDM1_filter_config;


/* PDM2PCM init function */
void MX_PDM2PCM_Init(void)
{
  PDM1_filter_handler.bit_order = PDM_FILTER_BIT_ORDER_MSB;
  PDM1_filter_handler.endianness = PDM_FILTER_ENDIANNESS_LE;
  PDM1_filter_handler.high_pass_tap = 2104533974UL;
  PDM1_filter_handler.in_ptr_channels = 1U;
  PDM1_filter_handler.out_ptr_channels = 1U;
  PDM_Filter_Init(&PDM1_filter_handler);

  PDM1_filter_config.decimation_factor = PDM_FILTER_DEC_FACTOR_128;
  PDM1_filter_config.output_samples_number = (uint16_t) AUDIO_CAPTURE_PCM_BUFF_SIZE_SAMPLES;
  PDM1_filter_config.mic_gain = 24;
  PDM_Filter_setConfig(&PDM1_filter_handler, &PDM1_filter_config);
}


/*  process function */
uint8_t MX_PDM2PCM_Process(uint16_t *PDMBuf, uint16_t *PCMBuf)
{
  PDM_Filter((void *)PDMBuf, (void *)PCMBuf, &PDM1_filter_handler);
  return (uint8_t) 0;

}


