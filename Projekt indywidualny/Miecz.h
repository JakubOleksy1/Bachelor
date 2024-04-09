#pragma once
#include "Bron.h"
#include "Wojownik.h"

class Miecz : public Bron
{
private:
	int dmg = 70;

public:
	int obrazenia(int __odleglosc);

};