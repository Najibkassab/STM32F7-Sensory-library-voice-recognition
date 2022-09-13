/**
  ******************************************************************************
  * @file    VoiceUI_usr_thf.c
  * @author  MCD Application Team
  * @brief   Functions to call THF according to user configuration (buffering,
  *          models, print detected items or potential errors)
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
#include "VoiceUI_usr_thf.h"

/* Sensory Vocabs*/

/* Wake Word*/
//#include   "wakeword-pc60-6.5.0-op05-dev-search.h"
#include   "wakeword-pc60-6.5.0-op10-dev-search.h"
/* Command*/
#include   "command-pc62-6.4.0-op10-dev-search.h"

/* Misra can not parse the Vocabs files*/
#ifndef  MISRA_ANALYSIS 

/* Wake Word*/
//#include   "wakeword-pc60-6.5.0-op05-dev-search.c"
//#include   "wakeword-pc60-6.5.0-op05-dev-net.c"
#include   "wakeword-pc60-6.5.0-op10-dev-search.c"
#include   "wakeword-pc60-6.5.0-op10-dev-net.c"
/* Command*/
#include   "command-pc62-6.4.0-op10-dev-net.c"
#include   "command-pc62-6.4.0-op10-dev-search.c"

#else
const char *command_phrases[16]; 
const unsigned short dnn_command_netLabel[];
const unsigned short gs_command_grammarLabel[];
const char *wakeword_phrases[3]; 
const unsigned short dnn_wakeword_netLabel[];
const unsigned short gs_wakeword_grammarLabel[];
#endif
    

#if defined(VOICEUI_CONF_COMMANDS_USED) || defined(VOICEUI_CONF_WAKEWORDS_USED)

/* Global variables ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
#define THF_CHANNELS_NB     1U
#define THF_FS              16000U
#define THF_DURATION_NS     15000000UL
#define THF_NBFRAMES        2U
#define THF_FORMAT_DOMAIN   ABUFF_FORMAT_TIME
#define THF_FORMAT_TYPE     ABUFF_FORMAT_FIXED16
#define THF_INTERLEAVED     ABUFF_FORMAT_INTERLEAVED
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static VoiceUI_wrp_thf_t       g_thfHdle;
static VoiceUI_wrp_thfResult_t g_thfRes;
/* Private function prototypes -----------------------------------------------*/
static void VoiceUI_usr_thf_help(VoiceUI_wrp_thf_mode_t const mode);
static void VoiceUI_usr_thf_ww_help(void);
static void VoiceUI_usr_thf_cmds_help(void);

/* Functions Definition ------------------------------------------------------*/
/**
  * @brief  Init THF according to user configuration
  * @retval Error
  */
int32_t VoiceUI_usr_thf_init(void)
{
  int32_t error = VOICEUI_USR_THF_ERROR_NONE;

  g_thfHdle.conf.mode      = VOICEUI_THF_MODE;
  g_thfHdle.conf.trg.gram  = (u32)VOICEUI_WAKEWORDS_GRAMMAR;
  g_thfHdle.conf.trg.net   = (u32)VOICEUI_WAKEWORDS_NET;
  g_thfHdle.conf.cmd.gram  = (u32)VOICEUI_COMMAND_GRAMMAR;
  g_thfHdle.conf.cmd.net   = (u32)VOICEUI_COMMAND_NET;
  g_thfHdle.conf.sdet_type = (uint16_t)VOICEUI_CONF_WAKEWORDS_SDET;
  g_thfHdle.conf.timeout   = 3U;
  g_thfHdle.pApp           = NULL;
  g_thfHdle.pAudioBuffer   = NULL;
  g_thfHdle.status         = THF_STATE_DISABLED;

  if (VoiceUI_wrp_thf_Initialize(&g_thfHdle) != VOICEUI_USR_THF_ERROR_NONE)
  {
    error = VOICEUI_USR_THF_ERROR;
  }
  if (error == VOICEUI_USR_THF_ERROR_NONE)
  {
    printf("Sensory is ready, and ");
    VoiceUI_usr_thf_help(g_thfHdle.conf.mode);

    if ((g_thfHdle.conf.mode == THF_MODE_TRG) || (g_thfHdle.conf.mode == THF_MODE_TRG2CMDS))
    {
      printf("Listening to wake word ...\n\r");
    }
    else //THF_MODE_CMDS
    {
      printf(" ------------------------------------ Listening to commands ...\n");
      VoiceUI_usr_thf_cmds_help();
    }
  }
  return error;
}


/**
  * @brief  Processes THF
  * @param  pData     pointer toward 15ms mono channel microphone buffer
  * @retval Error
  */
int cmdCnt = 0;

int32_t VoiceUI_usr_thf_process(int16_t *const pData)
{
  int32_t    error  = ERR_OK;
  static int trgCnt = 0;

  error = VoiceUI_wrp_thf_ProcessFrame(&g_thfHdle, pData, &g_thfRes);
  if (error == ERR_OK)
  {

    if (g_thfRes.hasTriggered)
    {
      if (g_thfRes.type == THF_TRG_TYPE_WAKEWORDS)      /* check if trg found */
      {
        trgCnt++;
        printf("%s\r\n",wakeword_phrases[g_thfRes.idDetected]);
      //  printf("===> %s %d\n", wakeword_phrases[g_thfRes.idDetected], trgCnt);
//        printf("FinalScore =  %d\n", g_thfRes.confidence);

      }
      else if (g_thfRes.type == THF_TRG_TYPE_COMMAND)
      {
        printf("%s\n", command_phrases[g_thfRes.idDetected]);
        cmdCnt++;
      }
      else
      {
        /* Do nothing MISRA */
      }
      g_thfRes.hasTriggered = 0U;
    }
    if (g_thfRes.commandRestart)
    {
      printf(" Say a command ...\r\n");
      g_thfRes.commandRestart = 0U;
    }
    if (g_thfRes.triggerRestart)
    {
      printf("Say a wake-up word ...\r\n");
      g_thfRes.triggerRestart = 0U;
    }
    error = VOICEUI_USR_THF_ERROR_NONE;
  }
  else
  {
    if (error == ERR_MEMORY_CORRUPT)
    {
      printf("THF memory corruption");
    }
    else if (error == ERR_NOT_OK)
    {
      printf("THF generic error");
    }
    else if ((error >= 0x10) && (error < 0x20))
    {
      if (error == (ERR_DATACOL_TIMEOUT))
      {
        printf("THF TIMEOUT reached");
      }
      else
      {
        printf("THF data collection error %d", (int)error);
      }
    }
    else if ((error >= 0x30) && (error < 0x40))
    {
      printf("THF recognition error %d", (int)error);
    }
    else if ((error >= 0x50) && (error < 0x60))
    {
      printf("THF T2SI error %d", (int)error);
    }
    else if ((error >= 0x60) && (error < 0x70))
    {
      printf("THF DNN error %d", (int)error);
    }
    else
    {
      // do nothing (MISRA)
    }
    error = VOICEUI_USR_THF_ERROR;
  }
  return error;
}


/**
  * @brief  print THF wake word used
  * @retval None
  */
static void VoiceUI_usr_thf_ww_help(void)
{
  printf("wake words are:\r\n ");
  
  for(int i=1; i<(WAKEWORD_PHRASE_COUNT-1); i++)
  {
    printf("%s\n\r", wakeword_phrases[i] );
  }
}


/**
  * @brief  print THF commands used
  * @retval None
  */
static void VoiceUI_usr_thf_cmds_help(void)
{
  printf("List of available commands = \n\r");

  for (int i = 1; i < (COMMAND_PHRASE_COUNT-1); i++)
  {
    printf(" - %s\n\r", command_phrases[i]);
  }
}


/**
  * @brief  calls THF help function according to user mode
  * @param  mode     thf mode used , see VoiceUI_wrp_thf_mode_t
  * @retval None
  */
static void VoiceUI_usr_thf_help(VoiceUI_wrp_thf_mode_t const mode)
{
  if (mode == THF_MODE_TRG)
  {
    VoiceUI_usr_thf_ww_help();
  }
  else if (mode == THF_MODE_TRG2CMDS)
  {
    VoiceUI_usr_thf_ww_help();
    VoiceUI_usr_thf_cmds_help();
  }
  else //THF_MODE_CMDS
  {
    VoiceUI_usr_thf_cmds_help();
  }
}


#ifndef VOICEUI_CONF_LIB_FOR_MISRA
/**
  * @brief  __weak redefinition to connect audioCapture to sensory THF
  * @param  pData     pointer toward 15ms mono channel microphone buffer
  * @param  nbSamples must be 240 for THF
  * @retval None
  */
void AudioCapture_process(int16_t *pData, uint16_t nbSamples)
{
  if (nbSamples != 240U)
  {
    printf("ERROR: THF requires to be called with 240 samples frame length\n");
  }
  else
  {
    VoiceUI_usr_thf_process(pData);
  }
}
#endif
#else

int32_t VoiceUI_usr_thf_init(void)
{
  return 0;
}


/**
  * @brief  Processes THF
  * @param  pData     pointer toward 15ms mono channel microphone buffer
  * @retval Error
  */
int32_t VoiceUI_usr_thf_process(int16_t *const pData)
{
  return 0;
}
#endif
