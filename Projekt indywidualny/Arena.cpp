#include "Arena.h"
#include "Wojownik.h"
#include "Miecz.h"
#include "Topor.h"
#include "Sztylet.h"
#include <iostream>
#include <fstream>
#include <vector>

Arena::Arena()
{

}

void Arena::rozpocznijGre()
{
	Miecz m1;
	Topor t1;
	Sztylet sz1;

	std::vector<int> vZdrowia;
	std::vector<int> vEnergii;
	std::vector<std::string> vNazw(2);

	int n = 0;
	int z = 1;
	int k = 0;
	
	w = new Wojownik[2];
	liczbaGraczy = 2;
	for (int i = 0; i < liczbaGraczy; i++)
	{
		w[i].wybierzBronGlowna();
		if (w[i].podajWybranaBron() == 1)
		{
			w[i].podniesBron(&m1);
		}
		if (w[i].podajWybranaBron() == 2)
		{
			w[i].podniesBron(&t1);
		}
		if (w[i].podajWybranaBron() == 3)
		{
			w[i].podniesBron(&sz1);
		}
	}
	w[0].przypiszNumerGracza(1);
	w[1].przypiszNumerGracza(2);
	w[0].ustawSie(-2);
	w[1].ustawSie(2);

	system("cls");
	while (1)
	{
		for (int i = 0; i < liczbaGraczy; i++)
		{
			if (w[0].podajPunktyZdrowia() == 0)
			{
				w[0].przegral();
				system("cls");
				break;
			}
			else if (w[1].podajPunktyZdrowia() == 0)
			{
				w[1].przegral();
				system("cls");
				break;
			}
			w[i].gdzieSieZnajduje(w[0].podajAktualnaPozycje(), w[1].podajAktualnaPozycje());
			this->obliczOdleglosc(odleglosc);
			std::cout << "Ruch nr.: " << z << std::endl;
			std::cout << "Odleglosc miedzy gladiatorami: ";
			std::cout << odleglosc << std::endl;

			if (w[i].podajEnergie() > 0)
			{
				if (w[i].podajCzySieZamacha() == 1)
				{
					std::cout << "Kolej gracza: ";
					w[i].podajNazwe();
					w[i].podajDane();
					w[i].decyzja();
					system("cls");
					if (w[i].podajDecyzje() == 1)
					{
						try
						{
							if (i == 1)
							{
								w[0].otrzymajObrazenia(w[0].podajPunktyZdrowia(), w[i].zaatakuj(odleglosc, w[0].podajAktualnaPozycje(), w[1].podajAktualnaPozycje()));
							}
							else if (i == 0)
							{
								w[1].otrzymajObrazenia(w[1].podajPunktyZdrowia(), w[i].zaatakuj(odleglosc, w[0].podajAktualnaPozycje(), w[1].podajAktualnaPozycje()));
							}
						}
						catch (...)
						{
							std::cout << "Wyglada na to ze jeden gracz zgubil bron\nWalka zostaje przerwana aby kazdy mogl wybrac bron\n";
							for (int i = 0; i < liczbaGraczy; i++)
							{
								w[i].wybierzBronGlowna();
								if (w[i].podajWybranaBron() == 1)
								{
									w[i].podniesBron(&m1);
								}
								if (w[i].podajWybranaBron() == 2)
								{
									w[i].podniesBron(&t1);
								}
								if (w[i].podajWybranaBron() == 3)
								{
									w[i].podniesBron(&sz1);
								}
							}
							w[0].ustawSie(-2);
							w[1].ustawSie(2);
						}
					}
					if (w[i].podajDecyzje() == 2)
					{
						if (i == 0)
						{
							n = 1;
						}
						else if (i == 1)
						{
							n = -1;
						}
						w[i].ruch(2 * n);
						this->obliczOdleglosc(odleglosc);
						if (odleglosc == 0)
						{
							std::cout << "Gracz zaczynaja szarpanine. Po krotkiej walce cesarz nakazuje wrocic im na pozycje poczatkowe\n";
							w[0].ustawSie(-2);
							w[1].ustawSie(2);
						}
					}
					if (w[i].podajDecyzje() == 3)
					{
						if (i == 0)
						{
							n = 1;
						}
						else if (i == 1)
						{
							n = -1;
						}
						w[i].ruch(-2 * n);
						if (odleglosc == 0)
						{
							std::cout << "Gracz zaczynaja szarpanine. Po krotkiej walce cesarz nakazuje wrocic im na pozycje poczatkowe\n";
							w[0].ustawSie(-2);
							w[1].ustawSie(2);
						}
					}
					if (w[i].podajDecyzje() == 4)
					{
						w[i].odpocznij();
					}
				}
				else
				{
					if (i == 1)
					{
						w[0].otrzymajObrazenia(w[0].podajPunktyZdrowia(), w[i].zaatakuj(odleglosc, w[0].podajAktualnaPozycje(), w[1].podajAktualnaPozycje()));
					}
					else if (i == 0)
					{
						w[1].otrzymajObrazenia(w[1].podajPunktyZdrowia(), w[i].zaatakuj(odleglosc, w[0].podajAktualnaPozycje(), w[1].podajAktualnaPozycje()));
					}
				}
			}
			else
			{
				w[i].odpocznij();
			}
			if (w[0].podajPunktyZdrowia() <= 0)
			{
				w[0].przegral();
				system("cls");
				break;
			}
			else if (w[1].podajPunktyZdrowia() <= 0)
			{
				w[1].przegral();
				system("cls");
				break;
			}
		}
		if (w[0].podajPunktyZdrowia() <= 0)
		{
			w[0].przegral();
			system("cls");
			break;
		}
		else if (w[1].podajPunktyZdrowia() <= 0)
		{
			w[1].przegral();
			system("cls");
			break;
		}
		k++;
		if (k % 2 == 0)
		{
			z++;
		}
	}
	system("cls");
	std::cout << "Pojedynek zakonczyony\n";
	for (int i = 0; i < 2; i++)
	{
		w[i].podajNazwe();
		w[i].podajDane();
	}
	if (w[0].sprawdzCzyZyje() == 0)
	{
		std::cout << "Zwyciezyl: ";
		w[0].podajNazwe();
		std::cout << std::endl;
	}
	else if (w[1].sprawdzCzyZyje() == 0)
	{
		std::cout << "Zwyciezyl: ";
		w[1].podajNazwe();
		std::cout << std::endl;
	}

	for (int i = 0; i < liczbaGraczy; i++)
	{
		vZdrowia.push_back(w[i].podajPunktyZdrowia());
		vEnergii.push_back(w[i].podajEnergie());
		vNazw[i].assign(w[i].ZwrocNazwe());
	}
	vZdrowia.shrink_to_fit();
	vEnergii.shrink_to_fit();
	vNazw.shrink_to_fit();

	std::ofstream plik;
	std::locale pol("pl_PL");
	plik.imbue(pol);
	plik.open("Wynik walki.txt", std::ofstream::out);
	if (plik.good() == true && plik.is_open() == true)
	{
		for (int i = 0; i < 2; i++)
		{
			plik << "Nazwa gracza: " << vNazw[i] << "\nPunkty zdrowia: " << vZdrowia[i] << "\nPunkty energii: " << vEnergii[i] << std::endl << std::endl;
		}
		std::cout << "Zapisano do .txt\n";
		plik.close();
	}
	vZdrowia.clear();
	vEnergii.clear();
	vNazw.clear();
	vZdrowia.shrink_to_fit();
	vEnergii.shrink_to_fit();
	vNazw.shrink_to_fit();
}

void Arena::obliczOdleglosc(int &odleglosc)
{
	odleglosc = (-1*(w[0].podajAktualnaPozycje() - w[1].podajAktualnaPozycje()))/2;
}

Arena::~Arena()
{
	delete[] w;
}