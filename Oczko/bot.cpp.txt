#include <iostream>
#include "Kasyno.h"
#include "Gracz.h"
#include "Karta.h"
#include "Bot.h"

void Bot::jakSieZachowywac()
{
	zachowanie = 1 + rand() % 3;
	std::cout << "Typ zachowania: " << zachowanie << std::endl;
}

void Bot::doklej(int i)
{
	if (i == 0)
	{
		char ch = '1';
		nicknameBota.push_back(ch);
	}
	if (i == 1)
	{
		char ch = '2';
		nicknameBota.push_back(ch);
	}
	if (i == 2)
	{
		char ch = '3';
		nicknameBota.push_back(ch);
	}
}

void Bot::zachowanieBota(int _punkty)
{
	if (zachowanie == 1)//ostrozny 
	{
		if (_punkty > 15 && _punkty < 21)
		{
			this->spasowal();
		}
		else if (_punkty < 15)
		{
			this->nieSpasowal();
		}
		else if (_punkty > 21)
		{
			this->spasowal();
		}
	}
	if (zachowanie == 2)//normalny
	{
		if (_punkty > 15 && _punkty < 21)
		{
			int szybkadecyzja = 0;
			szybkadecyzja = 1 + rand() % 2;
			if (szybkadecyzja == 1)
			{
				this->nieSpasowal();
			}
			else 
			{
				this->spasowal();
			}
		}
		else if (_punkty < 15)
		{
			this->nieSpasowal();
		}
		else if (_punkty > 21)
		{
			this->spasowal();
		}
	}
	if (zachowanie == 3)//ryzykujacy
	{
		if (_punkty > 18 && _punkty < 21)
		{
			this->spasowal();
		}
		else if (_punkty < 18)
		{
			this->nieSpasowal();
		}
		else if (_punkty > 21)
		{
			this->spasowal();
		}
	}
}