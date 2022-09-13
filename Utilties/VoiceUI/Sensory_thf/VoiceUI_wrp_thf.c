/**
  ******************************************************************************
  * @file    VoiceUI_wrp_thf.c
  * @author  MCD Application Team
  * @brief   Wrapper for THF library
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "VoiceUI_wrp_thf.h"


/* Global variables ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
#define WAKEWORDS_DELAY        0U // override trigger grammar delay value to find end of trigger with more accuracy
#define COMMAND_DELAY          0U // command delay: use grammar value
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void    s_initAudioBuffer(VoiceUI_wrp_thf_t         *const pHdle);
static int32_t s_allocate(VoiceUI_wrp_thf_t                *const pHdle);
static int32_t s_initTrg(VoiceUI_wrp_thf_t                 *const pHdle);
static int32_t s_initCmd(VoiceUI_wrp_thf_t                 *const pHdle);
static int32_t s_processFrameForTrigger(VoiceUI_wrp_thf_t  *const pHdle, int16_t *const pData, VoiceUI_wrp_thfResult_t *const pRes);
static int32_t s_processFrameForCommands(VoiceUI_wrp_thf_t *const pHdle, int16_t *const pData, VoiceUI_wrp_thfResult_t *const pRes);
static int32_t s_processTrg2Commands(VoiceUI_wrp_thf_t     *const pHdle, int16_t *const pData, VoiceUI_wrp_thfResult_t *const pRes);
static void    s_resetRes(VoiceUI_wrp_thfResult_t          *const pRes);
static int32_t s_monitorMemory(t2siStruct         *const pT2si);
static int32_t s_getAudioBufferSize(VoiceUI_wrp_thf_t      *const pHdle);



/* Functions Definition ------------------------------------------------------*/

/**
* @brief  Routine to initialize the recognition
* @param  pHdle = THF Instance
* @retval error
*/
int32_t VoiceUI_wrp_thf_Initialize(VoiceUI_wrp_thf_t *const pHdle)
{
  int32_t error = ERR_OK;

  pHdle->status = THF_STATE_DISABLED;
  error         = s_allocate(pHdle);

  if (error == ERR_OK)
  {
    s_initAudioBuffer(pHdle);
    if ((pHdle->conf.mode == THF_MODE_TRG) || (pHdle->conf.mode == THF_MODE_TRG2CMDS))
    {
      /*call THF init*/
      error = s_initTrg(pHdle);
      pHdle->status = (error == ERR_OK) ? THF_STATE_WAKEWORDS : THF_STATE_DISABLED;
    }
    else //THF_MODE_CMDS
    {
      /*call THF init*/
      error = s_initCmd(pHdle);
      pHdle->status = (error == ERR_OK) ? THF_STATE_COMMAND : THF_STATE_DISABLED;
    }
  }
  else
  {
    pHdle->status = THF_STATE_DISABLED;
  }

  return error;
}


// process a pData of audio samples
// While listening it returns ERR_NOT_FINISHED until a WW is detected then
// it returns ERR_OK
// return value error codes is from SensoryProcessInit or SensoryProcessData.
//
/**
* @brief  process a pData of audio samples. While listening it returns ERR_NOT_FINISHED until a WW is detected then
* @param  pHdle = THF Instance
* @param  pData   pointer on 15ms mono 16-bit PCM audio buffer
* @param  pRes    log results of recognition if any
* @retval value error codes is from SensoryProcessInit or SensoryProcessData.
*/
int32_t VoiceUI_wrp_thf_ProcessFrame(VoiceUI_wrp_thf_t *const pHdle, int16_t *const pData, VoiceUI_wrp_thfResult_t *const pRes)
{
  int32_t error = ERR_OK;

  if (pHdle->status == THF_STATE_DISABLED)
  {
    error = ERR_NOT_FINISHED;
  }

  if (error == ERR_OK)
  {
    error = s_processTrg2Commands(pHdle, pData, pRes);
  }

  return error;
}


/**
* @brief  Routine to get output of the recognition engine status
* @param  pHdle = THF Instance
* @retval boolean
*/
uint8_t VoiceUI_wrp_thf_IsRecoComplete(VoiceUI_wrp_thf_t *const pHdle)
{
  appStruct_T *const pAppStruct = (appStruct_T *)pHdle->pApp;
  t2siStruct  *const pT2si      = &pAppStruct->_t;
  uint8_t            ret        = 0U;

  if ((pT2si->recogPending == 0U) && (pT2si->lpsdHoldoff == 0U))
  {
    ret = 1U;
  }

  return ret;
}


/**
* @brief  Routine to terminate the recognition
* @param  pHdle = THF Instance
* @retval error
*/
int32_t VoiceUI_wrp_thf_Terminate(VoiceUI_wrp_thf_t *const pHdle)
{
  appStruct_T *const pAppStruct = pHdle->pApp;
  t2siStruct  *const pT2si      = &pAppStruct->_t;

  pHdle->status = THF_STATE_DISABLED;

  if (pHdle->pAudioBuffer != NULL)
  {
    AudioFree(pHdle->pAudioBuffer, 0);
  }

  if (pT2si->spp != NULL)
  {
    AudioFree(pT2si->spp, 0);
  }

  if (pHdle->pApp != NULL)
  {
    AudioFree(pHdle->pApp, 0);
  }

  return ERR_OK;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////// static routines ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
* @brief  reset input structure
* @param  results pointer
* @retval None
*/
static void s_resetRes(VoiceUI_wrp_thfResult_t *const pRes)
{
  memset(pRes, 0, sizeof(VoiceUI_wrp_thfResult_t));
}


/**
* @brief  Init THF internal audio buffer
* @param  pHdle = thf instance
* @retval None
*/
static void s_initAudioBuffer(VoiceUI_wrp_thf_t *const pHdle)
{
  appStruct_T *const pAppStruct = (appStruct_T *)pHdle->pApp;

  // initialize audio buffer items. Do this before calling SensoryLPSDInit.
  pAppStruct->audioBufferLen       = s_getAudioBufferSize(pHdle);
  pAppStruct->audioBufferStart     = pHdle->pAudioBuffer;
  pAppStruct->lpsdGetIndex         = 0;
  pAppStruct->audioGetIndex        = 0;
  pAppStruct->audioPutIndex        = 0;
  pAppStruct->audioGetFrameCounter = 0UL;
  pAppStruct->audioFilledCount     = 0;
}


/**
* @brief  Init THF for wakeword/trigger
* @param  pHdle = thf instance
* @retval error
*/
static int32_t s_initTrg(VoiceUI_wrp_thf_t *const pHdle)
{
  appStruct_T *const pAppStruct = (appStruct_T *)pHdle->pApp;
  t2siStruct  *const pT2si      = (t2siStruct *)&pAppStruct->_t;
  unsigned int       size       = 0U;

  /*call LPSD init*/
  SensoryLPSDInit(pAppStruct);

  pT2si->net          = pHdle->conf.trg.net;
  pT2si->gram         = pHdle->conf.trg.gram;
  pT2si->delay        = WAKEWORDS_DELAY;
  pT2si->timeout      = 0U;
  pT2si->initFromLast = 0U;
  pT2si->sdet_type    = pHdle->conf.sdet_type;

  if (pHdle->status != THF_STATE_DISABLED)
  {
    /* Note: need to call SensoryAlloc() to set one library internal variable
    *  with calculated size whenever different net and gram are used
    *  However, can't be called after the first SensoryAlloc used for allocation!!*/
    SensoryAlloc(pAppStruct, &size);
  }
  else
  {
    /*Disable State machine in case init will fail */
    pHdle->status = THF_STATE_DISABLED;
  }
  /*call THF init*/
//  printf("Calling SensoryProcessInit\n");
  return (int32_t)SensoryProcessInit(pAppStruct);
}


/**
* @brief  Init THF for commands
* @param  pHdle = thf instance
* @retval error
*/
static int32_t s_initCmd(VoiceUI_wrp_thf_t *const pHdle)
{
  appStruct_T *const pAppStruct = (appStruct_T *)pHdle->pApp;
  t2siStruct  *const pT2si      = (t2siStruct *)&pAppStruct->_t;
  unsigned int       size       = 0U;

  pHdle->status       = THF_STATE_DISABLED;

  pT2si->net          = pHdle->conf.cmd.net;
  pT2si->gram         = pHdle->conf.cmd.gram;
  pT2si->delay        = COMMAND_DELAY;
  pT2si->timeout      = pHdle->conf.timeout;
  pT2si->sdet_type    = pHdle->conf.sdet_type;
  if (pHdle->conf.mode == THF_MODE_CMDS)
  {
    pT2si->initFromLast = 0U;         // must not be set unless transitting from wake word
  }
  else
  {
    pT2si->initFromLast = 1U;         // helps if no silence between trigger and command
  }
  SensoryAlloc(pAppStruct, &size);  // Note: need to call SensoryAlloc() to set one library internal variable with calculated size whenever different net and gram are used

  return (int32_t)SensoryProcessInit(pAppStruct);
}


/**
* @brief  allocate memory for THF
* @param  pHdle = thf instance
* @retval error
*/
static int32_t s_allocate(VoiceUI_wrp_thf_t *const pHdle)
{
  int32_t      error      = ERR_OK;
  appStruct_T *pAppStruct = NULL;
  t2siStruct  *pT2si      = NULL;
  unsigned int sizeAlloc  = 0U;
  unsigned int sizeCmd    = 0U;
  infoStruct_T  isp;

  pHdle->pApp = (void *)AudioMalloc(sizeof(appStruct_T), 0);
  if (pHdle->pApp == NULL)
  {
    error = ERR_HEAP_FULL;
  }

  if (error == ERR_OK)
  {
    pAppStruct = (appStruct_T *)pHdle->pApp;
    pT2si      = (t2siStruct *)&pAppStruct->_t;

    // Here we zero out appStruct including embedded t2siStruct.
    // Warning: if you do this after the persistent structure is malloc'd you will
    // overwrite the pointer without freeing the structure.
    memset(pAppStruct, 0, sizeof(*pAppStruct));

    // determine the size of the spp memory based on the larger of trigger and command grammars.
    pT2si->maxResults    = (u16)MAX_RESULTS;    // required to set this to get the size of spp
    pT2si->maxTokens     = (u16)MAX_TOKENS;     // "
    pT2si->enableLogging = 0U;

    if ((pHdle->conf.mode == THF_MODE_CMDS) || (pHdle->conf.mode == THF_MODE_TRG2CMDS))
    {
      if ((pHdle->conf.cmd.net != 0UL) && (pHdle->conf.cmd.gram != 0UL))
      {
        pT2si->net          = pHdle->conf.cmd.net;
        pT2si->gram         = pHdle->conf.cmd.gram;
        pT2si->delay        = COMMAND_DELAY;
        pT2si->timeout      = pHdle->conf.timeout;
        pT2si->sdet_type    = pHdle->conf.sdet_type;
        pT2si->initFromLast = 0U;   // helps if no silence between trigger and command
        SensoryAlloc(pAppStruct, &sizeCmd);   // get spp size for trigger
        if (sizeCmd == 0U)
        {
          error = ERR_NOT_OK;
        }
      }
    }
  }

  if (error == ERR_OK)
  {
    if ((pHdle->conf.mode == THF_MODE_TRG) || (pHdle->conf.mode == THF_MODE_TRG2CMDS))
    {
      if ((pHdle->conf.trg.net != 0UL) && (pHdle->conf.trg.gram != 0UL))
      {
        pT2si->net          = (uint32_t)pHdle->conf.trg.net;
        pT2si->gram         = (uint32_t)pHdle->conf.trg.gram;
        pT2si->delay        = WAKEWORDS_DELAY;
        pT2si->timeout      = 0U;
        pT2si->initFromLast = 1U;
        pT2si->sdet_type    = pHdle->conf.sdet_type;

        SensoryInfo(&isp);
	//printf("Tslice Version = %ld.%ld.%ld\n", (isp.version>>20)&0x00000fffUL, (isp.version>>12)&0x000000ffUL, isp.version&0x00000fffUL);
        
        SensoryAlloc(pAppStruct, &sizeAlloc);    // get spp size for trigger

        if (sizeAlloc == 0U)
        {
          error = ERR_NOT_OK;
        }
      }
    }
  }

  if (error == ERR_OK)
  {
    if (sizeCmd > sizeAlloc)
    {
      sizeAlloc = sizeCmd;     // pick the larger of the two
    }
    pT2si->spp = (void *)AudioMalloc(sizeAlloc, 0);

    if (pT2si->spp == NULL)
    {
      error = ERR_HEAP_FULL;
    }
  }

  if (error == ERR_OK)
  {
    pHdle->pAudioBuffer = (int16_t *)AudioMalloc((size_t)s_getAudioBufferSize(pHdle) * sizeof(int16_t), 0);
    if (pHdle->pAudioBuffer == NULL)
    {
      error = ERR_HEAP_FULL;
    }
  }

  return error;
}


/**
* @brief  Return THF internal audio buffer size according to configuration
* @param  pHdle = thf instance
* @retval error
*/
static int32_t s_getAudioBufferSize(VoiceUI_wrp_thf_t *const pHdle)
{
  int32_t audioBufferMs = AUDIO_BUFFER_MS;
  if (pHdle->conf.mode == THF_MODE_TRG2CMDS)
  {
    if (pHdle->conf.sdet_type == (u16)SDET_LPSD)
    {
      audioBufferMs = 630;
    }
    else
    {
      audioBufferMs = 360;
    }
  }
  else
  {
    if (pHdle->conf.sdet_type == (u16)SDET_LPSD)
    {
      audioBufferMs = 270;
    }
    else
    {
      audioBufferMs = 30;
    }
  }
  return ((((audioBufferMs + 29) / 30) * 2) * FRAME_LEN); //AUDIO_BUFFER_LEN ;//
}


/**
* @brief  Monitor THF memory usage errors
* @param  pT2si = thf lib strcuture
* @retval error
*/
static int32_t s_monitorMemory(t2siStruct *const pT2si)
{
  int32_t error = ERR_OK;

  if (pT2si->outOfMemory)
  {
    #if defined(TRACE_USE_UART)&& defined(USE_SENSORY_DEBUG_VERBOSE)
    TraceResult("ERROR -- out of memory!\n");
    #endif
    pT2si->outOfMemory = 0U;
    error = ERR_MEMORY_CORRUPT;
  }

  return error;
}


/**
* @brief  process THF for wakeword/trigger
* @param  pHdle = thf instance
* @param  pData   pointer on 15ms mono 16-bit PCM audio buffer
* @param  pRes    log results of recognition if any
* @retval error
*/
static int32_t s_processFrameForTrigger(VoiceUI_wrp_thf_t *const pHdle, int16_t *const pData, VoiceUI_wrp_thfResult_t *const pRes)
{
  int32_t            error       = ERR_OK;
  int32_t            result      = ERR_NOT_FINISHED;
  appStruct_T *const pAppStruct  = (appStruct_T *)pHdle->pApp;
  t2siStruct  *const pT2si       = (t2siStruct *)&pAppStruct->_t;
  AUDIOINDEX         epIndex, tailCount;
  
  result = (int32_t)SensoryProcessData((BRICK_SAMPLE *)pData, pAppStruct);
  if (result == (ERR_DATACOL_TIMEOUT))
  {
    result = (int32_t)SensoryProcessRestart(pAppStruct);
  }
  
  if (result != ERR_NOT_FINISHED)
  {
    if (result == ERR_OK)
    {
      if (pT2si->wordID == 0)
      {
        pHdle->status = THF_STATE_RESTART_WAKEWORDS;
        result = ERR_NOT_FINISHED;
      }
    }
    
    if (result == ERR_OK)
    {
      // check PQ score for trigger (if trigger uses PQ)
      if ((pT2si->nnpqScore > 0) && (!pT2si->nnpqPass))
      {
        pHdle->status = THF_STATE_RESTART_WAKEWORDS;
        result = ERR_NOT_FINISHED;
      }
    }
    
    if (result == ERR_OK)
    {
      SensoryFindEndpoint(pAppStruct, &epIndex, &tailCount);
      
      // backup get index to end point
      pAppStruct->audioGetIndex = epIndex;
      
      pRes->hasTriggered   = 1U;
      pRes->type           = THF_TRG_TYPE_WAKEWORDS;
      pRes->confidence     = pT2si->finalScore;
      pRes->idDetected     = pT2si->wordID;
      pRes->triggerRestart = 0U;
      pRes->commandRestart = 0U;
      
      
      if (pHdle->conf.mode == THF_MODE_TRG)
      {
        pRes->timeout = 0U;
        pHdle->status = THF_STATE_RESTART_WAKEWORDS;
      }
      else
      {
        pRes->timeout = pHdle->conf.timeout;
        pHdle->status = THF_STATE_RESTART_COMMAND;
      }
    }
    
    if (result != ERR_OK)
    {
      // ending here is worth checking THF error code but shouldn't stop the library
      s_resetRes(pRes);
      pHdle->status = THF_STATE_RESTART_WAKEWORDS;
      error = result;
    }
    if (result == ERR_LICENSE)
    {
      /* Sensory Lib license error */
      s_resetRes(pRes);
      pHdle->status = THF_STATE_DISABLED;
      error = result;
    }
  }
  
  return error;
}


/**
* @brief  process THF for commands
* @param  pHdle = thf instance
* @param  pData   pointer on 15ms mono 16-bit PCM audio buffer
* @param  pRes    log results of recognition if any
* @retval error
*/
static int32_t s_processFrameForCommands(VoiceUI_wrp_thf_t *const pHdle, int16_t *const pData, VoiceUI_wrp_thfResult_t *const pRes)
{
  int32_t            result     = ERR_NOT_FINISHED;
  appStruct_T *const pAppStruct = (appStruct_T *)pHdle->pApp;
  t2siStruct  *const pT2si      = (t2siStruct *)&pAppStruct->_t;
  int32_t            error      = ERR_OK;

  result = (int32_t)SensoryProcessData((BRICK_SAMPLE *)pData, pAppStruct);

  error = s_monitorMemory(pT2si);
  if (error == ERR_OK)
  {
    if (result != ERR_NOT_FINISHED)
    {
      if (result == ERR_OK)
      {
        pRes->hasTriggered   = 1U;
        pRes->type           = THF_TRG_TYPE_COMMAND;
        pRes->confidence     = pT2si->finalScore;
        pRes->idDetected     = pT2si->wordID;
        pRes->triggerRestart = 0U;
        pRes->commandRestart = 0U;
        pRes->timeout        = pHdle->conf.timeout;

        pHdle->status        = THF_STATE_RESTART_COMMAND;
      }
      else
      {
        // note: timeout error is ERR_DATACOL_TIMEOUT, or 0x11
        result = (int32_t)SensoryProcessRestart(pAppStruct);
        error  = result;
        if (pHdle->conf.mode == THF_MODE_CMDS)
        {
          pHdle->status = THF_STATE_RESTART_COMMAND;
        }
        else
        {
          pHdle->status = THF_STATE_RESTART_WAKEWORDS;
        }
      }
    }
  }

  return error;
}


/**
* @brief  process THF for wakeword/trigger to commands (state machine implementation)
* @param  pHdle = thf instance
* @param  pData   pointer on 15ms mono 16-bit PCM audio buffer
* @param  pRes    log results of recognition if any
* @retval error
*/
static int32_t s_processTrg2Commands(VoiceUI_wrp_thf_t *const pHdle, int16_t *const pData, VoiceUI_wrp_thfResult_t *const pRes)
{
  int32_t error = ERR_OK;

  switch (pHdle->status)
  {
    case THF_STATE_RESTART_WAKEWORDS:
      /*call THF init*/
      error = s_initTrg(pHdle);
      if (error != ERR_OK)
      {
        pHdle->status = THF_STATE_DISABLED;
      }

      if (error == ERR_OK)
      {
        pRes->hasTriggered   = 0U;
        pRes->type           = THF_TRG_TYPE_WAKEWORDS;
        pRes->confidence     = 0U;
        pRes->idDetected     = 0U;
        pRes->triggerRestart = 1U;
        pRes->commandRestart = 0U;
        pRes->timeout        = 0U;

        pHdle->status        = THF_STATE_WAKEWORDS;
      }
      if (error == ERR_OK)
      {
        error = s_processFrameForTrigger(pHdle, pData, pRes);
      }
      break;

    case THF_STATE_WAKEWORDS:
      error = s_processFrameForTrigger(pHdle, pData, pRes);
      break;

    case THF_STATE_RESTART_COMMAND:
      error = s_initCmd(pHdle);

      if (error == ERR_OK)
      {
        pRes->hasTriggered   = 0U;
        pRes->type           = THF_TRG_TYPE_COMMAND;
        pRes->confidence     = 0U;
        pRes->idDetected     = 0U;
        pRes->triggerRestart = 0U;
        pRes->commandRestart = 1U;

        pHdle->status        = THF_STATE_COMMAND;
      }
      else
      {
        pHdle->status        = THF_STATE_DISABLED;
      }
      if (error == ERR_OK)
      {
        error = s_processFrameForCommands(pHdle, pData, pRes);
      }
      break;

    case THF_STATE_COMMAND:
      error = s_processFrameForCommands(pHdle, pData, pRes);
      break;

    default:
      error = ERR_NOT_OK;
      break;
  } // switch (pHdle->status)

  return error;
}
