#pragma once

class Grzejnik
{
private:
	float mocNominalna = 0;
	float poziomMocy = 0;
	float mocObecna = 0;
public:
	Grzejnik();
	~Grzejnik();
	void sprawdzPoziomMocy(float _poziomMocy);
	float podajIleCiepla();
	float podajMocNominalna();
	float podajIleProcent();
	float ustawMocGrzejnika();
	float podajMocObecna();
	float jakiGrzejnik();
	void zamienMocGrzejnika();
	void zamienMocGrzejnikaRegulatorem(float _x);
};