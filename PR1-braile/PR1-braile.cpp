#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>


//pare globalnych sie przyda dla klienta:
const char znakPusty = ' ', znakPelny = '•';

/////////////////////////////////////////////////////////////////////////////////////////////////////
//funcja zmienia znaki lacinskie na znaki w alfabecie braille i wpisuje je do pliku
void TranslacjaIWpisanieDoPliku(int &x,int &y,char linijkaAlfabetLacinski[], char linijkaBraille[][120], std::ofstream& plikWyjsciowy) 
{
	std::string kodBraille = "";

	for (int j = 0; linijkaAlfabetLacinski[j] != 0; j++)
	{
		//																		  *			0 1
		//sprawdzam jaki znak i zamieniam go na kod znaku braille np.: 'w'	=	* *		=	1 1	=	011101
		//																		  *			0 1
		switch (tolower(linijkaAlfabetLacinski[j]))
		{
		case ' ': kodBraille = "000000"; break;
		case '	':kodBraille = "000000"; break;

		case 'a': kodBraille = "100000"; break;
		case 'b': kodBraille = "101000"; break;
		case 'c': kodBraille = "110000"; break;
		case 'd': kodBraille = "110100"; break;
		case 'e': kodBraille = "100100"; break;
		case 'f': kodBraille = "111000"; break;
		case 'g': kodBraille = "111100"; break;
		case 'h': kodBraille = "101100"; break;
		case 'i': kodBraille = "011000"; break;
		case 'j': kodBraille = "011100"; break;
		case 'k': kodBraille = "100010"; break;
		case 'l': kodBraille = "101010"; break;
		case 'm': kodBraille = "110010"; break;
		case 'n': kodBraille = "110110"; break;
		case 'o': kodBraille = "100110"; break;
		case 'p': kodBraille = "111010"; break;
		case 'r': kodBraille = "101110"; break;
		case 's': kodBraille = "011010"; break;
		case 't': kodBraille = "011110"; break;
		case 'u': kodBraille = "100011"; break;
		case 'v': kodBraille = "101011"; break;
		case 'w': kodBraille = "011101"; break;
		case 'x': kodBraille = "110011"; break;
		case 'y': kodBraille = "110111"; break;
		case 'z': kodBraille = "100111"; break;

		case '!': kodBraille = "001110"; break;
		case '?': kodBraille = "001001"; break;
		
		case '.': kodBraille = "001101"; break;
		case ',': kodBraille = "001000"; break;
		case ';': kodBraille = "001010"; break;
		case '\"':kodBraille = "000111"; break;
		case ':': kodBraille = "001100"; break;
		case '*': kodBraille = "000110"; break;
		
		//nieznany znak:
		default: kodBraille = "111111"; break;
		}

		//wpisuje znak w braille do tablicy korzystajac z podanych znakow
		linijkaBraille[x][y] = kodBraille[0] == '0' ? znakPusty : znakPelny;
		y++;
		linijkaBraille[x][y] = kodBraille[1] == '0' ? znakPusty : znakPelny;
		x++; y--;
		linijkaBraille[x][y] = kodBraille[2] == '0' ? znakPusty : znakPelny;
		y++;
		linijkaBraille[x][y] = kodBraille[3] == '0' ? znakPusty : znakPelny;
		x++; y--;
		linijkaBraille[x][y] = kodBraille[4] == '0' ? znakPusty : znakPelny;
		y++;
		linijkaBraille[x][y] = kodBraille[5] == '0' ? znakPusty : znakPelny;

		//spacja nie wymaga dodatkowego oddzielenia od kolejnego znaku
		if (kodBraille != "000000")
		{
			linijkaBraille[x][++y] = znakPusty;
			linijkaBraille[--x][y] = znakPusty;
			linijkaBraille[--x][y] = znakPusty;

			y++;
		}
		else {
			x -= 2;
			y++;
		}
	}

	//przepisanie tablicy przechowujacej znaki braille do pliku wyjsciowego
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; linijkaBraille[j][i]; i++)
		{
			plikWyjsciowy << linijkaBraille[j][i];
			linijkaBraille[j][i] = 0;
		}
		plikWyjsciowy << std::endl;
	}
	plikWyjsciowy << std::endl;

	x = y = 0;
}

int main(int argc, char **argv)
{
/////////////////////////////////////////////////////////////////////////////////////////////////////
	//wczytywanie i interpretowanie argumentow (przelaczniki)

	std::string plikWejsciowyNazwa = "", plikWyjsciowyNazwa = "";

	if (argc != 1) {
		for (int i = 1; i < argc; i++) {
			if (argv[i][0] == '-')
				if (argv[i][1] == 'i' && argv[i][2] == 0)
				{
					i++;
					for (int j = 0; argv[i][j] != 0; j++)
						plikWejsciowyNazwa += argv[i][j];
				}
				else if (argv[i][1] == 'o' && argv[i][2] == 0)
				{
					i++;
					for (int j = 0; argv[i][j] != 0; j++)
						plikWyjsciowyNazwa += argv[i][j];
				}
				else {
					std::cout << "Unknown switch. Type \"[program name] help\" to get more info" << std::endl;
					return 0;
				}
			else if (i == 1 && argv[i][0] == 'h')
				{
				if (argv[1][1] == 'e' && argv[1][2] == 'l' && argv[1][3] == 'p')
					{
						std::cout << "help yourself" << std::endl;
						return 0;
					}
				}
			else {
				std::cout << "Unknown switch. Type \"[program name] help\" to get more info" << std::endl;
				return 0;
			}
		}
	}
	else
	{
		std::cout << "Program zostal zle wywolany. Poprawne wywolanie: " << std::endl;
		std::cout << "program -i [input_name.txt] -o [output_name.txt]";
		return 0;
	}
	plikWejsciowyNazwa += ".txt";
	plikWyjsciowyNazwa += ".txt";

////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//otwieram i testuje pliki
	
	std::ifstream plikWejsciowy(plikWejsciowyNazwa);
	if (!plikWejsciowy)
	{
		std::cout << "Plik \"" << plikWejsciowyNazwa << "\" nie istnieje!\nSprawdz podana nazwe oraz czy plik znajduje sie w folderze glownym programu.\n";
		return 0;
	}
	
	//ofstream w razie nieistnienia pliku stworzy nowy o tej samej nazwie, wiec zeby sprawdzic, musze uzyc ifstream
	std::ifstream sprawdzCzyIstnieje(plikWyjsciowyNazwa);
	if (!sprawdzCzyIstnieje)
	{
		int chcesz_nowy = 2;

		std::cout << "Plik \"" << plikWyjsciowyNazwa << "\" nie istnieje"<<std::endl;
		while (chcesz_nowy != 0 && chcesz_nowy != 1)
		{
			std::cout<<"Czy mam stworzyc nowy? [0/1]" << std::endl; 
			std::cin >> chcesz_nowy;
		}
		if (chcesz_nowy == 0) 
			return 0;
	}
	sprawdzCzyIstnieje.close();

	std::ofstream plikWyjsciowy;
	plikWyjsciowy.open(plikWyjsciowyNazwa);

	if (!plikWyjsciowy.is_open())
	{
		std::cout << "nieakceptowalna nazwa pliku wyjsciowego\nWynik zostanie zapisany do \"plik_wyjsciowy.txt\"" << std::endl;
		plikWyjsciowy.open("plik_wyjsciowy.txt");
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//wczytuje tekst z pliku i dziele na ciagi maks 30 znakow

	std::string liniaZPliku = "";
	int x = 0, y = 0; //wspolrzedne generatora znakow braille
	char maks30znakow[31] = { 0 };
	char linijkaBraille[3][120];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 120; j++)
			linijkaBraille[i][j] = 0;
		

	while (getline(plikWejsciowy, liniaZPliku))
	{
		for (int i = 0, j = 0; i < liniaZPliku.size(); i++, j++)
			if (!(liniaZPliku[i] == ' ' && j == 0)) //usuwam ewentualna spacje z poczatku nowej linii
			{
				maks30znakow[j] = liniaZPliku[i];
				if (j == 29) //jesli tablica ma 30 (podane max) znakow, to przepisz to pliku, a reszte sprobuje wpisac do nowej linijki
				{
					TranslacjaIWpisanieDoPliku(x, y, maks30znakow, linijkaBraille, plikWyjsciowy);
					j = -1;
					for (int k = 0; k < 30; k++) maks30znakow[k] = 0; 
				}
			}
		if (maks30znakow[0]) //jesli cos zostalo jeszcze nieprzepisane 
		{
			TranslacjaIWpisanieDoPliku(x, y, maks30znakow, linijkaBraille, plikWyjsciowy);
			for (int k = 0; k < 30; k++) maks30znakow[k] = 0;
		}
		plikWyjsciowy << std::endl;
	}

	plikWejsciowy.close();
	plikWyjsciowy.close();
	
    return 0;
}