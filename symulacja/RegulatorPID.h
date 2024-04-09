#pragma once
#include "Regulator.h"

class RegulatorPID : public Regulator
{
private:
	float uchyb = 0;
	float p = 0;
	float i = 0;
	float d = 0;
	float wynik = 0;
	float uchybCalka = 0;
	float deltaUchyb = 0;
	float uchybPoprzedni = 0;
	float errord = 0;
	float kp = 4.0;
	float ki = 0.02;
	float kd = 0.1;
public:
	RegulatorPID();
	~RegulatorPID();
	float ustawWarPoprzednia(float _zadanaTemp, float _warPoprzednia);
	float steruj(float _zadanaTemp, float _czasPomiedzy, float _warZmierzona);
};