#pragma once
#include "Czas.h"

class Harmonogram
{
private:
	Czas* tab;
	int rozmiar;
public:
	Harmonogram();
	Harmonogram(int rozmiar);
	~Harmonogram();

	void podajWszystkieCzasy(int rozmiar);
	void ileCzasow(int rozmiar);
	void dodajDoHarmonogramu(Czas cz, int i);
	void utworzKopie(Harmonogram h, int ilekopii);

	Czas* podajKonkretnyCzas(int* rozmiar);
	Czas zsumujCzasy(Czas czasZsumowany, int rozmiar);
	Harmonogram& operator=(const Harmonogram& _inny);

	int podajrozmiar(int rozmiar);
	int ile();
	int ile2();
	int zabezpieczenie(int wybor, int *wybor1, int x, int y);

};