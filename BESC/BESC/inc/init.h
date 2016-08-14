#pragma once

#include "includes.h"

/*void GPIO_Pin_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode, 
	GPIOSpeed_TypeDef GPIO_Speed);*/

static const int PwmStepCount = 500;

namespace PeripheralInit
{
	void InitGPIO(void);
	void InitEXTI(void);
	void InitTIM1(void);
	//void InitTIM2(void);
	//void InitTIM4(void);
	void InitADC1(void);
	void InitUSART1(void);
	void InitUSART2(void);
	//void SetCOMP1InvInp(const Comp1InvInp);
	//void SetCOMP1OutPol(const CompOutPol);

	void InitADC1(void);
}


