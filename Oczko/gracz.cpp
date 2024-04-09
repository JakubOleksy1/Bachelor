#include <iostream>
#include "Gracz.h"
#include "Karta.h"
#include "Kasyno.h"
#include "Bot.h"

void Gracz::wezKarte(Karta* _karta)
{
	int zliczTemp = liczbaKartGracza;
	zliczTemp++;
	int zliczaczPozostalych = 0;
	for(int i = 0; i < 52; i++)
	{
		if (_karta[i].getWartosc() != 0 && _karta[i].getKolor() >= 3 && _karta[i].getKolor() <= 6)
		{
			zliczaczPozostalych++;
		}
	}
	zliczaczPozostalych--;
	if (liczbaKartGracza < 10)
	{
		this->kartaGracza[liczbaKartGracza] = _karta[zliczaczPozostalych];
		liczbaKartGracza = zliczTemp;
	}
	else
	{
		std::cout << "Nie mozesz posiadac wiecej kart\n";
	}
}

Gracz::Gracz(int x)
{	
}

Gracz::Gracz()
{
	std::cout << "Podaj nazwe uzytkownika:" << std::endl;
	while (1)
	{
		std::cin >> nickname;
		int p = 0;
		while (nickname[p] != '\0')
		{
			p++;
		}
		if (p > 0 && p < 20)
		{
			break;
		}
		else
		{
			std::cout << "Podana nazwa jest za dluga. Podaj nickname ponownie." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	std::cout << "Witaj " << nickname << std::endl;
}

char *Gracz::podajImie()
{
	return nickname;
}

int Gracz::czyDobrac()
{
	int wybor = 0;
	std::cout << "Czy chcesz dobrac karte?\n1.Tak\n2.Nie\n";
	while (1)
	{
		std::cin >> wybor;
		if (std::cin.fail())
		{
			std::cout << "Wykryto blad. Podaj wartosc ponownie " << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			if (wybor > 0 && wybor < 3) 
			break;
		}
	}
	if (wybor == 1)
	{
		czySpasowal = 1;
		return czySpasowal;
	}
	else
	{
		czySpasowal = 2;
		std::cout << "Spasowano\n";
		return czySpasowal;
	}
}

int Gracz::podajTylkoPunkty()
{
	int s = 0;
	for (int i = 0; i < liczbaKartGracza; i++)
	{
		s += kartaGracza[i].getWartosc();
	}
	return s;
}

int Gracz::ileKart()
{
	std::cout << "Liczba kart: " << liczbaKartGracza << std::endl;
	{
		for (int i = 0; i < liczbaKartGracza; i++)
		{
			punktyGracza += kartaGracza[i].getWartosc();
		}
	}
	std::cout << "Liczba punktow: " << punktyGracza << std::endl;
	return liczbaKartGracza;
}

void Gracz::pokazKarty()
{
	std::cout << "Gracz posiada nastepujace karty: ";
	for (int i = 0; i < liczbaKartGracza; i++)
	{
		kartaGracza[i].wypisz();
		std::cout << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void Gracz::jesliPrzegral()
{
	if (punktyGracza > 21)
	{
		punktyGracza = -1000;
		przegral = 1;
	}
}

void Gracz::zresetuj()
{
	czySpasowal = 0;
	liczbaKartGracza = 0;
	punktyGracza = 0;
	przegral = 0;
}

int Gracz::sprawdzCzySpasowal()
{
	return czySpasowal;
}

int Gracz::sprawdzCzyPrzegral()
{
	if (this->podajTylkoPunkty() > 21)
	{
		przegral = 1;
	}
	else
	{
		przegral = 0;
	}
	return przegral;
}

int Gracz::ileKartGracza()
{
	return liczbaKartGracza;
}

int Gracz::podajPunkty()
{
	return punktyGracza;
}

void Gracz::spasowal()
{
	czySpasowal = 2;
}

void Gracz::nieSpasowal()
{
	czySpasowal = 1;
}

int Gracz::zliczDlugoscImienia()
{	
	int p = 0;
	while (nickname[p] != '\0')
	{
		p++;
	}
	return p;
}

char Gracz::zapiszKarty(std::ofstream &plik, int i)
{
	int z = kartaGracza[i].getKolor();
	plik << " " << kartaGracza[i].getFigura();
	if (z == 3)
	{
		plik << "@ ";
	}
	if (z == 4)
	{
		plik << "^ ";
	}
	if (z == 5)
	{
		plik << "% ";
	}
	if (z == 6)
	{
		plik << "# ";
	}
	return 0;
}

Gracz::~Gracz()
{
	delete[] kartaGracza;
}

