/**
  ******************************************************************************
  * @file    VoiceUI_wrp_thf.h
  * @author  MCD Application Team
  * @brief   Header for VoiceUI_wrp_thf.c module
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
#ifndef _VOICEUI_THFWRP_H
#define _VOICEUI_THFWRP_H

/* Includes ------------------------------------------------------------------*/

#include "AudioCapture_memory.h"
#include "SensoryLib.h"
#include "SensoryTypes.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  THF_MODE_TRG,
  THF_MODE_TRG2CMDS,
  THF_MODE_CMDS,
} VoiceUI_wrp_thf_mode_t;

typedef enum
{
  THF_STATE_DISABLED,
  THF_STATE_RESTART_WAKEWORDS,
  THF_STATE_WAKEWORDS,
  THF_STATE_RESTART_COMMAND,
  THF_STATE_COMMAND
} VoiceUI_wrp_thf_state_t;

typedef enum
{
  THF_TRG_TYPE_WAKEWORDS = 0,
  THF_TRG_TYPE_COMMAND = 1
} VoiceUI_wrp_thf_trg_type_t;

typedef struct
{
  uint32_t net;   // (I) address of the net
  uint32_t gram;  // (I) address of the grammar
} thfVocab_t;


typedef struct
{
  thfVocab_t     trg;       // (I) trigger vocab
  thfVocab_t     cmd;       // (I) commands set
  uint16_t       sdet_type; // (I) type of speech detector: see enum above
  uint16_t       timeout;   // (I) time in seconds to listen for speech to start
  VoiceUI_wrp_thf_mode_t  mode;      // (I) trigger listening or trigger to commands
} thfConf_t;


typedef struct
{
  uint8_t           hasTriggered;
  VoiceUI_wrp_thf_trg_type_t type;
  uint8_t           triggerRestart;
  uint8_t           commandRestart;
  uint16_t          confidence;
  uint16_t          idDetected;
  uint16_t          timeout;   // (O) time in seconds to listen for commands
} VoiceUI_wrp_thfResult_t;


typedef struct
{
  thfConf_t         conf;
  void             *pApp;
  VoiceUI_wrp_thf_state_t    status;
  int16_t          *pAudioBuffer;
} VoiceUI_wrp_thf_t;

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

int32_t VoiceUI_wrp_thf_Initialize(VoiceUI_wrp_thf_t *const pHdle);
int32_t VoiceUI_wrp_thf_ProcessFrame(VoiceUI_wrp_thf_t *const pHdle, int16_t *const pData, VoiceUI_wrp_thfResult_t *const pRes);
int32_t VoiceUI_wrp_thf_Terminate(VoiceUI_wrp_thf_t *const pHdle);
uint8_t VoiceUI_wrp_thf_IsRecoComplete(VoiceUI_wrp_thf_t *const pHdle);

#endif /*_VOICEUI_THFWRP_H */


