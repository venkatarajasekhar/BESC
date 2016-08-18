//#include "main.h"

#include "stm32f10x.h"
//#include "stm32f10x_conf.h"

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

int main(void)
{
	/*!< At this stage the microcontroller clock setting is already configured,
	this is done through SystemInit() function which is called from startup
	file (startup_stm32f10x_xx.s) before to branch to application main.
	To reconfigure the default setting of SystemInit() function, refer to
	system_stm32f10x.c file
	*/

	/* GPIOC Periph clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	/* Configure PD0 and PD2 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* To achieve GPIO toggling maximum frequency, the following  sequence is mandatory.
	You can monitor PD0 or PD2 on the scope to measure the output signal.
	If you need to fine tune this frequency, you can add more GPIO set/reset
	cycles to minimize more the infinite loop timing.
	This code needs to be compiled with high speed optimization option.  */
	while (1)
	{
#define MASK (0x1<<13 | 0x1<<14)
		GPIO_SetBits(GPIOC, GPIO_Pin_13 | GPIO_Pin_14);
		/* Set PD0 and PD2 */
		//GPIOC->BSRR = MASK;
		/* Reset PD0 and PD2 */
		//GPIOC->BRR = MASK;
	}
}
