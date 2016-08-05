#include "Interrupt.h"
#include "Init.h"

extern "C"
{
	void delay(void)
	{
		volatile uint32_t i = 0;
		for (i = 0; i < 375000; ++i)
		{
			__asm("NOP"); /* delay */
		}
	}

	void delay2(void)
	{
		delay();
		delay();
	}

	void blink3(void)
	{
		GPIO_SetPinsOutput(GPIOA, 1u << 3);
		delay();
		GPIO_ClearPinsOutput(GPIOA, 1u << 3);
		delay();
	}

	void blink4(void)
	{
		GPIO_SetPinsOutput(GPIOA, 1u << 4);
		delay2();
		GPIO_ClearPinsOutput(GPIOA, 1u << 4);
		delay2();
	}

	void HardFault_Handler(void)
	{
		if (!InitCompleted)
		{
			Init::Clock_init();
			Init::PinMux_Init();
			Init::GPIO_Init();
		}

		for (int i = 0; i < 4; i++)
		{
			blink3();
		}

		for (int i = 0; i < 4; i++)
		{
			delay();
		}

		for (int i = 0; i < 3; i++)
		{
			blink3();
		}

		GPIO_SetPinsOutput(GPIOA, 1u << 3);
		while (true) {}
	}

	void LPUART0_IRQHandler(void)
	{
		/* If new data arrived. */
		if ((kLPUART_RxDataRegFullFlag)& LPUART_GetStatusFlags(LPUART0))
		{
			//LPUART_ClearStatusFlags(LPUART0, _lpuart_flags::kLPUART_RxDataRegFullFlag);
			uint8_t data = LPUART_ReadByte(LPUART0);
			LPUART_WriteByte(LPUART0, data);

			GPIO_TogglePinsOutput(GPIOA, 1u << 6);
			//delay();
			//GPIO_TogglePinsOutput(GPIOA, 1u << 6);
		}
	}
}

