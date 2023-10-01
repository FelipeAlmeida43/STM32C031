/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32c0xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32c0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Variables.h"
#include "button.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
int counterButton = 0;
extern uint32_t adc_buffer[];
uint32_t 	media		= 0,
			timer1Sec	= 0,
			fastTick 	= 0,
			ultraTick 	= 0,
			slowTick 	= 0,
			flashTick   = 0,
			timeoutTick = 0;
//extern float voltage;

float voltage =0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc1;
extern TIM_HandleTypeDef htim1;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32C0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32c0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line 4 to 15 interrupts.
  */
void EXTI4_15_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_15_IRQn 0 */

  /* USER CODE END EXTI4_15_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(LEFT_Pin);
  HAL_GPIO_EXTI_IRQHandler(RIGHT_Pin);
  HAL_GPIO_EXTI_IRQHandler(BTN_BLUE_Pin);
  /* USER CODE BEGIN EXTI4_15_IRQn 1 */

  //counterButton+=1;
  /* USER CODE END EXTI4_15_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel 1 interrupt.
  */
void DMA1_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel1_IRQn 0 */

  /* USER CODE END DMA1_Channel1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc1);
  /* USER CODE BEGIN DMA1_Channel1_IRQn 1 */

  /* USER CODE END DMA1_Channel1_IRQn 1 */
}

/**
  * @brief This function handles TIM1 break, update, trigger and commutation interrupts.
  */
void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_BRK_UP_TRG_COM_IRQn 0 */

  /* USER CODE END TIM1_BRK_UP_TRG_COM_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_BRK_UP_TRG_COM_IRQn 1 */
  timer1Sec++;
  if(timer1Sec>=100){
	  HAL_GPIO_TogglePin(GPIOA, LD4_GREEN_Pin);
	  timer1Sec =0;
  }
  if(Channel_0.debounce > 0)
  {
	  Channel_0.debounce++;
	  if (Channel_0.debounce >= Channel_0.debounce_target)
	      {

	     	 Channel_0.current_state = HAL_GPIO_ReadPin(GPIOA, RIGHT_Pin);

	     	 if (Channel_0.last_state == Channel_0.current_state)
	     	 {

	                 Channel_0.last_state = Channel_0.current_state;
	                 Channel_0.count++;
	                 Channel_0.debounce = 0;

	          }

	       }


  }
  if(Channel_1.debounce > 0)
    {
  	  Channel_1.debounce++;
  	  if (Channel_1.debounce >= Channel_1.debounce_target)
  	      {

  	     	 Channel_1.current_state = HAL_GPIO_ReadPin(GPIOA, LEFT_Pin);

  	     	 if (Channel_1.last_state == Channel_1.current_state)
  	     	 {

  	                 Channel_1.last_state = Channel_1.current_state;
  	                 Channel_1.count++;
  	                 Channel_1.debounce = 0;

  	          }

  	       }


    }
  /* USER CODE END TIM1_BRK_UP_TRG_COM_IRQn 1 */
}

/* USER CODE BEGIN 1 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    // Data processing code here using adc_buffer
	HAL_ADC_Stop_IT(hadc);
	for(int i =0;i<ADC_BUFFER_SIZE;i++)media += adc_buffer[i];
	media=media/ADC_BUFFER_SIZE;
	voltage = (media/4095.0) *3.3;
	media=0;
	//voltage = (adc_buffer[0] / 4095.0) * 3.3;

}
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == Channel_0.pin)
	{
		Channel_0.last_state =LOW;
		Channel_0.debounce = 1;
	}
	else if(GPIO_Pin == Channel_1.pin)
		{
			Channel_1.last_state =LOW;
			Channel_1.debounce = 1;
		}
}
/* USER CODE END 1 */
