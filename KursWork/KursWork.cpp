#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <math.h>
#include <stdarg.h>
#include <cstdlib>
#include <string>
#include <string.h>
#include <list>
#include <iterator>
#include <array>
#include <vector>

using namespace std;

typedef unsigned short us;
typedef unsigned long long ull;

enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

struct YourTank
{
	int x = 0;
	int y = 0;
	int dmg = 1;
	int your_hp = 3;
	string your_tank = string("@");

};
struct EnemyTanks
{
	int x;
	int y;
	int dmg = 1;
	string enemy_tank = string("*");
	int enemy_hp;
};


class Map
{
private:
	vector <vector <string>> map;
public:
	void Set_map(int size)
	{

		for (int i(0); i < size; i++)
		{
			vector <string> vec;
			for (int j(0); j < size; j++)
			{
				int temp;
				temp = rand() % 6;
				if (temp == 2)
				{
					vec.push_back("#");
				}
				else vec.push_back("-");
			}
			map.push_back(vec);
		}
	}
	void print_map()
	{
		HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
		WORD m_currentConsoleAttr;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (GetConsoleScreenBufferInfo(hwnd, &csbi))
		{
			m_currentConsoleAttr = csbi.wAttributes;
		}

		for (int i(0); i < map.size(); i++)
		{
			for (int j(0); j < map.size(); j++)
			{
				if (map[i][j] == string("@"))
				{
					SetConsoleTextAttribute(hwnd, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				}
				else if (map[i][j] == string("*"))
				{
					SetConsoleTextAttribute(hwnd, FOREGROUND_RED | FOREGROUND_INTENSITY);
				}
				else if (map[i][j] == string("#"))
				{
					SetConsoleTextAttribute(hwnd, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				}
				cout << map[i][j] << setw(2);
				SetConsoleTextAttribute(hwnd, m_currentConsoleAttr);
			}
			cout << endl;

		}
	}
	string Get_map_element(int i, int j)
	{
		return map[i][j];
	}
	vector <vector <string>> Get_maper()
	{
		return map;
	}
	string Get_NULL_element()
	{
		return map[0][0];
	}
	void Set_element(string str, int i, int j)
	{
		map[i][j] = str;
	}
};


class Game
{
private:

	int dmg;

	Map map;
	int tanks;
	const int size = 25;
	int lvl;

	YourTank A;
	EnemyTanks B;

	void GoToXY(int column, int line)
	{

		COORD coord;
		coord.X = column;
		coord.Y = line;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (!SetConsoleCursorPosition(hConsole, coord))
		{

		}
	}

	bool End_game()
	{
		if (tanks <= 0)
		{
			system("cls");
			cout << "\t\tWin" << endl;
			return true;
		}
		else if (A.your_hp <= 0)
		{
			system("csl");
			cout << "\t\tGG" << endl;
			return false;
		}
		return false;
	}
public:
	Game()
	{

	}
	void Spawn_your_tank()
	{
		map.Set_element(A.your_tank, 0, 0);
	}
	void Move()
	{

		while (End_game() != true)
		{
			char q = _getch();
			system("cls");
			switch (q)
			{
			case 75:
			{
				GoToXY(A.x, A.y);

			}break;
			case 77:
			{
				GoToXY(A.x, A.y);

			}break;
			case 72:
			{
				GoToXY(A.x, A.y);

			}break;
			case 80:
			{
				GoToXY(A.x, A.y);

			}break;
			}

		}
	}
	void Spawn_enemy_tanks()
	{
		srand(static_cast<unsigned int>(time(NULL)));
		int temp_x;
		int temp_y;
		int temp_move;
		switch (lvl)
		{
		case 1:
		{
			for (us i(0); i < tanks; i++)
			{
				temp_x = rand() % 10 + 1;
				temp_y = rand() % 10 + 1;
				if (map.Get_map_element(temp_x, temp_y) == string("*"))
				{
					--i;
				}
				map.Set_element(B.enemy_tank, temp_x, temp_y);
			}

		}break;
		case 2:
		{
			for (us i(0); i < tanks; i++)
			{
				temp_x = rand() % 10 + 1;
				temp_y = rand() % 10 + 1;
				if (map.Get_map_element(temp_x, temp_y) == B.enemy_tank)
				{
					--i;
				}
				map.Set_element(B.enemy_tank, temp_x, temp_y);
			}

		}break;
		case 3:
		{
			for (us i(0); i < tanks; i++)
			{
				temp_x = rand() % 10 + 1;
				temp_y = rand() % 10 + 1;
				if (map.Get_map_element(temp_x, temp_y) == B.enemy_tank)
				{
					--i;
				}
				map.Set_element(B.enemy_tank, temp_x, temp_y);
			}

		}break;
		case 4:
		{
			for (us i(0); i < tanks; i++)
			{
				temp_x = rand() % 10 + 1;
				temp_y = rand() % 10 + 1;
				if (map.Get_map_element(temp_x, temp_y) == B.enemy_tank)
				{
					--i;
				}
				map.Set_element(B.enemy_tank, temp_x, temp_y);
			}

		}break;
		}
	}
	void Set_lvl(int lvl)
	{
		srand(static_cast<unsigned int>(time(NULL)));
		int temp_x;
		int temp_y;
		int temp_move;
		this->lvl = lvl;
		switch (lvl)
		{
		case 1:
		{
			tanks = 2;
			B.enemy_hp = 2;

		}break;
		case 2:
		{
			B.enemy_hp = 5;
			tanks = 3;
		

		}break;
		case 3:
		{
			B.enemy_hp = 7;
			tanks = 4;

		}break;
		case 4:
		{
			B.enemy_hp = 10;
			tanks = 5;

		}break;
		}
	}
};




int main()
{


	srand(static_cast<unsigned int>(time(NULL)));
	setlocale(LC_ALL, "rus");
	system("mode con cols=53 lines=25");
	Game G;
	Map M;
	int lvl;
	const int size = 2;
Restart:
	cout << "\t\t Its tanks from Dendy to Pc " << endl;
	cout << "Enter lvl of hard: " << endl;
	cout << "Enter 1 to chose ez lvl" << endl;
	cout << "Enter 2 to chose midl lvl " << endl;
	cout << "Enter 3 to  hard lvl " << endl;
	cout << "Enter 4 to chose very hard lvl" << endl;
	cin >> lvl;
	if (lvl >= 1 && lvl <= 4)
	{
		(lvl);
	}
	else
	{
		cout << "Eror input " << endl;
		goto Restart;
	}
	G.Set_lvl(lvl);
	M.Set_map(size);
	G.Spawn_your_tank();
	G.Spawn_enemy_tanks();
	M.print_map();
	G.Move();




	_gettch();
	return 0;

}