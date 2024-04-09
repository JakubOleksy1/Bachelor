#pragma once
#include "Bron.h"
#include "Wojownik.h"

class Sztylet : public Bron
{
private:
	int dmg = 40;

public:
	int obrazenia(int __odleglosc);
};