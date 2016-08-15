#pragma once

#define __attribute__(x) 
//#include "../Libraries/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_include.h"

#include "stm32f0xx.h"
#include "system_stm32f0xx.h"

#include <stdio.h>
#include <cmath>
//#include <thread>

#include "stm32f0xx_conf.h"

enum class MotorState;

#include "init.h"
#include "interrupt.h"
#include "motor.h"

extern uint32_t SystemCoreClock;

extern CMotor *Motor;

enum class MainMsg
{
	StartMotor,
	StopMotor,
	CompInterrupt
};

enum class MotorState
{
	Coast,
	Stop,
	Brake,
	Forward,
	Reverse
};

struct rotation
{
	uint8_t Speed = 0;
	bool CW = true;
};

int main(void);

void blink(void);

void COMP1Interrupt(void);

//static void COMP1_2_3_IRQHandler(void) __attribute__((interrupt("IRQ")));
