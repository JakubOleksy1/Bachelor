#include "Wojownik.h"
#include <iostream>

Wojownik::Wojownik()
{
	std::cout << "Podaj nazwe wojownika\n";
	while (1)
	{
		std::cin >> nazwa;
		if (std::cin.fail())
		{
			std::cout << "Wykryto blad. Podaj wartosc ponownie " << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			break;
		}
	}
	std::cout << "Wojownik (" << nazwa <<  ") wchodzi na arene\n";
}

void Wojownik::podniesBron(Bron* _bron)
{
	bron = _bron;
}

int Wojownik::wybierzBronGlowna()
{
	std::cout << "Wybierz bron glowna\n1.Miecz\n2.Topor\n3.Sztylet\n";
	while (1)
	{
		std::cin >> wybranaBron;
		if (std::cin.fail())
		{
			std::cout << "Wykryto blad. Podaj wartosc ponownie " << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			if (wybranaBron == 1 || wybranaBron == 2 || wybranaBron == 3)
			{
				break;
			}
			else
			{
				std::cout << "Podano niewlasciwa wartosc\nPodaj wartosc ponownie\n";
			}
		}
	}
	return wybranaBron;
}

void Wojownik::decyzja()
{
	if (this->energia == 0)
	{
		std::cout << "Musisz odpoczac\n";
		wyborAkcji = 5;
	}
	else
	{
		std::cout << "Co chcesz zrobic\n1.Zaatakuj\n2.Przysun sie\n3.Odsun sie\n4.Odpocznij";
		while (1)
		{
			std::cin >> wyborAkcji;
			if (std::cin.fail())
			{
				std::cout << "Wykryto blad. Podaj wartosc ponownie " << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else
			{
				if (wyborAkcji > 0 && wyborAkcji < 6)
				{
					break;
				}
				else
				{
					std::cout << "Podaj wartosc ponownie\n";
				}
			}
		}
	}
}

void Wojownik::ruch(int _pozycja)
{
	energia -= 5;
	if (pozycja == 10 || pozycja == -10)
	{
		std::cout << "Doszedles do sciany\n Wykorzystujesz moment na zlapanie oddechu\n";
		energia += 5;
		pozycja = pozycja - _pozycja;
	}
	else
	{
		pozycja = pozycja + _pozycja;
	}
}

void Wojownik::odpocznij()
{
	energia += 10;
	if (energia >= 100)
	{
		std::cout << "Nie mozesz miec wiecej energii niz 100\n";
		energia = 100;
	}
}

void Wojownik::podajDane()
{
	std::cout << "Zdrowie: " << punktyZdrowia << "\nEnergia: " << energia << std::endl;
}

void Wojownik::gdzieSieZnajduje(int _p1, int _p2)
{
	std::cout << "|";
	for (int i = -10; i < 11; i++)
	{
		if (i == _p1 || i == _p2)
		{
			std::cout << "X";
		}
		else
		{
			std::cout << "_";
		}
	}
	std::cout << "|";
}

int Wojownik::zaatakuj(int _odleglosc, int p1, int p2)
{
	int k = 0;
	if (wybranaBron == 1)
	{
		energia -= 10;
		k = this->bron->obrazenia(_odleglosc);
	}
	else if (wybranaBron == 3)
	{
		energia -= 5;
		int z;
		if (this->podajNumerGracza() == 1)
		{
			z = 2;
		}
		else if (this->podajNumerGracza() == 2)
		{
			z = -2;
		}
		this->ruch(z);
		_odleglosc = _odleglosc - 1;
		k = this->bron->obrazenia(_odleglosc);
		this->ruch(-z);
		_odleglosc = _odleglosc + 1;
	}
	else if (wybranaBron == 2)
	{
		energia -= 7;
		if (this->podajCzySieZamacha() == 1)
		{
			this->wykonujeZamachniecie();
		}
		else if (this->podajCzySieZamacha() == 0)
		{
			this->wykonalZamachniecie();
			k = this->bron->obrazenia(_odleglosc);
		}
	}
	return k;
}

int Wojownik::otrzymajObrazenia(int _x, int _y)
{
	_x = _x - _y;
	punktyZdrowia = _x;
	return _x;
}

int Wojownik::podajWybranaBron()
{
	return wybranaBron;
}

int Wojownik::sprawdzCzyZyje()
{
	return zgon;
}

int Wojownik::podajDecyzje()
{
	return wyborAkcji;
}

int Wojownik::podajAktualnaPozycje()
{
	return pozycja;
}

void Wojownik::ustawSie(int _x)
{
	pozycja = _x;
}

int Wojownik::podajPunktyZdrowia()
{
	return punktyZdrowia;
}

int Wojownik::podajCzySieZamacha()
{
	return czySieZamacha;
}

void Wojownik::przegral()
{
	zgon = 1;
	punktyZdrowia = 0;
}

std::string Wojownik::ZwrocNazwe()
{
	return nazwa;
}

void Wojownik::podajNazwe()
{
	std::cout << nazwa << "\n";
}

void Wojownik::wykonalZamachniecie()
{
	czySieZamacha = 1;
}

void Wojownik::wykonujeZamachniecie()
{
	czySieZamacha = 0;
}

void Wojownik::przypiszNumerGracza(int _x)
{
	numerGracza = _x;
}

int Wojownik::podajNumerGracza()
{
	return numerGracza;
}

int Wojownik::podajEnergie()
{
	return energia;
}

Wojownik::~Wojownik()
{

}