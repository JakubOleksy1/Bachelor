#pragma once
#include "Grzejnik.h"
#include "Pomieszczenie.h"

class Regulator
{
private:
	Pomieszczenie* r;
	Grzejnik* g;
public:
	Regulator();
	~Regulator();
	virtual float ustawWarPoprzednia(float _zadanaTemp, float _warPoprzednia) = 0;
	virtual float steruj(float _zadanaTemp, float _czasPomiedzy, float _warZmierzona) = 0;
};