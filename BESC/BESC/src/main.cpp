//#include "main.h"

#include "stm32f10x.h"
#include "stm32f10x_conf.h"

/*
uint32_t _clocks_in_us;

CMotor *Motor;

__IO uint16_t ADC1ConvertedValue;

void delay_us(unsigned int delay)
{
	unsigned int t = delay * _clocks_in_us;
	for (unsigned int i = 0; i < t; i++)
	{
		__NOP();
	}
}

void blink()
{
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
	delay_us(10000);
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
}*/

GPIO_InitTypeDef GPIO_InitStructure;

int main(void)
{
	/*!< At this stage the microcontroller clock setting is already configured,
	this is done through SystemInit() function which is called from startup
	file (startup_stm32f10x_xx.s) before to branch to application main.
	To reconfigure the default setting of SystemInit() function, refer to
	system_stm32f10x.c file
	*/

	/* GPIOD Periph clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	/* Configure PD0 and PD2 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	//_clocks_in_us = 48000000 / 1000000;

	while (1)
	{
		// Main loop

	}

	return 0;
}
