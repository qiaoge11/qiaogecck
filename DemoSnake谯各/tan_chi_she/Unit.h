#pragma once

#include <Windows.h>
class CUnit
{

public:
	CUnit(int x = 0, int y = 0, char pic = '*');
	virtual ~CUnit();
	void show();
	void erase();
	static void gotoxy(int x, int y);
	//int color(int c);

public:
	int m_iX;
	int m_iY;
	char m_cPic;
};

