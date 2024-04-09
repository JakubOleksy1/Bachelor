#include <iostream>
#include "Czas.h"
#include "Harmonogram.h"

void Czas::wyzerujCzas()
{
	sekundy = 0;
	minuty = 0;
	godziny = 0;
}

void Czas::ustawCzas(int noweSekundy, int noweMinuty, int noweGodziny)
{
	ustawSekundy(noweSekundy);
	ustawMinuty(noweMinuty);
	ustawGodziny(noweGodziny);
}

void Czas::ustawSekundy(int noweSekundy)
{
	if (noweSekundy < 0)
	{
		noweSekundy = 0;
	}
	if (noweSekundy > 59)
	{
		int i = 0;
		for (i = 0; noweSekundy > 59; i++)
		{
			noweSekundy = noweSekundy - 60;
		}
		sekundy = noweSekundy;
		minuty = minuty + i;
	}
	else
	{
		sekundy = sekundy + noweSekundy;
	}
}

void Czas::ustawMinuty(int noweMinuty)
{
	if (noweMinuty < 0)
	{
		noweMinuty = 0;
	}
	if (noweMinuty + minuty > 59)
	{
		int j = 0;
		for (j = 0; noweMinuty + minuty > 59; j++)
		{
			noweMinuty = noweMinuty - 60;
		}
		minuty = minuty + noweMinuty;
		godziny = godziny + j;
	}
	else
	{
		minuty = minuty + noweMinuty;
	}
}

void Czas::ustawGodziny(int noweGodziny)
{
	if (noweGodziny < 0)
	{
		noweGodziny = 0;
	}
	while (noweGodziny + godziny > 23)
	{
		noweGodziny = noweGodziny - 24;
	}
	godziny = godziny + noweGodziny;
}

void Czas::podejrzyjGodziny(Czas czas)
{
	std::cout << czas.podajGodziny() << std::endl;
}

void Czas::podejrzyjMinuty(Czas czas)
{
	std::cout << czas.podajMinuty() << std::endl;
}

void Czas::podejrzyjSekundy(Czas czas)
{
	std::cout << czas.podajSekundy() << std::endl;
}

void Czas::wypiszCzas()
{
	std::cout << "Czas: " << podajGodziny() << ":" << podajMinuty() << ":" << podajSekundy() << std::endl;
}

void Czas::zwiekszSekundy(int noweSekundy)
{
	sekundy = sekundy + noweSekundy;
	sprawdz();
}

bool Czas::operator>(Czas _nowyCzas)
{
	if ((godziny * 3600 + minuty * 60 + sekundy) > ((_nowyCzas.godziny * 3600) + (_nowyCzas.minuty * 60) + (_nowyCzas.sekundy)))
	{
		std::cout << 1 << std::endl;
		return true;
	}
	else
	{
		std::cout << 0 << std::endl;
		return false;
	}
}

Czas Czas::operator+(Czas _nowyCzas)
{
	Czas temp = _nowyCzas;
	temp.sekundy += sekundy;
	temp.minuty += minuty;
	temp.godziny += godziny;
	sprawdz();
	return temp;
}

Czas& Czas::operator+=(Czas _nwCzas)
{
	sekundy += _nwCzas.sekundy;
	return *this;
}

void Czas::sprawdz()
{
	if (sekundy > 59)
	{
		int i = 0;
		for (i = 0; sekundy > 59; i++)
		{
			sekundy = sekundy - 60;
		}
		minuty = minuty + i;
	}
	if (minuty > 59)
	{
		int j = 0;
		for (j = 0; minuty > 59; j++)
		{
			minuty = minuty - 60;
		}
		godziny = godziny + j;
	}
	while (godziny > 23)
	{
		godziny -= 24;
	}
}

Czas::Czas(int noweSekundy, int noweMinuty, int noweGodziny)
{
	wyzerujCzas();
	ustawCzas(noweSekundy, noweMinuty, noweGodziny);
}

Czas::~Czas()
{
}

