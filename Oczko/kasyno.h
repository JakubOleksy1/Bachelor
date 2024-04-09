#pragma once
#include "Karta.h"
#include "Gracz.h"
#include "Bot.h"

class Kasyno
{
private:
	Karta* kartaKasyna = new Karta[52];
	int liczbaKart = 52;
	int wygrana = 0;
	int liczbaGraczy = 0;
	int liczbaBotow = 0;
	int losowosc = 0;
	Bot* bot;
	Gracz* gracz;
public:
	Kasyno();
	int graj();
	void potasuj();
	Karta *dajKarte();
	void pokazTalie();
	void zapiszGre();
	int jeszczeRaz(int gra);
	~Kasyno();
};