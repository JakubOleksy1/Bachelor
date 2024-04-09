#pragma once
#include "Karta.h"
#include <fstream>
#include <string>


class Gracz
{
private:
	char nickname[20];
	Karta* kartaGracza = new Karta[10];
	int czySpasowal = 0;
	int liczbaKartGracza = 0;
	int punktyGracza = 0;
	int przegral = 0;
public:
	Gracz();
	Gracz(int x);
	int ileKart();
	void wezKarte(Karta *karta);
	void jesliPrzegral();
	void pokazKarty();
	int czyDobrac();
	void zresetuj();
	int sprawdzCzySpasowal();
	int sprawdzCzyPrzegral();
	int podajPunkty();
	int ileKartGracza();
	char zapiszKarty(std::ofstream &plik, int i);
	int zliczDlugoscImienia();
	int podajTylkoPunkty();
	void spasowal();
	void nieSpasowal();
	char *podajImie();
	~Gracz();
};