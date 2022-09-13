/**
  ******************************************************************************
  * @file    AudioCapture_task.h
  * @author  MCD Application Team
  * @brief   Header for AudioCapture_task.c module
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

#ifndef _MICCAPTURE_TASK_H
#define _MICCAPTURE_TASK_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void     AudioCapture_createTask(void);
void     AudioCapture_processTask(void);
void     AudioCapture_terminateTask(void);
#ifdef __cplusplus
}
#endif

#endif /*_MICCAPTURE_TASK_H*/


