#pragma once

class CMotor;

#include "main.h"

class CMotor
{
private:

public:
	static const int PwmOffset = 21;
	static const int PwmMax = 491;
	static const int PwmRange = PwmMax - PwmOffset;

	CMotor(void);
	~CMotor(void);

	MotorState State;

	MotorState ChangeRotationSpeed(int8_t speed);
	MotorState Brake(void);
	MotorState Coast(void);
};
