#include <iostream>
#include <vector>
#include <fstream>
#include "Symulacja.h"
#include "Grzejnik.h"
#include "Pomieszczenie.h"
#include "Regulator.h"
#include "RegulatorBB.h"
#include "RegulatorPID.h"
#include <cstdlib>

Symulacja::Symulacja()
{

}

Symulacja::~Symulacja()
{
}

void Symulacja::przeprowadzSymulacje()
{
	float x, y, z, k;
	std::cout << "Podaj nastepujace wymiary:\n";
	while (1)
	{
		std::cout << "Wysokosc [m]\n";
		std::cin >> x;
		std::cout << "Szerokosc [m]\n";
		std::cin >> y;
		std::cout << "Glebokosc [m]\n";
		std::cin >> z;
		if (std::cin.fail())
		{
			std::cout << "Wykryto blad. Podaj wartosci ponownie " << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			if (x >= 0 && y >= 0 && z >=0)
				break;
		}
	}

	Pomieszczenie p1(x, y, z);
	RegulatorBB rb1;
	RegulatorPID rp1;

	this->ktoryRegulator();
	if (this->podajWybor() == 1)
	{
		this->wybierzRegulator(&rb1);
	}
	else if (this->podajWybor() == 2)
	{
		this->wybierzRegulator(&rp1);
	}
	this->ustawWarZadana();
	this->wyzerujWybor();
	this->podajDaneSymulacji();

	try
	{
		k = this->uzyjRegulatora(this->podajWarZadana(), ((this->podajCzas() * 1) - (this->podajCzas() * (1 - 1))), p1.getTemperatura(), p1.getTemperaturaPoprzednia());
		this->g1.zamienMocGrzejnikaRegulatorem(k);
	}
	catch (...)
	{
		std::cout << "Nie wykryto wyboru regulatora. Wybierz go teraz\n";
		this->ktoryRegulator();
		if (this->podajWybor() == 1)
		{
			this->wybierzRegulator(&rb1);
		}
		else if (this->podajWybor() == 2)
		{
			this->wybierzRegulator(&rp1);
		}
	}

	std::vector<float> vCzasu;
	std::vector<float> vTemperatury;
	std::vector<float> vMocy;
	system("cls");
	for (int i = 0; i < this->podajIle(); i++)
	{
		k = this->uzyjRegulatora(this->podajWarZadana(), ((this->podajCzas() * i) - (this->podajCzas() * (i - 1))), p1.getTemperatura(), p1.getTemperaturaPoprzednia());
		this->g1.zamienMocGrzejnikaRegulatorem(k);
		p1.dodajCieplo(this->g1.podajMocObecna());
		p1.aktualizuj(this->podajCzas());

		std::cout << "Czas: " << (this->podajCzas() * i) << " Temperatura: " << p1.getTemperatura() << std::endl;

		vCzasu.push_back(this->podajCzas() * i);
		vTemperatury.push_back(p1.getTemperatura());
		vMocy.push_back(this->g1.podajMocObecna());
	}
	vCzasu.shrink_to_fit();
	vTemperatury.shrink_to_fit();
	vMocy.shrink_to_fit();

	this->zapiszDoCSV(vCzasu, vTemperatury, vMocy);
	vCzasu.clear();
	vTemperatury.clear();
	vMocy.clear();
	vCzasu.shrink_to_fit();
	vTemperatury.shrink_to_fit();
	vMocy.shrink_to_fit();
}

float Symulacja::uzyjRegulatora(float _zadanaTemp, float _czasPomiedzy, float _warZmierzona, float _warPoprzednia)
{
	if (r)
	{
		r->ustawWarPoprzednia(_zadanaTemp, _warPoprzednia);
		return r->steruj(_zadanaTemp, _czasPomiedzy, _warZmierzona);
	}
	else
	{
		throw 261347;
	}
}

void Symulacja::wybierzRegulator(Regulator* _r)
{
	r = _r;
}

void Symulacja::ktoryRegulator()
{
	system("cls");
	std::cout << "Jaki regulator?\n1.RegulatorBB\n2.RegulatorPID\n";
	while (1)
	{
		std::cin >> wybor;
		if (std::cin.fail())
		{
			std::cout << "Wykryto blad. Podaj wartosc ponownie " << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			if (wybor == 1 || wybor == 2)
			{
				break;
			}
			else
			{
				std::cout << "Podana wartosc nie jest ani 1 ani 2\nPodaj wartosc ponownie\n";
			}
		}
	}
}

void Symulacja::zapiszDoCSV(const std::vector<float> vCzasu, const std::vector<float> vTemperatury, const std::vector<float> vMocy)
{
	std::ofstream plik;
	std::locale pol("pl_PL");
	plik.imbue(pol);
	plik.open("SymulowaneTemperatury.csv", std::ofstream::out);
	if (plik.good() == true && plik.is_open() == true)
	{
		plik << "Czas" << "; " << "Temperatura" << "; " << "Moc" << std::endl;
		for (int i = 0; i < this->podajIle(); i++)
		{
			plik << vCzasu[i] << "; " << vTemperatury[i] << "; " << vMocy[i] << std::endl;
		}
		std::cout << "Zapisano do .csv\n";
		plik.close();
	}
}

void Symulacja::podajDaneSymulacji()
{
	this->iteracja(iczas);
	this->przebieg(ile, iczas);
}

void Symulacja::iteracja(float& _iczas)
{
	std::cout << "Podaj co ile dokonywany ma byc pomiar [s]\n";
	while (1)
	{
		std::cin >> _iczas;
		if (std::cin.fail())
		{
			std::cout << "Wykryto blad. Podaj wartosc ponownie " << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			if (_iczas > 0)
			{
				break;
			}
			else
			{
				std::cout << "Podana wartosc jest bledna\nPodaj wartosc ponownie\n";
			}
		}
	}
}

void Symulacja::przebieg(int& _ile, float& _iczas)
{
	std::cout << "Podaj ile iteracji chcesz wykonac (Ilosc powtorzen)\n";
	while (1)
	{
		std::cin >> _ile;
		if (std::cin.fail())
		{
			std::cout << "Wykryto blad. Podaj wartosc ponownie " << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			if (_ile >= 0)
			{
				break;
			}
			else
			{
				std::cout << "Podana wartosc jest bledna\nPodaj wartosc ponownie\n";
			}
		}
	}
}

void Symulacja::ustawWarZadana()
{
	system("cls");
	std::cout << "Jaka chcesz temperature uzyskac [*C] \n";
	while (1)
	{
		std::cin >> warZadana;
		if (std::cin.fail())
		{
			std::cout << "Wykryto blad. Podaj wartosc ponownie " << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
				break;
		}
	}
}

int Symulacja::podajIle()
{
	return ile;
}

float Symulacja::podajCzas()
{
	return iczas;
}

int Symulacja::podajWybor()
{
	return wybor;
}

void Symulacja::wyzerujWybor()
{
	wybor = 0;
}

float Symulacja::podajWarZadana()
{
	return warZadana;
}