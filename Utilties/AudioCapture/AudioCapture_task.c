/**
  ******************************************************************************
  * @file    AudioCapture_task.c
  * @author  MCD Application Team
  * @brief   Creates SW tasks to manage audio capture
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
#include "AudioCapture.h"
#include "AudioCapture_task.h"



/* Global variables ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
#define AudioCapture_processWrite_IRQHandler EXTI1_IRQHandler
#define AudioCapture_processWrite_IRQ        EXTI1_IRQn
/* Private macros ------------------------------------------------------------*/
/* The AUDIO_CAPTURE_PRIO is the priority of the task that triggers audio
processing , default is 8U because most of our examples have capture DMA IT = 7U*/
#ifndef AUDIO_CAPTURE_PRIO
  #define AUDIO_CAPTURE_PRIO             (8UL)
#endif

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Functions Definition ------------------------------------------------------*/


#ifdef AUDIO_CAPTURE_NOTASK_USED

/**
* @brief  sends AudioIn Pushed message
* @param  None
* @retval None
*/
void AudioCapture_processTask(void)
{
  AudioCapture_process((int16_t *)PCM_Buffer, AUDIO_CAPTURE_PCM_BUFF_SIZE_SAMPLES);
}


/**
* @brief  creates task for AudioIn capture
* @param  None
* @retval None
*/
void AudioCapture_createTask(void)
{

}

/**
* @brief  terminates task for AudioIn capture
* @param  None
* @retval None
*/
void AudioCapture_terminateTask(void)
{

}

#else /* microphone processing done with low prio task */

void AudioCapture_processWrite_IRQHandler(void);
/**
* @brief  sends AudioIn Pushed message
* @param  None
* @retval None
*/
void AudioCapture_processTask(void)
{
  NVIC_SetPendingIRQ(AudioCapture_processWrite_IRQ);
}

/**
* @brief  AudioIn task
* @param  argument: pointer that is passed to the thread function as start argument.
* @retval None
*/
void AudioCapture_processWrite_IRQHandler(void)
{
  NVIC_ClearPendingIRQ(AudioCapture_processWrite_IRQ);
  AudioCapture_process(PCM_Buffer, (uint16_t)AUDIO_CAPTURE_PCM_BUFF_SIZE_SAMPLES);

}

/**
* @brief  creates task for AudioIn capture
* @param  None
* @retval None
*/
void AudioCapture_createTask(void)
{
  HAL_NVIC_SetPriority(AudioCapture_processWrite_IRQ, AUDIO_CAPTURE_PRIO, 0UL);
  HAL_NVIC_EnableIRQ(AudioCapture_processWrite_IRQ);
}

/**
* @brief  terminates task for AudioIn capture
* @param  None
* @retval None
*/
void AudioCapture_terminateTask(void)
{
  HAL_NVIC_SetPriority(AudioCapture_processWrite_IRQ, 0x0FUL, 0UL);
  HAL_NVIC_DisableIRQ(AudioCapture_processWrite_IRQ);
}
#endif
