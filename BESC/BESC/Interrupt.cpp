#include "Interrupt.h"

extern "C"
{
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

