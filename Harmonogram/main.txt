#include <iostream>
#include "Czas.h"
#include "Harmonogram.h"
#include <stdlib.h>

int main()
{
	int koniec = 0;
	int wybor1 = 0;
	int rozmiar = 5; // zabezpiecznia przed wprowadzaniem blednych danych
	int rozmiar1 = 0;

	Harmonogram h(rozmiar); //wprowadzenie harmonogramu 1 na "sztywno"
	Czas cz1, cz2, cz3, cz4, cz5, czasZsumowany;
	cz1 = Czas(60, 59, 1);
	cz2 = Czas();
	cz3 = Czas(22, 37);
	cz4 = Czas(56);
	cz5 = Czas(1, 12, 28);
	h.dodajDoHarmonogramu(cz1, 0);
	h.dodajDoHarmonogramu(cz2, 1);
	h.dodajDoHarmonogramu(cz3, 2);
	h.dodajDoHarmonogramu(cz4, 3);
	h.dodajDoHarmonogramu(cz5, 4);
	h.podajWszystkieCzasy(rozmiar);

	while (koniec != 1) // Menu glowne
	{
		std::cout << "Co chcesz zrobic?\n1.Zwieksz sekudny\n2.Skopiuj harmonogram poprzez zadanie ilosci\n3.Skopiuj harmonogram czasem\n4.Zakoncz\n";
		wybor1 = h.zabezpieczenie(wybor1, &wybor1, 4, 1);
		switch (wybor1)
		{
		case 1:
		{
			int numerCzasu = 0;
			int iloscSekund = 0;
			system("cls");
			std::cout << "Podaj ktory czas cie interesuje" << std::endl;
			numerCzasu = h.zabezpieczenie(numerCzasu, &wybor1, 5, 1);
			std::cout << "Teraz podaj o ile sekund bedziesz chcial zwiekszyc czas" << std::endl;
			if (!(std::cin >> iloscSekund))
			{
				std::cout << "Podana wartosc nie jest cyfra, czyli koncze program." << std::endl;
				wybor1 = 4;
				break;
			}
			if (numerCzasu == 1)
			{
				cz1.zwiekszSekundy(iloscSekund);
				h.dodajDoHarmonogramu(cz1, 0);
			}
			if (numerCzasu == 2)
			{
				cz2.zwiekszSekundy(iloscSekund);
				h.dodajDoHarmonogramu(cz2, 1);
			}
			if (numerCzasu == 3)
			{
				cz3.zwiekszSekundy(iloscSekund);
				h.dodajDoHarmonogramu(cz3, 2);
			}
			if (numerCzasu == 4)
			{
				cz4.zwiekszSekundy(iloscSekund);
				h.dodajDoHarmonogramu(cz4, 3);
			}
			if (numerCzasu == 5)
			{
				cz5.zwiekszSekundy(iloscSekund);
				h.dodajDoHarmonogramu(cz5, 4);
			}
			h.podajWszystkieCzasy(rozmiar);
			break;
		}
		case 2:
		{
			int rozmiar2 = 0;
			system("cls");
			rozmiar2 = h.ile();
			if (rozmiar2 == 0)
			{
				wybor1 = 4;
			}
			else
			{
				if (rozmiar2 > rozmiar)
				{
					std::cout << "Podana cyfra jest za wysoka ustawiam na tyle na ile jest to mozliwe\n";
					rozmiar2 = rozmiar;
				}
				Harmonogram h2(rozmiar2);
				h2.utworzKopie(h, rozmiar2);
				h2.podajWszystkieCzasy(rozmiar2);
				std::cout << "Czy chcesz dodac jeszcze jakis czas?\n1.Tak\n2.Nie" << std::endl;
				int wybor2 = 0;
				wybor2 = h2.zabezpieczenie(wybor2, &wybor1, 2, 1);
				if (wybor2 == 1)
				{
					h2.podajKonkretnyCzas(&rozmiar2);
					h2.podajWszystkieCzasy(rozmiar2);
				}
				else
				{
					h2.podajWszystkieCzasy(rozmiar2);
				}
			}
			break;
		}
		case 3:
		{
			int rozmiar3 = 0;
			system("cls");
			rozmiar3 = h.ile2();
			if (rozmiar3 == 0)
			{
				wybor1 = 4;
			}
			else
			{
				if (rozmiar3 > rozmiar)
				{
					std::cout << "Podana cyfra jest za wysoka ustawiam na tyle na ile jest to mozliwe";
					rozmiar3 = rozmiar;
				}
				int wybor3 = 0;
				Harmonogram h3(rozmiar3);
				h3.utworzKopie(h, rozmiar3);
				h3.podajWszystkieCzasy(rozmiar3);
				std::cout << "Czy chcesz dodac jeszcze jakis czas?\n1.Tak\n2.Nie" << std::endl;
				wybor3 = h3.zabezpieczenie(wybor3, &wybor1, 2, 1);
				if (wybor3 == 1)
				{
					h3.podajKonkretnyCzas(&rozmiar3);
					h3.podajWszystkieCzasy(rozmiar3);
				}
				else
				{
					h3.podajWszystkieCzasy(rozmiar3);
				}
			}
			break;
		}
		case 4:
		{
			system("cls");
			koniec = 1;
			printf("Do widzenia!");
			break;
		}
		}
	}
}
/*NOTATKI
Jakub Oleksy 261347
dziala popraw bledy i gitara akcesory destruktory itd wycieki pamieci.
*/