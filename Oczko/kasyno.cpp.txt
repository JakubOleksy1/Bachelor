#include <iostream>
#include <cstdlib>
#include <fstream>
#include "Kasyno.h"
#include "Karta.h"
#include "Bot.h"

Kasyno::Kasyno()
{
	std::cout << "Podaj liczbe botow" << std::endl;
	while (1)
	{
		std::cin >> liczbaBotow;
		if (std::cin.fail())
		{
			std::cout << "Wykryto blad. Podaj wartosc ponownie " << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			if (liczbaBotow >= 0 && liczbaBotow < 4)
				break;
		}
	}
	std::cout << "Podaj liczbe graczy ludzkich" << std::endl;
	while (1)
	{
		std::cin >> liczbaGraczy;
		if (std::cin.fail())
		{
			std::cout << "Wykryto blad. Podaj wartosc ponownie " << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			if (liczbaGraczy > 0 && liczbaGraczy < 4)
				break;
		}
	}
	bot = new Bot[liczbaBotow];
	for (int i = 0; i < liczbaBotow; i++)
	{
		bot[i].doklej(i);
		std::cout << bot[i].nicknameBota << "     ";
		bot[i].jakSieZachowywac();
	}
	gracz = new Gracz[liczbaGraczy];
	int k = 0;
	for(int i = 0; i<4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			kartaKasyna[j+k].setKolor(i);
			kartaKasyna[j+k].setWartosc(j);
		}
		k += 13;
	}
}

int Kasyno::graj()
{
	int gra = 0;
	for (int i = 0; i < liczbaGraczy; i++)
	{
		gracz[i].zresetuj();
	}
	for (int i = 0; i < liczbaBotow; i++)
	{
		bot[i].zresetuj();
	}
	this->potasuj();
	for (int j = 0; j < 2; j++)
	{
		if (liczbaBotow != 0)
		{
			for (int i = 0; i < liczbaBotow; i++)
			{
				this->bot[i].wezKarte(this->kartaKasyna);
				this->dajKarte();
			}
		}
		for (int i = 0; i < liczbaGraczy; i++)
		{
			this->gracz[i].wezKarte(this->kartaKasyna);
			this->dajKarte();
		}
	}
	while (wygrana != 1)
	{
		for (int i = 0; i < liczbaGraczy; i++)
		{
			if (gracz[i].sprawdzCzyPrzegral() == 0)
			{
				system("cls");
				std::cout << "Kolej gracza o imieniu: " << gracz[i].podajImie() << std::endl;
				this->gracz[i].pokazKarty();
				std::cout << "Liczba punktow: " << this->gracz[i].podajTylkoPunkty() << std::endl;
				gracz[i].czyDobrac();
			}
			else
			{
				gracz[i].spasowal();
			}
			if (gracz[i].sprawdzCzySpasowal() < 2)
			{
				this->gracz[i].wezKarte(this->kartaKasyna);
				this->dajKarte();
				this->gracz[i].pokazKarty();
			}
		}
		for (int i = 0; i < liczbaBotow; i++)
		{
			if (bot[i].sprawdzCzyPrzegral() == 0)
			{
				bot[i].zachowanieBota(bot[i].podajTylkoPunkty());
			}
			else
			{
				bot[i].spasowal();
			}
			if (bot[i].sprawdzCzySpasowal() < 2)
			{
				this->bot[i].wezKarte(this->kartaKasyna);
				this->dajKarte();
			}
		}
		system("cls");
		if (liczbaGraczy == 1)
		{
			if (liczbaBotow == 1)
			{
				if (gracz[0].sprawdzCzySpasowal() == 2 && bot[0].sprawdzCzySpasowal() == 2 || gracz[0].podajPunkty() > 21 || bot[0].podajPunkty() > 21)
				{
					wygrana = 1;
					std::cout << "Imie: " << gracz[0].podajImie() << std::endl;
					this->gracz[0].ileKart();
					this->gracz[0].pokazKarty();
					gracz[0].jesliPrzegral();
					std::cout << "Imie: BOT" << 1 << std::endl;
					this->bot[0].ileKart();
					this->bot[0].pokazKarty();
					bot[0].jesliPrzegral();
					if (gracz[0].podajPunkty() > bot[0].podajPunkty())
					{
						std::cout << "Wygral  " << gracz[0].podajImie() << std::endl;
					}
					else if (bot[0].podajPunkty() == gracz[0].podajPunkty())
					{
						std::cout << "Wyglada na to ze mamy remis\n";
					}
					else
					{
						std::cout << "Wygral BOT1" << std::endl;
					}
					gra = this->jeszczeRaz(gra);
				}
			}
			if (liczbaBotow == 2)
			{
				if (gracz[0].sprawdzCzySpasowal() == 2 && bot[0].sprawdzCzySpasowal() == 2 && bot[1].sprawdzCzySpasowal() == 2 || gracz[0].podajPunkty() > 21 || bot[0].podajPunkty() > 21 || bot[1].podajPunkty() > 21)
				{
					wygrana = 1;
					std::cout << "Imie: " << gracz[0].podajImie() << std::endl;
					this->gracz[0].ileKart();
					this->gracz[0].pokazKarty();
					gracz[0].jesliPrzegral();
					for (int i = 0; i < 2; i++)
					{
						std::cout << "Imie: BOT" << (i + 1) << std::endl;
						this->bot[i].ileKart();
						this->bot[i].pokazKarty();
						bot[i].jesliPrzegral();
					}
					if (bot[0].podajPunkty() > bot[1].podajPunkty() && bot[0].podajPunkty() > gracz[0].podajPunkty())
					{
						std::cout << "Wygral BOT1" << std::endl;
					}
					else if (bot[0].podajPunkty() == bot[1].podajPunkty() && bot[1].podajPunkty() == gracz[0].podajPunkty())
					{
						std::cout << "Wyglada na to ze mamy remis\n";
					}
					else if (bot[1].podajPunkty() > bot[0].podajPunkty() && bot[1].podajPunkty() > gracz[0].podajPunkty())
					{
						std::cout << "Wygral BOT2" << std::endl;
					}
					else if (gracz[0].podajPunkty() > bot[0].podajPunkty() && gracz[0].podajPunkty() > bot[1].podajPunkty())
					{
						std::cout << "Wygral  " << gracz[0].podajImie() << std::endl;
					}
					gra = this->jeszczeRaz(gra);
				}
			}
			if (liczbaBotow == 3)
			{
				if (gracz[0].sprawdzCzySpasowal() == 2 && bot[0].sprawdzCzySpasowal() == 2 && bot[1].sprawdzCzySpasowal() == 2 && bot[2].sprawdzCzySpasowal() == 2 || gracz[0].podajPunkty() > 21 || bot[0].podajPunkty() > 21 || bot[1].podajPunkty() > 21 || bot[2].podajPunkty() > 21)
				{
					wygrana = 1;
					std::cout << "Imie: " << gracz[0].podajImie() << std::endl;
					this->gracz[0].ileKart();
					this->gracz[0].pokazKarty();
					gracz[0].jesliPrzegral();
					for (int i = 0; i < 3; i++)
					{
						std::cout << "Imie: BOT" << (i + 1) << std::endl;
						this->bot[i].ileKart();
						this->bot[i].pokazKarty();
						bot[i].jesliPrzegral();
					}
					if (bot[0].podajPunkty() > bot[1].podajPunkty() && bot[0].podajPunkty() > gracz[0].podajPunkty() && bot[0].podajPunkty() > bot[2].podajPunkty())
					{
						std::cout << "Wygral BOT1" << std::endl;
					}
					else if (bot[0].podajPunkty() == bot[1].podajPunkty() && bot[1].podajPunkty() == gracz[0].podajPunkty() && bot[0].podajPunkty() == bot[2].podajPunkty())
					{
						std::cout << "Wyglada na to ze mamy remis\n";
					}
					else if (bot[1].podajPunkty() > bot[0].podajPunkty() && bot[1].podajPunkty() > gracz[0].podajPunkty() && bot[1].podajPunkty() > bot[2].podajPunkty())
					{
						std::cout << "Wygral BOT2" << std::endl;
					}
					else if (bot[2].podajPunkty() > bot[0].podajPunkty() && bot[2].podajPunkty() > gracz[0].podajPunkty() && bot[2].podajPunkty() > bot[1].podajPunkty())
					{
						std::cout << "Wygral BOT3" << std::endl;
					}
					else if (gracz[0].podajPunkty() > bot[0].podajPunkty() && gracz[0].podajPunkty() > bot[1].podajPunkty() && gracz[0].podajPunkty() > bot[2].podajPunkty())
					{
						std::cout << "Wygral  " << gracz[0].podajImie() << std::endl;
					}
					gra = this->jeszczeRaz(gra);
				}
			}
		}
		if (liczbaGraczy == 2)
		{
			if (liczbaBotow == 0)
			{
				if (gracz[0].sprawdzCzySpasowal() == 2 && gracz[1].sprawdzCzySpasowal() == 2 || gracz[0].podajPunkty() > 21 || gracz[1].podajPunkty() > 21)
				{
					wygrana = 1;
					for (int i = 0; i < 2; i++)
					{
						std::cout << "Imie: " << gracz[i].podajImie() << std::endl;
						this->gracz[i].ileKart();
						this->gracz[i].pokazKarty();
						gracz[i].jesliPrzegral();
					}
					if (gracz[0].podajPunkty() > gracz[1].podajPunkty())
					{
						std::cout << "Wygral " << gracz[0].podajImie() << std::endl;
					}
					else if (gracz[0].podajPunkty() == gracz[1].podajPunkty())
					{
						std::cout << "Wyglada na to ze mamy remis\n";
					}
					else
					{
						std::cout << "Wygral " << gracz[1].podajImie() << std::endl;
					}
					gra = this->jeszczeRaz(gra);
				}
			}
			if (liczbaBotow == 1)
			{
				if (gracz[0].sprawdzCzySpasowal() == 2 && bot[0].sprawdzCzySpasowal() == 2 && gracz[1].sprawdzCzySpasowal() == 2 || gracz[0].podajPunkty() > 21 || bot[0].podajPunkty() > 21 || gracz[1].podajPunkty() > 21)
				{
					wygrana = 1;
					std::cout << "Imie: BOT" << 1 << std::endl;
					this->bot[0].ileKart();
					this->bot[0].pokazKarty();
					bot[0].jesliPrzegral();
					for (int i = 0; i < 2; i++)
					{
						std::cout << "Imie: " << gracz[i].podajImie() << std::endl;
						this->gracz[i].ileKart();
						this->gracz[i].pokazKarty();
						gracz[i].jesliPrzegral();
					}
					if (bot[0].podajPunkty() > gracz[1].podajPunkty() && bot[0].podajPunkty() > gracz[0].podajPunkty())
					{
						std::cout << "Wygral BOT1" << std::endl;
					}
					else if (bot[0].podajPunkty() == gracz[1].podajPunkty() && gracz[1].podajPunkty() == gracz[0].podajPunkty())
					{
						std::cout << "Wyglada na to ze mamy remis\n";
					}
					else if (gracz[1].podajPunkty() > bot[0].podajPunkty() && gracz[1].podajPunkty() > gracz[0].podajPunkty())
					{
						std::cout << "Wygral  " << gracz[1].podajImie() << std::endl;
					}
					else if (gracz[0].podajPunkty() > bot[0].podajPunkty() && gracz[0].podajPunkty() > gracz[1].podajPunkty())
					{
						std::cout << "Wygral  " << gracz[0].podajImie() << std::endl;
					}
					gra = this->jeszczeRaz(gra);
				}
			}
			if (liczbaBotow == 2)
			{
				if (gracz[0].sprawdzCzySpasowal() == 2 && gracz[1].sprawdzCzySpasowal() == 2 && bot[1].sprawdzCzySpasowal() == 2 && bot[0].sprawdzCzySpasowal() == 2 || gracz[0].podajPunkty() > 21 || bot[0].podajPunkty() > 21 || bot[1].podajPunkty() > 21 || gracz[1].podajPunkty() > 21)
				{
					wygrana = 1;
					for (int i = 0; i < 2; i++)
					{
						std::cout << "Imie: " << gracz[i].podajImie() << std::endl;
						this->gracz[i].ileKart();
						this->gracz[i].pokazKarty();
						gracz[i].jesliPrzegral();
					}
					for (int i = 0; i < 2; i++)
					{
						std::cout << "Imie: BOT" << (i + 1) << std::endl;
						this->bot[i].ileKart();
						this->bot[i].pokazKarty();
						bot[i].jesliPrzegral();
					}
					if (bot[0].podajPunkty() > bot[1].podajPunkty() && bot[0].podajPunkty() > gracz[0].podajPunkty() && bot[0].podajPunkty() > gracz[1].podajPunkty())
					{
						std::cout << "Wygral BOT1" << std::endl;
					}
					else if (bot[0].podajPunkty() == bot[1].podajPunkty() && bot[1].podajPunkty() == gracz[0].podajPunkty() && bot[0].podajPunkty() == gracz[1].podajPunkty())
					{
						std::cout << "Wyglada na to ze mamy remis\n";
					}
					else if (bot[1].podajPunkty() > bot[0].podajPunkty() && bot[1].podajPunkty() > gracz[0].podajPunkty() && bot[1].podajPunkty() > gracz[1].podajPunkty())
					{
						std::cout << "Wygral BOT2" << std::endl;
					}
					else if (gracz[1].podajPunkty() > bot[0].podajPunkty() && gracz[1].podajPunkty() > gracz[0].podajPunkty() && gracz[1].podajPunkty() > bot[1].podajPunkty())
					{
						std::cout << "Wygral  " << gracz[1].podajImie() << std::endl;
					}
					else if (gracz[0].podajPunkty() > bot[0].podajPunkty() && gracz[0].podajPunkty() > bot[1].podajPunkty() && gracz[0].podajPunkty() > gracz[1].podajPunkty())
					{
						std::cout << "Wygral  " << gracz[0].podajImie() << std::endl;
					}
					gra = this->jeszczeRaz(gra);
				}
			}
			if (liczbaBotow == 3)
			{
				if (gracz[0].sprawdzCzySpasowal() == 2 && gracz[1].sprawdzCzySpasowal() == 2 && bot[0].sprawdzCzySpasowal() == 2 && bot[1].sprawdzCzySpasowal() == 2 && bot[2].sprawdzCzySpasowal() == 2 || gracz[0].podajPunkty() > 21 || gracz[1].podajPunkty() > 21 || bot[0].podajPunkty() > 21 || bot[1].podajPunkty() > 21 || bot[2].podajPunkty() > 21)
				{
					wygrana = 1;
					for (int i = 0; i < 2; i++)
					{
						std::cout << "Imie: " << gracz[i].podajImie() << std::endl;
						this->gracz[i].ileKart();
						this->gracz[i].pokazKarty();
						gracz[i].jesliPrzegral();
					}
					for (int i = 0; i < 3; i++)
					{
						std::cout << "Imie: BOT" << (i + 1) << std::endl;
						this->bot[i].ileKart();
						this->bot[i].pokazKarty();
						bot[i].jesliPrzegral();
					}
					if (bot[0].podajPunkty() > bot[1].podajPunkty() && bot[0].podajPunkty() > gracz[0].podajPunkty() && bot[0].podajPunkty() > gracz[1].podajPunkty() && bot[0].podajPunkty() > bot[2].podajPunkty())
					{
						std::cout << "Wygral BOT1" << std::endl;
					}
					else if (bot[0].podajPunkty() == bot[1].podajPunkty() && bot[1].podajPunkty() == gracz[0].podajPunkty() && bot[0].podajPunkty() == gracz[1].podajPunkty() && bot[0].podajPunkty() == bot[2].podajPunkty())
					{
						std::cout << "Wyglada na to ze mamy remis\n";
					}
					else if (bot[1].podajPunkty() > bot[0].podajPunkty() && bot[1].podajPunkty() > gracz[0].podajPunkty() && bot[1].podajPunkty() > gracz[1].podajPunkty() && bot[1].podajPunkty() > bot[2].podajPunkty())
					{
						std::cout << "Wygral BOT2" << std::endl;
					}
					else if (bot[2].podajPunkty() > bot[0].podajPunkty() && bot[2].podajPunkty() > gracz[0].podajPunkty() && bot[2].podajPunkty() > gracz[1].podajPunkty() && bot[2].podajPunkty() > bot[1].podajPunkty())
					{
						std::cout << "Wygral BOT3" << std::endl;
					}
					else if (gracz[1].podajPunkty() > bot[0].podajPunkty() && gracz[1].podajPunkty() > gracz[0].podajPunkty() && gracz[1].podajPunkty() > bot[1].podajPunkty() && gracz[1].podajPunkty() > bot[2].podajPunkty())
					{
						std::cout << "Wygral  " << gracz[1].podajImie() << std::endl;
					}
					else if (gracz[0].podajPunkty() > bot[0].podajPunkty() && gracz[0].podajPunkty() > bot[1].podajPunkty() && gracz[0].podajPunkty() > gracz[1].podajPunkty() && gracz[0].podajPunkty() > bot[2].podajPunkty())
					{
						std::cout << "Wygral  " << gracz[0].podajImie() << std::endl;
					}
					gra = this->jeszczeRaz(gra);
				}
			}
		}
		if (liczbaGraczy == 3)
		{
			if (liczbaBotow == 0)
			{
				if (gracz[0].sprawdzCzySpasowal() == 2 && gracz[1].sprawdzCzySpasowal() == 2 && gracz[2].sprawdzCzySpasowal() == 2 || gracz[0].podajPunkty() > 21 || gracz[1].podajPunkty() > 21 || gracz[2].podajPunkty() > 21)
				{
					wygrana = 1;
					for (int i = 0; i < 3; i++)
					{
						std::cout << "Imie: " << gracz[i].podajImie() << std::endl;
						this->gracz[i].ileKart();
						this->gracz[i].pokazKarty();
						gracz[i].jesliPrzegral();
					}
					if (gracz[0].podajPunkty() > gracz[1].podajPunkty() && gracz[0].podajPunkty() > gracz[2].podajPunkty())
					{
						std::cout << "Wygral " << gracz[0].podajImie() << std::endl;
					}
					if (gracz[2].podajPunkty() > gracz[1].podajPunkty() && gracz[2].podajPunkty() > gracz[0].podajPunkty())
					{
						std::cout << "Wygral " << gracz[2].podajImie() << std::endl;
					}
					if (gracz[1].podajPunkty() > gracz[2].podajPunkty() && gracz[1].podajPunkty() > gracz[0].podajPunkty())
					{
						std::cout << "Wygral " << gracz[1].podajImie() << std::endl;
					}
					else if (gracz[0].podajPunkty() == gracz[1].podajPunkty() || gracz[0].podajPunkty() == gracz[2].podajPunkty() || gracz[1].podajPunkty() == gracz[2].podajPunkty())
					{
						std::cout << "Wyglada na to ze mamy remis\n";
					}
					gra = this->jeszczeRaz(gra);
				}
			}
			if (liczbaBotow == 1)
			{
				if (gracz[0].sprawdzCzySpasowal() == 2 && gracz[1].sprawdzCzySpasowal() == 2 && gracz[2].sprawdzCzySpasowal() == 2 && bot[0].sprawdzCzySpasowal() == 2 || gracz[0].podajPunkty() > 21 || gracz[1].podajPunkty() > 21 || gracz[2].podajPunkty() > 21 || bot[0].podajPunkty() > 21)
				{
					wygrana = 1;
					for (int i = 0; i < 3; i++)
					{
						std::cout << "Imie: " << gracz[i].podajImie() << std::endl;
						this->gracz[i].ileKart();
						this->gracz[i].pokazKarty();
						gracz[i].jesliPrzegral();
					}
					std::cout << "Imie: BOT" << 1 << std::endl;
					this->bot[0].ileKart();
					this->bot[0].pokazKarty();
					bot[0].jesliPrzegral();
					if (bot[0].podajPunkty() > gracz[0].podajPunkty() && bot[0].podajPunkty() > gracz[1].podajPunkty() && bot[0].podajPunkty() > gracz[2].podajPunkty())
					{
						std::cout << "Wygral BOT1" << std::endl;
					}
					else if (bot[0].podajPunkty() == gracz[0].podajPunkty() && bot[0].podajPunkty() == gracz[1].podajPunkty() && bot[0].podajPunkty() == gracz[2].podajPunkty())
					{
						std::cout << "Wyglada na to ze mamy remis\n";
					}
					else if (gracz[0].podajPunkty() > bot[0].podajPunkty() && gracz[0].podajPunkty() > gracz[1].podajPunkty() && gracz[0].podajPunkty() > gracz[2].podajPunkty())
					{
						std::cout << "Wygral  " << gracz[0].podajImie() << std::endl;
					}
					else if (gracz[1].podajPunkty() > bot[0].podajPunkty() && gracz[1].podajPunkty() > gracz[0].podajPunkty() && gracz[1].podajPunkty() > gracz[2].podajPunkty())
					{
						std::cout << "Wygral  " << gracz[1].podajImie() << std::endl;
					}
					else if (gracz[2].podajPunkty() > bot[0].podajPunkty() && gracz[2].podajPunkty() > gracz[1].podajPunkty() && gracz[2].podajPunkty() > gracz[0].podajPunkty())
					{
						std::cout << "Wygral  " << gracz[2].podajImie() << std::endl;
					}
					gra = this->jeszczeRaz(gra);
				}
			}
			if (liczbaBotow == 2)
			{
				if (gracz[0].sprawdzCzySpasowal() == 2 && gracz[1].sprawdzCzySpasowal() == 2 && gracz[2].sprawdzCzySpasowal() == 2 && bot[0].sprawdzCzySpasowal() == 2 && bot[1].sprawdzCzySpasowal() == 2 || gracz[0].podajPunkty() > 21 || gracz[1].podajPunkty() > 21 || gracz[2].podajPunkty() > 21 || bot[1].podajPunkty() > 21 || bot[0].podajPunkty() > 21)
				{
					wygrana = 1;
					for (int i = 0; i < 3; i++)
					{
						std::cout << "Imie: " << gracz[i].podajImie() << std::endl;
						this->gracz[i].ileKart();
						this->gracz[i].pokazKarty();
						gracz[i].jesliPrzegral();
					}
					for (int i = 0; i < 2; i++)
					{
						std::cout << "Imie: BOT" << (i + 1) << std::endl;
						this->bot[i].ileKart();
						this->bot[i].pokazKarty();
						bot[i].jesliPrzegral();
					}
					if (bot[0].podajPunkty() > bot[1].podajPunkty() && bot[0].podajPunkty() > gracz[0].podajPunkty() && bot[0].podajPunkty() > gracz[1].podajPunkty() && bot[0].podajPunkty() > gracz[2].podajPunkty())
					{
						std::cout << "Wygral BOT1" << std::endl;
					}
					else if (bot[0].podajPunkty() == bot[1].podajPunkty() && bot[0].podajPunkty() == gracz[0].podajPunkty() && bot[0].podajPunkty() == gracz[1].podajPunkty() && bot[0].podajPunkty() == gracz[2].podajPunkty())
					{
						std::cout << "Wyglada na to ze mamy remis\n";
					}
					else if (bot[1].podajPunkty() > bot[0].podajPunkty() && bot[1].podajPunkty() > gracz[0].podajPunkty() && bot[1].podajPunkty() > gracz[1].podajPunkty() && bot[1].podajPunkty() > gracz[2].podajPunkty())
					{
						std::cout << "Wygral BOT2" << std::endl;
					}
					else if (gracz[2].podajPunkty() > bot[0].podajPunkty() && gracz[2].podajPunkty() > bot[1].podajPunkty() && gracz[2].podajPunkty() > gracz[1].podajPunkty() && gracz[2].podajPunkty() > gracz[0].podajPunkty())
					{
						std::cout << "Wygral  " << gracz[2].podajImie() << std::endl;
					}
					else if (gracz[1].podajPunkty() > bot[0].podajPunkty() && gracz[1].podajPunkty() > gracz[0].podajPunkty() && gracz[1].podajPunkty() > bot[1].podajPunkty() && gracz[1].podajPunkty() > gracz[2].podajPunkty())
					{
						std::cout << "Wygral  " << gracz[1].podajImie() << std::endl;
					}
					else if (gracz[0].podajPunkty() > bot[0].podajPunkty() && gracz[0].podajPunkty() > bot[1].podajPunkty() && gracz[0].podajPunkty() > gracz[1].podajPunkty() && gracz[0].podajPunkty() > gracz[2].podajPunkty())
					{
						std::cout << "Wygral  " << gracz[0].podajImie() << std::endl;
					}
					gra = this->jeszczeRaz(gra);
				}

			}
			if (liczbaBotow == 3)
			{
				if (gracz[0].sprawdzCzySpasowal() == 2 && gracz[1].sprawdzCzySpasowal() == 2 && gracz[2].sprawdzCzySpasowal() == 2 && bot[0].sprawdzCzySpasowal() == 2 && bot[1].sprawdzCzySpasowal() == 2 && bot[2].sprawdzCzySpasowal() == 2 || gracz[0].podajPunkty() > 21 || gracz[1].podajPunkty() > 21 || gracz[2].podajPunkty() > 21 || bot[0].podajPunkty() > 21 || bot[1].podajPunkty() > 21 || bot[2].podajPunkty() > 21)
				{
					wygrana = 1;
					for (int i = 0; i < 3; i++)
					{
						std::cout << "Imie: " << gracz[i].podajImie() << std::endl;
						this->gracz[i].ileKart();
						this->gracz[i].pokazKarty();
						gracz[i].jesliPrzegral();
					}
					for (int i = 0; i < 3; i++)
					{
						std::cout << "Imie: BOT" << (i+1)  << std::endl;
						this->bot[i].ileKart();
						this->bot[i].pokazKarty();
						bot[i].jesliPrzegral();
					}
					if (bot[0].podajPunkty() > bot[1].podajPunkty() && bot[0].podajPunkty() > gracz[0].podajPunkty() && bot[0].podajPunkty() > gracz[1].podajPunkty() && bot[0].podajPunkty() > gracz[2].podajPunkty() && bot[0].podajPunkty() > bot[2].podajPunkty())
					{
						std::cout << "Wygral BOT1" << std::endl;
					}
					else if (bot[0].podajPunkty() == bot[1].podajPunkty() && bot[0].podajPunkty() == gracz[0].podajPunkty() && bot[0].podajPunkty() == gracz[1].podajPunkty() && bot[0].podajPunkty() == gracz[2].podajPunkty() && bot[0].podajPunkty() == bot[2].podajPunkty())
					{
						std::cout << "Wyglada na to ze mamy remis\n";
					}
					else if (bot[1].podajPunkty() > bot[0].podajPunkty() && bot[1].podajPunkty() > gracz[0].podajPunkty() && bot[1].podajPunkty() > gracz[1].podajPunkty() && bot[1].podajPunkty() > gracz[2].podajPunkty() && bot[1].podajPunkty() > bot[2].podajPunkty())
					{
						std::cout << "Wygral BOT2" << std::endl;
					}
					else if (bot[2].podajPunkty() > bot[0].podajPunkty() && bot[2].podajPunkty() > gracz[0].podajPunkty() && bot[2].podajPunkty() > gracz[1].podajPunkty() && bot[2].podajPunkty() > gracz[2].podajPunkty() && bot[2].podajPunkty() > bot[1].podajPunkty())
					{
						std::cout << "Wygral BOT3" << std::endl;
					}
					else if (gracz[2].podajPunkty() > bot[0].podajPunkty() && gracz[2].podajPunkty() > bot[1].podajPunkty() && gracz[2].podajPunkty() > bot[2].podajPunkty() && gracz[2].podajPunkty() > gracz[1].podajPunkty() && gracz[2].podajPunkty() > gracz[0].podajPunkty())
					{
						std::cout << "Wygral  " << gracz[2].podajImie() << std::endl;
					}
					else if (gracz[1].podajPunkty() > bot[0].podajPunkty() && gracz[1].podajPunkty() > bot[1].podajPunkty() && gracz[1].podajPunkty() > bot[2].podajPunkty() && gracz[1].podajPunkty() > gracz[0].podajPunkty() && gracz[1].podajPunkty() > gracz[2].podajPunkty())
					{
						std::cout << "Wygral  " << gracz[1].podajImie() << std::endl;
					}
					else if (gracz[0].podajPunkty() > bot[0].podajPunkty() && gracz[0].podajPunkty() > bot[1].podajPunkty() && gracz[0].podajPunkty() > bot[2].podajPunkty() && gracz[0].podajPunkty() > gracz[1].podajPunkty() && gracz[0].podajPunkty() > gracz[2].podajPunkty())
					{
						std::cout << "Wygral  " << gracz[0].podajImie() << std::endl;
					}
					gra = this->jeszczeRaz(gra);
				}
			}
		}
	}
	this->zapiszGre();
	return gra;
}

int Kasyno::jeszczeRaz(int gra)
{
	std::cout << "\nCzy chcesz zagrac jeszcze raz?\n1.Tak\n2.Nie\n";
	while (1)
	{
		std::cin >> gra;
		if (std::cin.fail())
		{
			std::cout << "Wykryto blad. Podaj wartosc ponownie " << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			if (gra > 0 && gra < 3)
				break;
		}
	}
	if (gra == 1)
	{
		return 1;
	}
	else if (gra == 2)
	{
		return 0;
	}
}

Kasyno::~Kasyno()
{
	delete[] kartaKasyna;
}

void Kasyno::potasuj()
{
	Karta temp(0, 0);
	losowosc = 100 + rand() % 50;
	for (int i = 0; i < losowosc ; i++)
	{
		int x = rand() % 52;
		int y = rand() % 52;
		if (x != y)
		{
			temp = kartaKasyna[x];
			kartaKasyna[x] = kartaKasyna[y];
			kartaKasyna[y] = temp;
		}
	}
	for (int i = 0; i < 52; i++)
	{
		kartaKasyna[i].wypisz();
	}
}
Karta *Kasyno::dajKarte()
{
	int zlicz = liczbaKart;
	zlicz--;
	Karta *taliaTemp = new Karta[zlicz];
	for (int i = 0; i < zlicz; i++)
	{
		taliaTemp[i] = this->kartaKasyna[i];
	}
	liczbaKart = zlicz;
	this->kartaKasyna = taliaTemp;
	std::cout << std::endl;
	return this->kartaKasyna;
}

void Kasyno::zapiszGre()
{
	int p = 0;
	int b = 0;
	std::ofstream plik;
	plik.open("WynikGry.txt", std::ofstream::out);
	plik << "Nazwa";
	plik.width(40);
	plik << "Karty";
	plik.width(40);
	plik << "Punkty" << std::endl;
	for (int i = 0; i < liczbaGraczy; i++)
	{
		p = gracz[i].zliczDlugoscImienia();
		plik << gracz[i].podajImie();
		plik.width(40-p);
		plik.fill(' ');
		for (int j = 0; j < gracz[i].ileKartGracza(); j++)
		{
			plik << gracz[i].zapiszKarty(plik, j);
		}
		b = (gracz[i].ileKartGracza()*2) + (2 * (gracz[i].ileKartGracza() -1));
		plik.width(40-b);
		plik << gracz[i].podajPunkty();
		plik << "\n";
	}
	for (int i = 0; i < liczbaBotow; i++)
	{
		p = 4;
		plik << "BOT";
		plik << (i+1);
		plik.width(40 - p);
		plik.fill(' ');
		for (int j = 0; j < bot[i].ileKartGracza(); j++)
		{
			plik << bot[i].zapiszKarty(plik, j);
		}
		b = (bot[i].ileKartGracza() * 2) + (2 * (bot[i].ileKartGracza()) -1);
		plik.width(40 - b);
		plik << bot[i].podajPunkty();
		plik << "\n";
	}
	plik.close();
}

void Kasyno::pokazTalie()
{
	std::cout << liczbaKart;
	std::cout << std::endl;
	for (int i = 0; i < liczbaKart; i++)
	{
		kartaKasyna[i].wypisz();
	}
	std::cout << std::endl;
}

