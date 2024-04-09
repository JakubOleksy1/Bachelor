#include "Sztylet.h"
#include "Wojownik.h"
#include <iostream>

int Sztylet::obrazenia(int __odleglosc)
{
	if (__odleglosc < 1)
	{
		return dmg;
	}
	else
	{
		std::cout << "Sztylet nie siegnal przeciwnika\n";
		return 0;
	}
}