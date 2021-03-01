#include "Unit.h"
#include <iostream>
using namespace std;

CUnit::CUnit(int x, int y, char pic)
{
	m_iX = x;
	m_iY = y;	
	m_cPic = pic;
}
CUnit::~CUnit()
{
}
void CUnit::gotoxy(int x, int y)
{
	COORD coor;
	coor.X = x;
	coor.Y = y;

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, coor);
}

//int color(int c)
//{
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
//	return 0;
//}
void CUnit::show()
{
	
	gotoxy(m_iX, m_iY);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << m_cPic;
}
void CUnit::erase()
{
	gotoxy(m_iX, m_iY);
	cout << " ";
}

