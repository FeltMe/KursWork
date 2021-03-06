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
	string bullet = string(".");

};
struct EnemyTanks
{
	int enemy_hp;
	int x;
	int y;
	int dmg = 1;
	string enemy_tank = string("*");
	string bullet = string(",");

};


#define Last_move_left 1
#define Last_move_right 2
#define Last_move_up 3
#define Last_move_down 4
#define size_map 25

class Interfese_to_map
{
private:
	vector<vector<string>> temp;
public:
	virtual void Set_map() = 0;
	virtual void print_map() = 0;
	virtual string Get_map_element(int i, int j) = 0;
	virtual vector < vector <string>> Get_maper() = 0;
	virtual string Get_NULL_element() = 0;
	virtual void Set_element(string str, int i, int j) = 0;
	virtual void Wash_element(int i, int j) = 0;
};

class Map : Interfese_to_map

{
private:
	vector <vector <string>> map;
public:
	void Set_map()
	{

		for (int i(0); i < size_map; i++)
		{
			vector <string> vec;
			for (int j(0); j < size_map; j++)
			{
				int temp;
				temp = rand() % 9;
				if (i == 0 || i == size_map - 1)
				{
					vec.push_back("#");
				}
				else if (j == 0 || j == size_map - 1)
				{
					vec.push_back("#");
				}
				else if (temp == 2)
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
				cout << map[i][j] << setw(1);
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
	void Wash_element(int i, int j)
	{
		map[i][j] = string("-");
	}
};


class Game
{
private:
	string Washed_element = "-";
	int dmg;
	Map map;
	int tanks = 1;
	int lvl;
	YourTank A;
	EnemyTanks B;

	void GoToXY(int column, int line)
	{
		COORD coord;
		coord.X = column;
		coord.Y = line;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, coord);
		if (coord.X == size_map - 1)
		{
			--coord.X;
		}
		else if (coord.X == 0)
		{
			++coord.X;
		}
		else if (coord.Y == size_map - 1)
		{
			++coord.Y;
		}
		else if (coord.Y == 0)
		{
			--coord.Y;
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
	static Game& GetInstance()
	{
		static Game app;
		return app;
	}
	void StartGame()
	{
		int lvl;

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
			Set_lvl(lvl);
		}
		else
		{
			cout << "Eror input " << endl;
			goto Restart;
		}
		system("cls");
		Set_lvl(lvl);
		map.Set_map();
		Spawn_your_tank();
		Spawn_enemy_tank();
		map.print_map();
		Move();
	}
	void Spawn_your_tank()
	{
		A.x = 12;
		A.y = 13;
		map.Set_element(A.your_tank, A.x, A.y);
	}
	void Move()
	{

		while (End_game() != true)
		{

			int Last_move;
			char Getch = _getch();
			switch (Getch)
			{
			case 75: // Left
			{
				if (A.x == 1)
				{
					break;
				}
				else
				{
					int temp = A.x - 1;
					if (map.Get_map_element(temp, A.y) == string("#"))
					{
						break;
					}
					cout << Washed_element;
					map.Wash_element(A.x, A.y);
					GoToXY(--A.x, A.y);
					map.Set_element(A.your_tank, A.x, A.y);
					cout << A.your_tank;
					Last_move = Last_move_left;
				}
			}break;
			case 77: // Right
			{
				if (A.x == size_map - 1)
				{
					break;
				}
				else
				{
					int temp = A.x + 1;
					if (map.Get_map_element(temp, A.y) == string("#"))
					{
						break;
					}
					map.Wash_element(A.x, A.y);
					GoToXY(++A.x, A.y);
					cout << Washed_element;
					map.Set_element(A.your_tank, A.x, A.y);
					cout << A.your_tank;
					Last_move = Last_move_right;
				}
			}break;
			case 72: // Up
			{
				if (A.y == 1)
				{
					break;
				}
				else
				{
					int temp = A.y - 1;
					if (map.Get_map_element(A.x, temp) == string("#"))
					{
						break;
					}
					cout << Washed_element;
					map.Wash_element(A.x, A.y);
					GoToXY(A.x, --A.y);
					map.Set_element(A.your_tank, A.x, A.y);
					cout << A.your_tank;
					Last_move = Last_move_up;
				}
			}break;
			case 80: // Down
			{
				if (A.y == size_map - 1)
				{
					break;
				}
				else
				{
					int temp = A.y + 1;
					if (map.Get_map_element(A.x, temp) == string("#"))
					{
						break;
					}
					cout << Washed_element;
					map.Wash_element(A.x, A.y);
					GoToXY(A.x, ++A.y);
					map.Set_element(A.your_tank, A.x, A.y);
					cout << A.your_tank;
					Last_move = Last_move_down;
				}
			}break;
			}
			Move_enemy_tanks();
		}
	}
	void Spawn_enemy_tank()
	{
		srand(static_cast<unsigned int>(time(NULL)));
		B.x = rand() % 10 + 2;
		B.y = rand() % 10 + 2;
		map.Set_element(B.enemy_tank, B.x, B.y);

	}
	void Set_lvl(int lvl)
	{
		int temp_x;
		int temp_y;
		int temp_move;
		this->lvl = lvl;
		switch (lvl)
		{
		case 1:
		{
			B.enemy_hp = 2;

		}break;
		case 2:
		{
			B.enemy_hp = 5;

		}break;
		case 3:
		{
			B.enemy_hp = 7;

		}break;
		case 4:
		{
			B.enemy_hp = 10;

		}break;
		}
	}
	void Move_enemy_tanks()
	{
		srand(static_cast<unsigned int>(time(NULL)));
		int temp_move;
		temp_move = rand() % 4 + 1;
		switch (temp_move)
		{
		case 1:
		{

			if (B.x == 1)
			{
				B.x++;
			}
			else
			{
				int temp = B.x - 1;
				if (map.Get_map_element(temp, B.y) == string("#"))
				{
					break;
				}
				cout << Washed_element;
				B.x--;
				GoToXY(B.x, B.y);
				cout << B.enemy_tank;
				map.Set_element(B.enemy_tank, B.x, B.y);
			}
		} break;
		case 2:
		{
			if (B.x == size_map - 1)
			{
				B.x--;
			}
			else
			{
				int temp = B.x + 1;
				if (map.Get_map_element(temp, B.y) == string("#"))
				{
					break;
				}
				cout << Washed_element;
				B.x++;
				GoToXY(B.x, B.y);
				cout << B.enemy_tank;
				map.Set_element(B.enemy_tank, B.x, B.y);
			}
		}break;
		case 3:
		{
			if (B.y == size_map + 1)
			{
				B.y++;
			}
			else
			{
				int temp = B.y - 1;
				if (map.Get_map_element(B.x, temp) == string("#"))
				{
					break;
				}
				cout << Washed_element;
				B.y--;
				GoToXY(B.x, B.y);
				cout << B.enemy_tank;
				map.Set_element(B.enemy_tank, B.x, B.y);
			}
		}break;
		case 4:
		{
			if (B.y == 1)
			{
				B.y--;
			}
			else
			{
				int temp = B.y + 1;
				if (map.Get_map_element(B.x, temp) == string("#"))
				{
					break;
				}
				cout << Washed_element;
				B.y++;
				GoToXY(B.x, B.y);
				cout << B.enemy_tank;
				map.Set_element(B.enemy_tank, B.x, B.y);
			}
		}break;
		}

	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	system("mode con cols=55 lines=30");
	Game::GetInstance().StartGame();

	_gettch();
	return 0;
}