#pragma once
#include "Regulator.h"

class RegulatorBB : public Regulator
{
private:

public:
	RegulatorBB();
	~RegulatorBB();
	float ustawWarPoprzednia(float _zadanaTemp, float _warPoprzednia);
	float steruj(float _zadanaTemp, float _czasPomiedzy, float _warZmierzona);
};