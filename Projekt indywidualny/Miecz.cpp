#include "Miecz.h"
#include "Wojownik.h"
#include <iostream>

int Miecz::obrazenia(int __odleglosc)
{
	if (__odleglosc <= 1)
	{
		return dmg;
	}
	else
	{
		std::cout << "Miecz nie siegnal przeciwnika\n";
		return 0;
	}
}