#pragma once

#ifdef __cplusplus
extern "C" {
#endif

	/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

	extern void Error_Handler(void);
	/* USER CODE BEGIN 0 */

	/* USER CODE END 0 */

	/**
	* Initializes the Global MSP.
	*/
	void HAL_MspInit(void);
	void HAL_CAN_MspInit(CAN_HandleTypeDef* hcan);
	void HAL_CAN_MspDeInit(CAN_HandleTypeDef* hcan);
	void HAL_CRC_MspInit(CRC_HandleTypeDef* hcrc);
	void HAL_CRC_MspDeInit(CRC_HandleTypeDef* hcrc);
	void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c);
	void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c);
	void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi);
	void HAL_SPI_MspDeInit(SPI_HandleTypeDef* hspi);
	void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base);
	void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim);
	void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base);
	void HAL_UART_MspInit(UART_HandleTypeDef* huart);
	void HAL_UART_MspDeInit(UART_HandleTypeDef* huart);
	void HAL_WWDG_MspInit(WWDG_HandleTypeDef* hwwdg);
	void HAL_WWDG_MspDeInit(WWDG_HandleTypeDef* hwwdg);

#ifdef __cplusplus
}
#endif
