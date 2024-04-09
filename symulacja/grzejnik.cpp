#include <iostream>
#include "Grzejnik.h"

Grzejnik::Grzejnik()
{
	this->jakiGrzejnik();
	this->ustawMocGrzejnika();
}

Grzejnik::~Grzejnik()
{
}

void Grzejnik::zamienMocGrzejnika()
{
	this->ustawMocGrzejnika();
}

void Grzejnik::zamienMocGrzejnikaRegulatorem(float _x)
{
	poziomMocy = _x;
	sprawdzPoziomMocy(poziomMocy);
	mocObecna = mocNominalna * poziomMocy;
}

void Grzejnik::sprawdzPoziomMocy(float _poziomMocy)
{
	if (_poziomMocy > 1)
	{
		std::cout << "Poziom mocy nie moze byc wiekszy od 100%\nUstawiam na 100%\n";
		_poziomMocy = 1;
	}
	else if (_poziomMocy < 0)
	{
		std::cout << "Poziom mocy nie moze by mniejszy od 0%\nUstawiam na 0%\n";
		_poziomMocy = 0;
	}
}

float Grzejnik::ustawMocGrzejnika()
{
	std::cout << "Podaj moc grzejnika w %\n";
	while (1)
	{
		std::cin >> poziomMocy;
		if (std::cin.fail())
		{
			std::cout << "Wykryto blad. Podaj wartosc ponownie " << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			system("cls");
			break;
		}
	}
	poziomMocy = poziomMocy / 100;
	sprawdzPoziomMocy(poziomMocy);
	mocObecna = mocNominalna * poziomMocy;
	return mocObecna;
}

float Grzejnik::jakiGrzejnik()
{
	std::cout << "Ile wat ma grzejnik\n";
	while (1)
	{
		std::cin >> mocNominalna;
		if (std::cin.fail())
		{
			std::cout << "Wykryto blad. Podaj wartosc ponownie " << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			if (mocNominalna >= 0)
				break;
		}
	}
	return mocNominalna;
}

float Grzejnik::podajIleCiepla()
{
	std::cout << "Cieplo w watach: " << mocObecna << std::endl;
	return mocObecna;
}

float Grzejnik::podajMocObecna()
{
	return mocObecna;
}

float Grzejnik::podajMocNominalna()
{
	return mocNominalna;
}

float Grzejnik::podajIleProcent()
{
	return poziomMocy;
}