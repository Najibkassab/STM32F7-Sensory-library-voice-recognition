/**
 ******************************************************************************
 * @file    AudioCapture_saidPdm.c
 * @author  MCD Application Team
 * @brief   Starts microphone connected to SAIPDM
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
#include "AudioCapture_pdm2pcm.h"
#include "AudioCapture_task.h"
#include "stdio.h"
#include "AudioCapture_ring_buff.h"
#if defined(USBD_AUDIO_IN_USED)
#include "usbd_audio_if.h"
static void s_merge2stereo(int16_t *pIn1Buffer, int16_t *pIn2Buffer, int16_t *pMergeBuffer, uint32_t nbSamples);
//__attribute__((__section__(AUDIO_CAPTURE_MEMORY_SECTION_HW_BUFFERS))) int16_t USB_Buffer[2*AUDIO_CAPTURE_PCM_BUFF_SIZE_SAMPLES];
int16_t USB_Buffer[2*AUDIO_CAPTURE_PCM_BUFF_SIZE_SAMPLES];
#endif

/* Global variables ----------------------------------------------------------*/
int16_t PCM_Buffer[AUDIO_CAPTURE_PCM_BUFF_SIZE_SAMPLES];
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
//#define AUDIO_CAPTURE_PDM_BUFF_SIZE_BYTES (AUDIO_CAPTURE_IT_MS * 2UL * 2048UL / 8UL) /* 256 kHz frequency expected on SAI ; 2x for pingPong */
//#define AUDIO_CAPTURE_PDM_BUFF_SIZE_BYTES (AUDIO_CAPTURE_IT_MS * UTIL_AUDIO_IN_FREQUENCY/1000 )
#define AUDIO_CAPTURE_PDM_BUFF_SIZE_BYTES (AUDIO_CAPTURE_IT_MS * 2048UL / 8UL) /* 256 kHz frequency expected on SAI ; 2x for pingPong */

/* Private macros ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static AudioCapture_ring_buff_t *s_ringBufferHandle = NULL;
#if defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4
  #ifdef AUDIO_CAPTURE_MEMORY_SECTION_HW_BUFFERS
    __ALIGN_BEGIN uint8_t PDM_Buffer[AUDIO_CAPTURE_PDM_BUFF_SIZE_BYTES] __ALIGN_END @ AUDIO_CAPTURE_MEMORY_SECTION_HW_BUFFERS;
  #else
    __ALIGN_BEGIN uint8_t PDM_Buffer[AUDIO_CAPTURE_PDM_BUFF_SIZE_BYTES] __ALIGN_END;
  #endif


//#else /* keil & (__GNUC__)*/
//  __attribute__((__section__(AUDIO_CAPTURE_MEMORY_SECTION_HW_BUFFERS)))
//  __ALIGN_BEGIN uint8_t PDM_Buffer[AUDIO_CAPTURE_PDM_BUFF_SIZE_BYTES] __ALIGN_END;
//#endif
#endif // #if defined(USBD_AUDIO_IN_USED)

//    __attribute__((__section__(".ROarraySection")))
//    __ALIGN_BEGIN uint8_t PDM_Buffer[AUDIO_CAPTURE_PDM_BUFF_SIZE_BYTES] __ALIGN_END;

uint8_t PDM_Buffer[AUDIO_CAPTURE_PDM_BUFF_SIZE_BYTES] __attribute__((section(".ROarraySection")));
//    uint8_t PDM_Buffer[AUDIO_CAPTURE_PDM_BUFF_SIZE_BYTES];
/* Private function prototypes -----------------------------------------------*/
/* Functions Definition ------------------------------------------------------*/

/**
 * @brief  starts microphone capture (DMA)
 * @param  None
 * @retval hal error code for dma start
 */
int AudioCapture_start(void *pHdleAudioIp) {
	AudioCapture_createTask();
	return (int) HAL_SAI_Receive_DMA((SAI_HandleTypeDef*) pHdleAudioIp,
			PDM_Buffer, (uint16_t) AUDIO_CAPTURE_PDM_BUFF_SIZE_BYTES);

}

/**
 * @brief  process microphone data (receive from DMA)
 * @param  data pointer
 * @param  number of samples
 * @retval None
 */
__weak void AudioCapture_process(int16_t *pData, uint16_t nbSamples) {
	UNUSED(pData);
	UNUSED(nbSamples);
	printf("Microphone DMA IT \n");
}

/**
 * @brief  Register the ring buffer handle if needed
 * @param  Callbacks
 * @retval None
 */
void AudioCapture_SetRingBuffer(AudioCapture_ring_buff_t *pHdle) {
	s_ringBufferHandle = pHdle;
}

/**
 * @brief  Overwrite hal dma callback to connect to application
 * @param  sai handler
 * @retval none
 */
void HAL_SAI_RxHalfCpltCallback(SAI_HandleTypeDef *hsai) {
	/* Call the record update function to get the second half */
	/* Invalidate Data Cache to get the updated content of the SRAM*/
	SCB_InvalidateDCache_by_Addr((uint32_t*) &PDM_Buffer,
			(int32_t) (AUDIO_CAPTURE_PDM_BUFF_SIZE_BYTES / 2UL));
	MX_PDM2PCM_Process((uint16_t*) PDM_Buffer, (uint16_t*) PCM_Buffer);
	if (s_ringBufferHandle != NULL) {
		AudioCapture_ring_buff_feed(s_ringBufferHandle, (uint8_t*) PCM_Buffer,
				(int16_t) AUDIO_CAPTURE_PCM_BUFF_SIZE_SAMPLES);
	}
#if defined(USBD_AUDIO_IN_USED)
//  s_merge2stereo(PCM_Buffer, PCM_Buffer, USB_Buffer, AUDIO_CAPTURE_PCM_BUFF_SIZE_SAMPLES);
  Send_Audio_to_USB(PCM_Buffer, AUDIO_CAPTURE_PCM_BUFF_SIZE_SAMPLES);
#endif
	AudioCapture_processTask();
}

/**
 * @brief  Overwrite hal dma callback to connect to application
 * @param  sai handler
 * @retval none
 */
void HAL_SAI_RxCpltCallback(SAI_HandleTypeDef *hsai) {
	/* Call the record update function to get the second half */
	/* Invalidate Data Cache to get the updated content of the SRAM*/
	SCB_InvalidateDCache_by_Addr(
			(uint32_t*) &PDM_Buffer[AUDIO_CAPTURE_PDM_BUFF_SIZE_BYTES / 2UL],
			(int32_t) (AUDIO_CAPTURE_PDM_BUFF_SIZE_BYTES / 2UL));
	MX_PDM2PCM_Process(
			(uint16_t*) (&PDM_Buffer[AUDIO_CAPTURE_PDM_BUFF_SIZE_BYTES / 2UL]),
			(uint16_t*) PCM_Buffer);
	if (s_ringBufferHandle != NULL) {
		AudioCapture_ring_buff_feed(s_ringBufferHandle, (uint8_t*) PCM_Buffer,
				(int16_t) AUDIO_CAPTURE_PCM_BUFF_SIZE_SAMPLES);
	}
#if defined(USBD_AUDIO_IN_USED)
//  s_merge2stereo(PCM_Buffer, PCM_Buffer, USB_Buffer, AUDIO_CAPTURE_PCM_BUFF_SIZE_SAMPLES);
  Send_Audio_to_USB(PCM_Buffer, AUDIO_CAPTURE_PCM_BUFF_SIZE_SAMPLES);
#endif
	AudioCapture_processTask();
}

/**
 * @brief  Overwrite sai error callback to implement infinite loop
 * @param  sai handler
 * @retval none
 */
void HAL_SAI_ErrorCallback(SAI_HandleTypeDef *hsai) {
	/* Prevent unused argument(s) compilation warning */
	printf("SAI error, please check the configuration again, Error code = %d\n",
			(int) hsai->ErrorCode);
}

#if defined(USBD_AUDIO_IN_USED)
static void s_merge2stereo(int16_t *pIn1Buffer, int16_t *pIn2Buffer, int16_t *pMergeBuffer, uint32_t nbSamples)
{

  if ((pIn1Buffer == NULL) || (pIn2Buffer == NULL) || (pMergeBuffer == NULL)) {
    return;
  }

  for (uint16_t i = 0; i <  nbSamples; i++)
  {
    pMergeBuffer[2U*i]    = pIn1Buffer[i];
    pMergeBuffer[(2U*i) +1U] = pIn2Buffer[i];
  }

  return;
}
#endif
