/**
  ******************************************************************************
  * @file    VoiceUI_usr_thf.h
  * @author  MCD Application Team
  * @brief   Header for VoiceUI_usr_thf.c module
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
#ifndef _VOICEUI_USR_THF_H
#define _VOICEUI_USR_THF_H

/* Includes ------------------------------------------------------------------*/
#include "VoiceUI_wrp_thf.h"


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define VOICEUI_USR_THF_ERROR_NONE 0
#define VOICEUI_USR_THF_ERROR      1


/** THF CONFIGURATION: ***************************************************/

#define VOICEUI_CONF_WAKEWORDS_USED
#define VOICEUI_CONF_COMMANDS_USED


#define VOICEUI_CONF_WAKEWORDS_SDET SDET_NONE


#ifdef VOICEUI_CONF_WAKEWORDS_USED
  #define  VOICEUI_WAKEWORDS_GRAMMAR gs_wakeword_grammarLabel
  #define  VOICEUI_WAKEWORDS_NET     dnn_wakeword_netLabel
#else
  #define  VOICEUI_WAKEWORDS_GRAMMAR 0UL
  #define  VOICEUI_WAKEWORDS_NET     0UL
#endif


#ifdef VOICEUI_CONF_COMMANDS_USED
  #define  VOICEUI_COMMAND_GRAMMAR gs_command_grammarLabel
  #define  VOICEUI_COMMAND_NET     dnn_command_netLabel

#else
  #define  VOICEUI_COMMAND_GRAMMAR 0UL
  #define  VOICEUI_COMMAND_NET     0UL
#endif

#if defined(VOICEUI_CONF_COMMANDS_USED) && defined(VOICEUI_CONF_WAKEWORDS_USED)
  #define  VOICEUI_THF_MODE THF_MODE_TRG2CMDS
#elif defined(VOICEUI_CONF_WAKEWORDS_USED)
  #define  VOICEUI_THF_MODE THF_MODE_TRG
#elif defined(VOICEUI_CONF_COMMANDS_USED)
  #define  VOICEUI_THF_MODE THF_MODE_CMDS
#else
  #error "Error either VOICEUI_CONF_COMMANDS_USED or VOICEUI_CONF_WAKEWORDS_USED needs to be set inside VoiceUI_usr_thf.h"
#endif

/* Exported variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
int32_t VoiceUI_usr_thf_init(void);
int32_t VoiceUI_usr_thf_process(int16_t *const pData);

#endif /*_VOICEUI_USR_THF_H*/


