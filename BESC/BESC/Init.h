#pragma once
#include "Includes.h"

namespace Init
{
	void PinMux_Init(void);
	void GPIO_Init(void);
	void LPUART0_Init(void);
	status_t TPM0_Init(void);
	void Clock_init(void);
}
