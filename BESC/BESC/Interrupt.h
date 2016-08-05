#pragma once
#include "Includes.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

	static void HardFault_Handler(void) __attribute__((naked));
	//void HardFault_Handler(void);
	void LPUART0_IRQHandler(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/
