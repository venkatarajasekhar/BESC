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
	bool brightnessUp = true; /* Indicate LED is brighter or dimmer */
	uint8_t updatedDutycycle = 0U;

	/* Define the init structure for the output LED pin*/
	gpio_pin_config_t led_config = {
		kGPIO_DigitalOutput, 0,
	};

	Init::Clock_init();
	Init::PinMux_Init();
	Init::LPUART0_Init();
	Init::TPM0_Init();

	while (1)
	{
		/* Delay to see the change of LED brightness */
		delay();

		if (brightnessUp)
		{
			/* Increase duty cycle until it reach limited value */
			if (++updatedDutycycle == 100U)
			{
				brightnessUp = false;
			}
		}
		else
		{
			/* Decrease duty cycle until it reach limited value */
			if (--updatedDutycycle == 0U)
			{
				brightnessUp = true;
			}
		}
		/* Start PWM mode with updated duty cycle */
		TPM_UpdatePwmDutycycle(TPM0, tpm_chnl_t::kTPM_Chnl_0, tpm_pwm_mode_t::kTPM_CenterAlignedPwm, updatedDutycycle);
		TPM_UpdatePwmDutycycle(TPM0, tpm_chnl_t::kTPM_Chnl_1, tpm_pwm_mode_t::kTPM_CenterAlignedPwm, updatedDutycycle);
	}

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
