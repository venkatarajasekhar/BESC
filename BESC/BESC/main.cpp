#include "main.h"


void delay(void)
{
	volatile uint32_t i = 0;
	for (i = 0; i < 400000; ++i)
	{
		__asm("NOP"); /* delay */
	}
}

/*!
* @brief Main function
*/
int main(void)
{

	/* Define the init structure for the output LED pin*/
	gpio_pin_config_t led_config = {
		kGPIO_DigitalOutput, 0,
	};

	Init::Clock_init();
	Init::PinMux_Init();
	Init::LPUART0_Init();

	/* Init output LED GPIO. */
	GPIO_PinInit(GPIOA, 6U, &led_config);
	GPIO_TogglePinsOutput(GPIOA, 1u << 6);
	delay();
	GPIO_TogglePinsOutput(GPIOA, 1u << 6);

	/* Enable RX interrupt. */
	LPUART_EnableInterrupts(LPUART0, kLPUART_RxDataRegFullInterruptEnable);
	EnableIRQ(IRQn::LPUART0_IRQn);

	while (1)
	{
		delay();
		GPIO_TogglePinsOutput(GPIOA, 1u << 6);
	}
}
