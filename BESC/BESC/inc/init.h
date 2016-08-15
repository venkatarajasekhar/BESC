#pragma once

#include "stm32f0xx.h"
#include "main.h"

void GPIO_Pin_Init(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode, 
	GPIOSpeed_TypeDef GPIO_Speed, GPIOOType_TypeDef GPIO_OType, GPIOPuPd_TypeDef GPIO_PuPd);

static const int PwmStepCount = 500;

namespace PeripheralInit
{

	/* This function is obsolete, hence SHOULD NOT be called. */
	void InitClock(void);
	void InitGPIO(void);
	void InitEXTI(void);
	/* This function is obsolete, hence SHOULD NOT be called. */
	void InitNVIC(void);
	void InitTIM1(void);
	//void InitTIM2(void);
	//void InitTIM4(void);
	void InitADC1(void);
	void EnableCOMP1(void);
	void InitUSART1(void);
	void InitUSART2(void);
	//void SetCOMP1InvInp(const Comp1InvInp);
	//void SetCOMP1OutPol(const CompOutPol);

	void InitADC1(void);
}


