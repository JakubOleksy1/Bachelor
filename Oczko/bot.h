#pragma once
#include <iostream>
#include "Kasyno.h"
#include "Gracz.h"
#include "Karta.h"

class Bot : public Gracz
{
public:
	std::string nicknameBota = "BOT";
	Bot() : Gracz(1) {};
	int zachowanie = 0;;
	void jakSieZachowywac();
	void doklej(int i);
	void zachowanieBota(int _punkty);
};