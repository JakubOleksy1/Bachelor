#pragma once
class Czas
{
private:
	int sekundy;
	int minuty;
	int godziny;
	void ustawSekundy(int noweSekundy);
	void ustawMinuty(int noweMinuty);
	void ustawGodziny(int noweGodziny);
public:
	Czas(int noweSekundy = 0, int noweMinuty = 0, int noweGodziny = 0);
	~Czas();
	void sprawdz();
	void wypiszCzas();
	void wyzerujCzas();
	void podejrzyjSekundy(Czas czas);
	void podejrzyjMinuty(Czas czas);
	void podejrzyjGodziny(Czas czas);
	void zwiekszSekundy(int noweSekundy);
	void ustawCzas(int noweSekundy = 0, int noweMinuty = 0, int noweGodziny = 0);

	int podajSekundy() { return sekundy; }
	int podajMinuty() { return minuty; }
	int podajGodziny() { return godziny; }

	Czas operator+(Czas _nowyCzas);
	Czas& operator+=(Czas _nwCzas);
	bool operator>(Czas _nowyCzas);
};





