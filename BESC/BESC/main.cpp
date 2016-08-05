#include "main.h"

volatile bool InitCompleted = false;

void delay(void)
{
	volatile uint32_t i = 0;
	for (i = 0; i < 10000; ++i)
	{
		__asm("NOP"); /* delay */
	}
}

void blink(void)
{
	GPIO_SetPinsOutput(GPIOA, 1u << 6);
	delay();
	GPIO_ClearPinsOutput(GPIOA, 1u << 6);
	delay();
}

/*!
* @brief Main function
*/
int main(void)
{
	Init::Clock_init();
	Init::PinMux_Init();
	Init::GPIO_Init();

	InitCompleted = true;

	bool brightnessUp = true; /* Indicate LED is brighter or dimmer */
	uint8_t updatedDutycycle = 0U;

	//while (1)
	{
		blink();
	}

	//Init::LPUART0_Init();
	auto s = Init::TPM0_Init();
	if (s != kStatus_Success)
	{
		blink();
	}
	//TPM_UpdatePwmDutycycle(TPM0, tpm_chnl_t::kTPM_Chnl_0, tpm_pwm_mode_t::kTPM_CenterAlignedPwm, 50);

	//blink();
	while (1)
	{
		// Delay to see the change of LED brightness
		//blink();
		for (int i = 0; i < 100; i++)
		{
			blink();
			TPM_UpdatePwmDutycycle(TPM0, tpm_chnl_t::kTPM_Chnl_0, tpm_pwm_mode_t::kTPM_CenterAlignedPwm, i);
		}
		for (int i = 0; i < 100; i++)
		{
			blink();
			TPM_UpdatePwmDutycycle(TPM0, tpm_chnl_t::kTPM_Chnl_0, tpm_pwm_mode_t::kTPM_CenterAlignedPwm, 100 - i);
		}
		// Start PWM mode with updated duty cycle
		//TPM_UpdatePwmDutycycle(TPM0, tpm_chnl_t::kTPM_Chnl_0, tpm_pwm_mode_t::kTPM_CenterAlignedPwm, updatedDutycycle);
		//TPM_UpdatePwmDutycycle(TPM0, tpm_chnl_t::kTPM_Chnl_1, tpm_pwm_mode_t::kTPM_CenterAlignedPwm, updatedDutycycle);
	}

	/*
	GPIO_TogglePinsOutput(GPIOA, 1u << 6);
	delay();
	GPIO_TogglePinsOutput(GPIOA, 1u << 6);

	// Enable RX interrupt.
	LPUART_EnableInterrupts(LPUART0, kLPUART_RxDataRegFullInterruptEnable);
	EnableIRQ(IRQn::LPUART0_IRQn);

	while (1)
	{
		delay();
		GPIO_TogglePinsOutput(GPIOA, 1u << 6);
	}
	*/
}
