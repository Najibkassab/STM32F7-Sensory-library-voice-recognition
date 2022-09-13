/**
******************************************************************************
* @file    cube_hal.h
* @author  STM
* @version V2.3.3
* @date    16-June-2021
* @brief   X-CUBE includes file
******************************************************************************
*
* This software component is licensed by ST under Ultimate Liberty license
* SLA0044, the "License"; You may not use this file except in compliance with
* the License. You may obtain a copy of the License at:
*                             www.st.com/SLA0044
*
******************************************************************************
*/

#ifndef _CUBE_HAL_H_
#define _CUBE_HAL_H_

/* Includes ------------------------------------------------------------------*/
#define APP_REVISION "3.2.0"

#if  defined ( __GNUC__ ) && !defined   (__CC_ARM)
  #ifndef __weak
    #define __weak   __attribute__((weak))
  #endif /* __weak */
  #ifndef __packed
    #define __packed __attribute__((__packed__))
  #endif /* __packed */
#endif /* __GNUC__ */



/* generic macro for memory placement */

#ifdef __ICCARM__
  #define DEFAULT_SECTION ""
#else
  #define DEFAULT_SECTION ".bss"
#endif

#if defined ( __ICCARM__ )
#define VAR_DECLARE_ALIGN4_AT_SECTION(type, var, section)   \
_Pragma("data_alignment=4") type var @ section
#elif defined(__GNUC__)
#define VAR_DECLARE_ALIGN4_AT_SECTION(type, var, section)   \
__attribute__((__section__(section)))                       \
type var __attribute__ ((aligned (4)))
#elif defined(__CC_ARM)
#define VAR_DECLARE_ALIGN4_AT_SECTION(type, var, section)   \
__attribute__((__section__(section)))                       \
__align(4) type var
#else
#error "unsupported compiler"
#endif

#include "stm32f7xx.h"

#if defined(USBD_AUDIO_OUT_USED) || defined(USBD_AUDIO_IN_USED)
  #include "usbd_conf.h"
  #define APP_HID_IN_EP HID_EPIN_ADDR
#else
  #define APP_HID_IN_EP 0
#endif

#if defined(USBD_AUDIO_OUT_USED) || defined(USBD_AUDIO_IN_USED)
#ifdef USE_USB_FS
  #define USB_IRQHandler OTG_FS_IRQHandler
  #define USB_IRQn       OTG_FS_IRQn
#else
  #define USB_IRQHandler OTG_HS_IRQHandler
  #define USB_IRQn       OTG_HS_IRQn
#endif
#endif

#define __QSPI_DATA __attribute__((section(".qspi_data"),aligned(4)))
//#define __QSPI_DATA  /*If empty, logos are in internal flash */

#endif //_CUBE_HAL_H_
