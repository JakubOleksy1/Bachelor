#include "RegulatorPID.h"
#include <iostream>

RegulatorPID::RegulatorPID()
{
}

RegulatorPID::~RegulatorPID()
{
}

float RegulatorPID::ustawWarPoprzednia(float _zadanaTemp, float _warPoprzednia)
{
	uchybPoprzedni = _zadanaTemp - _warPoprzednia;
	return uchybPoprzedni;
}

float RegulatorPID::steruj(float _zadanaTemp, float _czasPomiedzy, float _warZmierzona)
{
	//czesc P
	uchyb = _zadanaTemp - _warZmierzona;
	p = kp * uchyb;

	//czesc I
	uchybCalka = uchybCalka + (uchyb * _czasPomiedzy);
	i = ki * uchybCalka;

	//czesc D
	try
	{
		deltaUchyb = (uchyb - uchybPoprzedni) / _czasPomiedzy;
		if (_czasPomiedzy == 0)
		{
			throw errord;
		}

	}
	catch (float errord)
	{
		std::cout << "Dzielenie przez 0\n";
		d = 0;
	}
	d = kd * deltaUchyb;
	wynik = p + i + d;
	if (wynik > 1)
	{
		wynik = 1;
	}
	else if (wynik < 0)
	{
		wynik = 0;
	}
	return wynik;
}