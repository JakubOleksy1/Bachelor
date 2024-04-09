#pragma once
#include "Grzejnik.h"
#include "Pomieszczenie.h"
#include "Regulator.h"

class Symulacja
{
private:
	float iczas = 0.0;
	int ile = 0;
	float czas = iczas * ile;
	float wybor = 0;
	int poIluZmiana = 0;
	float warZadana;
	Pomieszczenie p1(float, float, float);
	Regulator* r;
	Grzejnik g1;
	int zabezpieczenie;
public:
	Symulacja();
	~Symulacja();
	void przeprowadzSymulacje();
	void iteracja(float& _iczas);
	void przebieg(int& _ile, float& _iczas);
	void zapis(char* tab);
	void wybierzRegulator(Regulator* _r);
	int podajIle();
	float podajCzas();
	void podajDaneSymulacji();
	void ktoryRegulator();
	int podajWybor();
	void wyzerujWybor();
	float podajWarZadana();
	void ustawWarZadana();
	float uzyjRegulatora(float _zadanaTemp, float _czasPomiedzy, float _warZmierzona, float _warPoprzednia);
	void zapiszDoCSV(std::vector<float> vCzasu, std::vector<float> vTemperatury, std::vector<float> vMocy);
};