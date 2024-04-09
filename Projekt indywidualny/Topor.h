#pragma once
#include "Bron.h"
#include "Wojownik.h"

class Topor : public Bron
{
private:
	int dmg = 100;

public:
	int obrazenia(int __odleglosc);
};