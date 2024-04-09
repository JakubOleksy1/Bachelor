#pragma once
#include "Wojownik.h"

class Arena
{
private:
	Wojownik* w;

	int odleglosc = 0;
	int liczbaGraczy = 2;

public:
	Arena();
	~Arena();
	void rozpocznijGre();
	void obliczOdleglosc(int &odleglosc);
};