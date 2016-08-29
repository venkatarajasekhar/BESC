#include "motor.h"

CMotor::CMotor(void)
{

}

CMotor::~CMotor(void)
{

}

/*
	*	This function takes SIGNED 8-bit integer as its argument.
	*	The range is from -128 to 127.
	*	0 to brake, -128 to coast.
	*/
MotorState CMotor::ChangeRotationSpeed(int8_t speed)
{
	if (speed == 0)
	{
		// Brake
		//TIM_SetCompare1(TIM1, 0);
		//TIM_SetCompare2(TIM1, 0);
		TIM1->CCR1 = 0;
		TIM1->CCR2 = 0;

		//GPIO_SetBits(GPIOB, GPIO_Pin_1 | GPIO_Pin_2);
		GPIOA->BSRR = GPIO_PIN_10 | GPIO_PIN_11;

		return this->State = MotorState::Brake;
	}

	if (speed != -128)
	{
		//GPIO_SetBits(GPIOB, GPIO_Pin_1 | GPIO_Pin_2);
		//GPIOA->BSRR = GPIO_PIN_10 | GPIO_PIN_11;
		// I think you don't even want to try to change this: 
		int pwm = (std::abs((float)speed) * (PwmRange / 127.0)) + PwmOffset;

		if (speed > 0)
		{
			// forward

			//TIM_SetCompare1(TIM1, pwm);
			//TIM_SetCompare2(TIM1, 0);
			TIM1->CCR1 = pwm;
			TIM1->CCR2 = 0;
			return this->State = MotorState::Forward;
		}
		else
		{
			// reverse

			//TIM_SetCompare1(TIM1, 0);
			//TIM_SetCompare2(TIM1, pwm);
			TIM1->CCR1 = 0;
			TIM1->CCR2 = pwm;
			return this->State = MotorState::Reverse;
		}
		GPIOA->BSRR = GPIO_PIN_10 | GPIO_PIN_11;
	}
	else
	{
		//GPIO_ResetBits(GPIOB, GPIO_Pin_1 | GPIO_Pin_2);
		GPIOA->BRR = GPIO_PIN_10 | GPIO_PIN_11;

		return this->State = MotorState::Coast;
	}
}

MotorState CMotor::Brake(void)
{
	TIM1->CCR1 = 0;
	TIM1->CCR2 = 0;
	GPIOA->BSRR = GPIO_PIN_10 | GPIO_PIN_11;

	return this->State = MotorState::Brake;
}

MotorState CMotor::Coast(void)
{
	//GPIO_ResetBits(GPIOB, GPIO_Pin_1 | GPIO_Pin_2);
	GPIOA->BRR = GPIO_PIN_10 | GPIO_PIN_11;

	return this->State = MotorState::Coast;
}

	
