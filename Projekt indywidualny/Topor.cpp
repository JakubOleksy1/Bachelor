#include "Topor.h"
#include <iostream>
#include "Wojownik.h"

int Topor::obrazenia(int __odleglosc)
{
		if (__odleglosc <= 1)
		{
			return dmg;
		}
		else
		{
			std::cout << "Topor nie siegnal przeciwnika\n";
			return 0;
		}
}