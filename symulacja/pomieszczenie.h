#pragma once

class Pomieszczenie {
public:
	~Pomieszczenie();
	Pomieszczenie(float wysokosc, float szerokosc, float glebokosc);
	float getTemperatura() const { return temperaturaWewnetrzna; }
	float getTemperaturaPoprzednia();
	//float getTemperaturaPoprzednia1();
	float getCieploWchodzace() const { return cieploWchodzace; }
	void dodajCieplo(float cieplo);
	void aktualizuj(float timeStep = 1.0);

private:
	float wysokosc;
	float szerokosc;
	float glebokosc;
	float powierzchniaScian;
	float masaPowietrza;
	float temperaturaWewnetrzna;
	float temperaturaPoprzednia;
	float cieploWchodzace;
	const float cieploWlasciwe;
	const float gestoscPowietrza;
	const float gruboscScian;
	const float przewodnoscScian;
	const float temperaturaZewnetrzna;

	float utrataCiepla() const;
	float zmianaTemperatury(float cieplo, float czas = 1.0) const;
};