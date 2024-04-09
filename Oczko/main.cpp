#include <iostream>
#include "Kasyno.h"
#include "Gracz.h"
#include "Karta.h"

int main()
{
	srand(time(NULL));
	int nowaGra = 1;
	while (nowaGra == 1)
	{
		Kasyno k;
		nowaGra = k.graj();
		system("cls");
		if (nowaGra != 1)
		{
			std::cout << "Do widzenia" << std::endl;
		}
	}
}
/*NOTATKI
Jakub Oleksy 261347
*/