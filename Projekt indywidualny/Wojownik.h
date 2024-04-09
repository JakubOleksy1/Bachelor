#pragma once
#include "Bron.h"
#include <string>

class Wojownik
{
private:
	Bron* bron;

	std::string nazwa;

	int zgon = 0;
	int wyborAkcji;
	int pozycja = 0;
	int energia = 100;
	int numerGracza = 0;
	int wybranaBron = 0;
	int czySieZamacha = 1;
	int punktyZdrowia = 100;

public:
	Wojownik();
	~Wojownik();

	int podajEnergie();
	int podajDecyzje();
	int sprawdzCzyZyje();
	int podajWybranaBron();
	int podajNumerGracza();
	int wybierzBronGlowna();
	int podajPunktyZdrowia();
	int podajCzySieZamacha();
	int podajAktualnaPozycje();
	int otrzymajObrazenia(int _x, int _y);
	int zaatakuj(int _odleglosc, int _p1, int _p2);

	void decyzja();
	void przegral();
	void podajDane();
	void odpocznij();
	void podajNazwe();
	void ustawSie(int _x);
	void ruch(int _pozycja);
	void wykonalZamachniecie();
	void wykonujeZamachniecie();
	void podniesBron(Bron* _bron);
	void przypiszNumerGracza(int _x);
	void gdzieSieZnajduje(int _p1, int _p2);

	std::string ZwrocNazwe();
};