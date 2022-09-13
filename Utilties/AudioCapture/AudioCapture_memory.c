/**
  ******************************************************************************
  * @file    AudioCapture_memory.c
  * @author  MCD Application Team
  * @brief   encapsulation of malloc for audio purposes
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
#include "AudioCapture_memory.h"
#include <stdlib.h>     /* malloc, free, rand */
#include <assert.h>



/* Global variables ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/

#if defined(AUDIOCAPTURE_CONF_TRACK_MALLOC)
#define AUDIO_MAX_MEMBLOCKS_NB 3000

typedef struct
{
  int32_t size;
  void    *ptr;
} AudioMemBlock_t;

typedef struct
{
  int32_t         totalSize;
  AudioMemBlock_t memBlocks[AUDIO_MAX_MEMBLOCKS_NB];
} AudioMemoryCurrent_t;

int32_t              AFE_currentBlock = 0;
AudioMemoryCurrent_t AudioMem;
#endif

/* Private defines -----------------------------------------------------------*/
#define AUDIO_MEM_UNUSED_VAR(x) ((void)(x))

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Functions Definition ------------------------------------------------------*/


/**
  * @brief  Malloc encapsulation for audio purposes
  * @param  size  malloc size
  * @param  type  malloc type/memory pool
  * @retval ptr   pointer
  */
__weak void *AudioMalloc(size_t const size, int32_t const type)
{
  UNUSED(type);
  void *ptr = malloc(size);

  #if defined(AUDIOCAPTURE_CONF_TRACK_MALLOC)
  if (AFE_currentBlock < AUDIO_MAX_MEMBLOCKS_NB)
  {
    if (ptr != NULL)
    {
      AudioMem.totalSize                       += size;
      AudioMem.memBlocks[AFE_currentBlock].size = size;
      AudioMem.memBlocks[AFE_currentBlock].ptr  = ptr;
    }
  }
  else
  {
    /* more memory blocks than estimated are needed */
    ptr = NULL;
  }
  #endif

  return ptr;
}

/**
  * @brief  Free encapsulation for audio purposes
  * @param  pMemToFree  pointer to be freed size
  * @param  type  malloc type/memory pool
  * @retval None
  */
__weak void AudioFree(void *const pMemToFree, int32_t const type)
{
  UNUSED(type);
  if (pMemToFree != NULL)
  {
    #if defined(AUDIOCAPTURE_CONF_TRACK_MALLOC)
    uint8_t ok = 0U;

    for (int32_t i = 0; i < AFE_currentBlock; i++)
    {
      if (AudioMem.memBlocks[i].ptr == pMemToFree)
      {
        AudioMem.totalSize -= AudioMem.memBlocks[i].size;
        AFE_currentBlock--;
        ok = 1U;
        break;
      }
    }
    assert(ok);   /* if false: This block hasn't been allocated through AFE_malloc() */
    #endif
    free(pMemToFree);
  }
}
