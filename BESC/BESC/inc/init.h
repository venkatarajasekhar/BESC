#pragma once

#include "includes.h"

/*void GPIO_Pin_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode, 
	GPIOSpeed_TypeDef GPIO_Speed);*/

extern CAN_HandleTypeDef hcan;

extern CRC_HandleTypeDef hcrc;

extern I2C_HandleTypeDef hi2c2;

extern SPI_HandleTypeDef hspi1;

extern TIM_HandleTypeDef htim1;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

extern WWDG_HandleTypeDef hwwdg;

static const int PwmStepCount = 500;

void SystemClock_Config(void);
void Error_Handler(void);

namespace Init
{
	void MX_GPIO_Init(void);
	void MX_CAN_Init(void);
	void MX_CRC_Init(void);
	void MX_I2C2_Init(void);
	void MX_SPI1_Init(void);
	void MX_TIM1_Init(void);
	void MX_USART1_UART_Init(void);
	void MX_USART2_UART_Init(void);
	void MX_WWDG_Init(void);
}

extern "C"
{
	void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
}

