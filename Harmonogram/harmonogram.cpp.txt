#include <iostream>
#include "Harmonogram.h"
#include <algorithm>


Harmonogram::Harmonogram()
	: tab(nullptr) {}
Harmonogram::Harmonogram(int rozmiar)
{
	tab = new Czas[rozmiar];
}

Harmonogram::~Harmonogram()
{
}

Czas Harmonogram::zsumujCzasy(Czas _czasZsumowany, int rozmiar)
{
	int a = 0;
	int b = 0;
	int c = 0;
	for (int i = 0; i < rozmiar; i++)
	{
		a += tab[i].podajSekundy();
		b += tab[i].podajMinuty();
		c += tab[i].podajGodziny();
	}
	_czasZsumowany.ustawCzas(a, b, c);
	std::cout << "Czas zsumowany" << std::endl;
	return _czasZsumowany;
}


void Harmonogram::dodajDoHarmonogramu(Czas cz, int i)
{
	tab[i] = cz;
}

void Harmonogram::podajWszystkieCzasy(int rozmiar)
{
	for (int i = 0; i < rozmiar; i++)
	{
		tab[i].wypiszCzas();
	}
}

Czas* Harmonogram::podajKonkretnyCzas(int* _prozmiar)
{
	int chcianyCzas;
	int rozmiar = *_prozmiar;
	int wybor = 0;
	std::cout << "Podaj numer czasu ktory chcesz zobaczyc." << std::endl;
	std::cin >> chcianyCzas;
	while (chcianyCzas < 0 || chcianyCzas > rozmiar)
	{
		std::cout << "Podaj numer czasu ponownie" << std::endl;
		std::cin >> chcianyCzas;
	}
	tab[chcianyCzas - 1].wypiszCzas();
	std::cout << "Chcesz go dodac?\n1.Tak\n2.Nie\n" << std::endl;
	std::cin >> wybor;
	while (wybor < 0 || wybor > 2)
	{
		std::cout << "Podaj wartosc ponownie.\n1.Tak\n2.Nie" << std::endl;
		std::cin >> wybor;
	}
	if (wybor == 1)
	{
		Czas* wsktemp = nullptr;
		rozmiar++;
		wsktemp = new Czas[rozmiar];
		for (int i = 0; i < rozmiar - 1; i++)
		{
			wsktemp[i] = tab[i];
		}
		if (rozmiar - 1 >= chcianyCzas)
		{
			wsktemp[rozmiar - 1] = tab[chcianyCzas - 1];
		}
		delete[] tab;
		tab = new Czas[rozmiar];
		*tab = *wsktemp;
		for (int i = 0; i < rozmiar; i++)
		{
			tab[i] = wsktemp[i];
		}
		*_prozmiar = rozmiar;
		delete[] wsktemp;
		return tab;
	}
	else
	{
		return tab;
	}
}

void Harmonogram::ileCzasow(int rozmiar)
{
	std::cout << rozmiar << std::endl;
}

int Harmonogram::podajrozmiar(int rozmiar)
{
	rozmiar = 4;
	return rozmiar;
}

Harmonogram& Harmonogram::operator=(const Harmonogram& _inny)
{
	if (this == &_inny)
	{
		return *this;
	}
	rozmiar = _inny.rozmiar;
	tab = new Czas[rozmiar];
	memcpy(tab, _inny.tab, rozmiar);
	delete[] tab;
	return *this;
}

void Harmonogram::utworzKopie(Harmonogram h, int ilekopii)
{
	for (int i = 0; i < ilekopii; i++)
	{
		tab[i] = h.tab[i];
	}
}

int Harmonogram::ile()
{
	int ilekopii = 0;
	std::cout << "Podaj ile czasow chcesz skopiowac?" << std::endl;
	if(!(std::cin >> ilekopii))
	{
		std::cout << "Podana wartosc nie jest cyfra. Ustawiam na 0" << std::endl;
		ilekopii = 0;
	}
	return ilekopii;
}

int Harmonogram::ile2()
{
	int s = 0;
	int m = 0;
	int g = 0;
	int a = 0;
	int c = 0;
	Czas czastemp, czaspodany;
	std::cout << "Podaj czas w formacie godziny, minuty, sekundy" << std::endl;
	if(!(std::cin >> g))
	{
		std::cout << "Podana wartosc nie jest cyfra. Ustawiam na 0" << std::endl;
		g = 0;
	}
	if (!(std::cin >> m))
	{
		std::cout << "Podana wartosc nie jest cyfra. Ustawiam na 0" << std::endl;
		m = 0;
	}
	if (!(std::cin >> s))
	{
		std::cout << "Podana wartosc nie jest cyfra. Ustawiam na 0" << std::endl;
		s = 0;
	}
	czaspodany.ustawCzas(s, m, g);
	czastemp = tab[0];
	s = 0;
	m = 0;
	g = 0;
	while ((czaspodany.podajSekundy() + (60*czaspodany.podajMinuty()) + (3600*czaspodany.podajGodziny())) > (czastemp.podajSekundy() + (60 * czastemp.podajMinuty()) + (3600 * czastemp.podajGodziny())))
	{
		s = tab[c+1].podajSekundy();
		m = tab[c+1].podajMinuty();
		g = tab[c+1].podajGodziny();
		czastemp.ustawCzas(s, m, g);
		czastemp.sprawdz();
		c++;
	}
	return c;
}

int Harmonogram::zabezpieczenie(int wybor, int *wybor1, int x, int y)
{
	std::cin >> wybor;
	while (wybor > x || wybor < y)
	{
		std::cout << "Podaj wartosc ponownie\n";
		if (!(std::cin >> wybor))
		{
			std::cout << "Podana wartosc nie jest cyfra, czyli koncze program." << std::endl;
			std::cin.get();
			*wybor1 = 4;
			break;
		}
	}
	return wybor;
}