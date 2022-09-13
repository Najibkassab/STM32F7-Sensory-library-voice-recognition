/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "AudioCapture_pdm2pcm.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
CRC_HandleTypeDef hcrc;

SAI_HandleTypeDef hsai_BlockA1;
DMA_HandleTypeDef hdma_sai1_a;

UART_HandleTypeDef huart3;

static void *pHdleAudioIp;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_SAI1_Init(void);
static void MX_CRC_Init(void);
static void set_audio_ip_hdle(void);
static void s_initUSB(void);
/* Private user code ---------------------------------------------------------*/

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MPU Configuration--------------------------------------------------------*/
	MPU_Config();

	/* Enable I-Cache---------------------------------------------------------*/
	SCB_EnableICache();

	/* Enable D-Cache---------------------------------------------------------*/
	SCB_EnableDCache();

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	/* Configure the peripherals common clocks */
	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_USART3_UART_Init();
	MX_SAI1_Init();
	MX_CRC_Init();
	MX_PDM2PCM_Init();
//	s_initUSB();

	set_audio_ip_hdle();
	VoiceUI_usr_thf_init();
	AudioCapture_start(pHdleAudioIp);
	//AudioCapture_SetRingBuffer(pHdleAudioIp);

	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 5;
	RCC_OscInitStruct.PLL.PLLN = 90;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 3;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
//	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART3
//			| RCC_PERIPHCLK_SAI1;
//	PeriphClkInitStruct.PLLSAI.PLLSAIN = 128;
//	PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
//	PeriphClkInitStruct.PLLSAI.PLLSAIQ = 5;
//	PeriphClkInitStruct.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV2;
//	PeriphClkInitStruct.PLLSAIDivQ = 1;
//	PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
//	PeriphClkInitStruct.Sai1ClockSelection = RCC_SAI1CLKSOURCE_PLLSAI;
//	PeriphClkInitStruct.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
////	PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
//	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
//		Error_Handler();
//	}


	  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SAI1 |RCC_PERIPHCLK_USART3;
	  PeriphClkInitStruct.PLLSAI.PLLSAIN = 128;
	  PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
	  PeriphClkInitStruct.PLLSAI.PLLSAIQ = 5;
	  PeriphClkInitStruct.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV2;
	  PeriphClkInitStruct.PLLSAIDivQ = 25;
	  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
	  PeriphClkInitStruct.Sai1ClockSelection = RCC_SAI1CLKSOURCE_PLLSAI;
	  PeriphClkInitStruct.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
	  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
	  {
	    Error_Handler();
	  }
}

/**
 * @brief CRC Initialization Function
 * @param None
 * @retval None
 */
static void MX_CRC_Init(void) {

	/* USER CODE BEGIN CRC_Init 0 */

	/* USER CODE END CRC_Init 0 */

	/* USER CODE BEGIN CRC_Init 1 */

	/* USER CODE END CRC_Init 1 */
	hcrc.Instance = CRC;
	hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
	hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
	hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
	hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
	hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
	if (HAL_CRC_Init(&hcrc) != HAL_OK) {
		Error_Handler();
	}
	__HAL_CRC_DR_RESET(&hcrc);
	/* USER CODE BEGIN CRC_Init 2 */
	/* Enable CRC peripheral to unlock the PDM library */
	__HAL_RCC_CRC_CLK_ENABLE();
	/* USER CODE END CRC_Init 2 */

}

void MX_SAI1_Init(void) {

	/* USER CODE BEGIN SAI1_Init 0 */

	  /* USER CODE END SAI1_Init 0 */

	  /* USER CODE BEGIN SAI1_Init 1 */

	  /* USER CODE END SAI1_Init 1 */
	  hsai_BlockA1.Instance = SAI1_Block_A;
	  hsai_BlockA1.Init.Protocol = SAI_FREE_PROTOCOL;
	  hsai_BlockA1.Init.AudioMode = SAI_MODEMASTER_RX;
	  hsai_BlockA1.Init.DataSize = SAI_DATASIZE_16;
	  hsai_BlockA1.Init.FirstBit = SAI_FIRSTBIT_LSB;
	  hsai_BlockA1.Init.ClockStrobing = SAI_CLOCKSTROBING_FALLINGEDGE;
	  hsai_BlockA1.Init.Synchro = SAI_ASYNCHRONOUS;
	  hsai_BlockA1.Init.OutputDrive = SAI_OUTPUTDRIVE_DISABLE;
	  hsai_BlockA1.Init.NoDivider = SAI_MASTERDIVIDER_DISABLE;
	  hsai_BlockA1.Init.FIFOThreshold = SAI_FIFOTHRESHOLD_EMPTY;
	  hsai_BlockA1.Init.SynchroExt = SAI_SYNCEXT_DISABLE;
	  hsai_BlockA1.Init.MonoStereoMode = SAI_STEREOMODE;
	  hsai_BlockA1.Init.CompandingMode = SAI_NOCOMPANDING;
	  hsai_BlockA1.FrameInit.FrameLength = 16;
	  hsai_BlockA1.FrameInit.ActiveFrameLength = 1;
	  hsai_BlockA1.FrameInit.FSDefinition = SAI_FS_STARTFRAME;
	  hsai_BlockA1.FrameInit.FSPolarity = SAI_FS_ACTIVE_HIGH;
	  hsai_BlockA1.FrameInit.FSOffset = SAI_FS_FIRSTBIT;
	  hsai_BlockA1.SlotInit.FirstBitOffset = 0;
	  hsai_BlockA1.SlotInit.SlotSize = SAI_SLOTSIZE_DATASIZE;
	  hsai_BlockA1.SlotInit.SlotNumber = 1;
	  hsai_BlockA1.SlotInit.SlotActive = 0x0000FFFF;
	  if (HAL_SAI_Init(&hsai_BlockA1) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  /* USER CODE BEGIN SAI1_Init 2 */

}
/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
void MX_USART3_UART_Init(void) {

	/* USER CODE BEGIN USART3_Init 0 */

	/* USER CODE END USART3_Init 0 */

	/* USER CODE BEGIN USART3_Init 1 */

	/* USER CODE END USART3_Init 1 */
	huart3.Instance = USART3;
	huart3.Init.BaudRate = 115200;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart3) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART3_Init 2 */

	/* USER CODE END USART3_Init 2 */

}

/**
 * Enable DMA controller clock
 */
static void MX_DMA_Init(void) {

	/* DMA controller clock enable */
//	__HAL_RCC_DMA1_CLK_ENABLE();
	__HAL_RCC_DMA2_CLK_ENABLE();
	/* DMA interrupt init */

	/*	 DMA1_Stream0_IRQn interrupt configuration
	 HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 7, 0);
	 HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);*/

	/* DMA2_Stream1_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 7, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();

}

static void s_initUSB(void) {
#if defined(USBD_AUDIO_OUT_USED) || defined(USBD_AUDIO_IN_USED)
	/* Init Device Library */
	USBD_AUDIO_Init_Microphone_Descriptor(&hUSBDDevice, 16000, 1);

	USBD_Init(&hUSBDDevice, &AUDIO_Desc, 0);
	/* Add Supported Class */
	USBD_RegisterClass(&hUSBDDevice, &USBD_AUDIO);
	/* Add Interface callbacks for AUDIO Class */
	USBD_AUDIO_RegisterInterface(&hUSBDDevice, &USBD_AUDIO_fops);
	/* Start Device Process */
	USBD_Start(&hUSBDDevice);
#endif
}

/* USER CODE BEGIN 4 */

static void set_audio_ip_hdle(void) {
	pHdleAudioIp = (void*) &hsai_BlockA1;
}

/* USER CODE END 4 */

/* MPU Configuration */

void MPU_Config(void)
{
	  MPU_Region_InitTypeDef MPU_InitStruct = {0};

	  /* Disables the MPU */
	  HAL_MPU_Disable();
	  /** Initializes and configures the Region and the memory to be protected
	  */
	  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
	  MPU_InitStruct.BaseAddress = 0x20048000;
	  MPU_InitStruct.Size = MPU_REGION_SIZE_8KB;
	  MPU_InitStruct.SubRegionDisable = 0x0;
	  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
	  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
	  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
	  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

	  HAL_MPU_ConfigRegion(&MPU_InitStruct);
	  /* Enables the MPU */
	  HAL_MPU_Enable(MPU_HFNMI_PRIVDEF);

}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

#if defined(__GNUC__)
/* With GCC, small printf (option LD Linker->Libraries->Small printf
 set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)

#elif defined ( __ICCARM__ ) /*!< IAR Compiler  */

#if __VER__ >= 9020001 /* IAR >= v9.20.001*/
#define PUTCHAR_PROTOTYPE int putchar(int ch)
#else  /* IAR < v9.20.001*/
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

#else
#error "Unsuported Compile version"

#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE {
	/* Place your implementation of fputc here */
	HAL_UART_Transmit(&huart3, (uint8_t*) &ch, 1U, 0xFFFFUL);

	return ch;
}

/**
 * @brief  Re targets the C library printf function to the USART.
 * @param  None
 * @retval None
 */
#ifdef __GNUC__
int _write(int file, char *ptr, int len) {
	UNUSED(file);
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++) {
		__io_putchar(*ptr++);
	}
	return len;
}
#endif
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
