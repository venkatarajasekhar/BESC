#pragma once

#define __attribute__(x) 
//#include "../Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_include.h"

#include "includes.h"

extern uint32_t SystemCoreClock;

extern CMotor *Motor;

enum class MainMsg
{
	StartMotor,
	StopMotor,
	CompInterrupt
};

struct rotation
{
	uint8_t Speed = 0;
	bool CW = true;
};

int main(void);

void blink(void);

//void COMP1Interrupt(void);

//static void COMP1_2_3_IRQHandler(void) __attribute__((interrupt("IRQ")));
