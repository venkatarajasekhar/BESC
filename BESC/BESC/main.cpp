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

	/* Board pin, clock, debug console init */
    /* Debug uart port mux config */
    /* Enable uart port clock */
    CLOCK_EnableClock(kCLOCK_PortA);
	PORT_SetPinMux(PORTA, 6U, kPORT_MuxAsGpio);

	/* Init output LED GPIO. */
	GPIO_PinInit(GPIOA, 6U, &led_config);

	while (1)
	{
		delay();
		GPIO_TogglePinsOutput(GPIOA, 1u << 6);
	}
}
