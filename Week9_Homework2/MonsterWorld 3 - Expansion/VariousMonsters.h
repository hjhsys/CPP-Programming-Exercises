#pragma once
#include <Windows.h>
#include <time.h>
#include "Monster.h"

static clock_t tStart;

class Zombie : public Monster
{
public:
	Zombie(string n = "«„¡¢¡ª∫Ò", string i = "°◊", int x = 0, int y = 0)
		:Monster(n, i, x, y) {}
	~Zombie() { cout << " Zombie"; }
};

class Smombi : public Monster
{
public:
	Smombi(string n = "Ω∫∏ˆ∫Ò", string i = "£¶", int x = 0, int y = 0)
		:Monster(n, i, x, y) {}
	~Smombi() { cout << " Smombi"; }

	void move(int** map, int maxx, int maxy)
	{
		int dir = rand() % 4;
		if (dir == 0) x--, y--;
		else if (dir == 1) x--, y++;
		else if (dir == 2) x++, y--;
		else x++, y++;
		clip(maxx, maxy);
		eat(map);
	}
};

class Vampire : public Monster
{
public:
	Vampire(string n = "πÏ∆ƒ¿ÃæÓ", string i = "°⁄", int x = 0, int y = 0)
		:Monster(n, i, x, y) {}
	~Vampire() { cout << " Vampire"; }

	void move(int** map, int maxx, int maxy)
	{
		int dir = rand() % 4;
		if (dir == 0) x--;
		else if (dir == 1) x++;
		else if (dir == 2) y--;
		else y++;
		clip(maxx, maxy);
		eat(map);
	}
};

class Knight : public Vampire
{
public:
	Knight(string n = "≥™¿Ã∆Æ", string i = "°Â", int x = 0, int y = 0)
		:Vampire(n, i, x, y) {}
	~Knight() { cout << " Knight"; }

	void move_knight(int** map, int maxx, int maxy)
	{
		int x1 = x;
		int y1 = y;
		move(map, maxx, maxy);

		if ((x1 != x) && !(y1 != y))
		{
			if (x1 < x)
				x++;
			else
				x--;
			clip(maxx, maxy);

			int dir = rand() % 2;
			if (dir == 0) 
				y++;
			else 
				y--;
			clip(maxx, maxy);
			eat(map);
		}
		else if (!(x1 != x) && (y1 != y))
		{
			if (y1 < y)
				y++;
			else
				y--;
			clip(maxx, maxy);

			int dir = rand() % 2;
			if (dir == 0)
				x++;
			else
				x--;
			clip(maxx, maxy);
			eat(map);
		}
	}
};

class KGhost : public Monster
{
public:
	KGhost(string n = "√≥≥‡±ÕΩ≈", string i = "°›", int x = 0, int y = 0)
		:Monster(n, i, x, y) {}
	~KGhost() { cout << " KGhost"; }

	void move(int** map, int maxx, int maxy)
	{
		x = rand() % maxx;
		y = rand() % maxy;
		clip(maxx, maxy);
		eat(map);
	}
};

class Jiangshi : public Monster
{
protected:
	bool bHori;
public:
	Jiangshi(string n = "¥Î∑˙∞≠Ω√", string i = "°‡", int x = 0, int y = 0, bool bH = true)
		:Monster(n, i, x, y), bHori(bH) {}
	~Jiangshi() { cout << " Jiangshi"; }

	void move(int** map, int maxx, int maxy)
	{
		int dir = rand() % 2;
		int jump = rand() % 2 + 1;
		if (bHori) x += ((dir == 0) ? -jump : jump);
		else y += ((dir == 0) ? -jump : jump);
		clip(maxx, maxy);
		eat(map);
	}
};

class Siangshi : public Jiangshi
{
public:
	Siangshi(string n = "ºßΩ√", string i = "°‡", int x = 0, int y = 0, bool bH = false)
		:Jiangshi(n, i, x, y, bH)
	{
		tStart = clock();
	}
	~Siangshi() { cout << " Siangshi"; }

	void move_change(int** map, int maxx, int maxy)
	{
		clock_t t1 = clock();
		double d = (double)(t1 - tStart) / CLOCKS_PER_SEC;
		if (d >= 2)				// ±‚¡ÿ Ω√∞£
		{
			tStart = clock();
			bHori = !bHori;
		}
		move(map, maxx, maxy);
	}
};