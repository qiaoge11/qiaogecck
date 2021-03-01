#include "Snake.h"
#include <windows.h>


int CSnake::m_iScore = 0;
int CSnake::m_iLevel = 1;
int CSnake::m_iSpeed = 250;


CSnake::CSnake(int x, int y, int length, Directions direction,  char pic)
{
	m_iHeadX = x;
	m_iHeadY = y;
	m_iLength = length;
	m_enumCurrentDirection = direction;
	m_cPic = pic;

	int tempX = 0;
	int tempY = 0;

	for (int i = 0; i < m_iLength; i++)
	{
		
		switch (m_enumCurrentDirection)
		{
		case UP:
			tempX = m_iHeadX;
			tempY = m_iHeadY + i;
			break;
		case DOWN:
			tempX = m_iHeadX;
			tempY = m_iHeadY - i;
			break;
		case LEFT:
			tempX = m_iHeadX + i;
			tempY = m_iHeadY;
			break;
		case RIGHT:
			tempX = m_iHeadX - i;
			tempY = m_iHeadY;
			break;
		}

		if (i == 0)
		{
			CUnit unit(tempX, tempY, '@');
			m_vecBody.push_back(unit);
		}
		else
		{
			CUnit unit(tempX, tempY, pic);
			m_vecBody.push_back(unit);
		}
		/*CUnit unit(tempX, tempY, pic);
		m_vecBody.push_back(unit);*/
	}
}


CSnake::~CSnake()
{
}


void CSnake::showSnake()
{
	for (int i = 0; i < m_iLength; i++)
	{
		m_vecBody[i].show();
	}
	CUnit::gotoxy(2, 29);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout<< ' ';
}
void CSnake::eraseSnake()
{
	for (int i = 0; i < m_iLength; i++)
	{
		m_vecBody[i].erase();
	}
}

void CSnake::changeDirection(int vkValue)
{
	switch (vkValue)
	{
	case 'w':  
	case 'W':
	case 72:
		if (m_enumCurrentDirection == LEFT || m_enumCurrentDirection == RIGHT) 
			m_enumCurrentDirection = UP;
		break;
	case 's':
	case 'S':
	case 80:
		if (m_enumCurrentDirection == LEFT || m_enumCurrentDirection == RIGHT)
			m_enumCurrentDirection = DOWN;
		break;			
	case 'a':
	case 'A':
	case 75 :
		if (m_enumCurrentDirection == UP || m_enumCurrentDirection == DOWN)
			m_enumCurrentDirection = LEFT;
		break;
	case 'd':
	case 'D':
	case 77:
		if (m_enumCurrentDirection == UP || m_enumCurrentDirection == DOWN)
			m_enumCurrentDirection = RIGHT;
		break;
	}
}

void CSnake::move()
{
	//²Á³ýÉßÉí
	eraseSnake();

	for (int i = m_iLength - 2; i >= 0; i--)
	{
		m_vecBody[i + 1].m_iX = m_vecBody[i].m_iX;
		m_vecBody[i + 1].m_iY = m_vecBody[i].m_iY;
	}

	switch (m_enumCurrentDirection)
	{
	case UP:
		m_vecBody[0].m_iY--;
		break;
	case DOWN:
		m_vecBody[0].m_iY++;
		break;
	case LEFT:
		m_vecBody[0].m_iX--;
		break;
	case RIGHT:
		m_vecBody[0].m_iX++;
		break;
	}

	showSnake();

	Sleep(m_iSpeed);
	//_sleep(m_iSpeed);
}

void CSnake::growup()
{
	CUnit unit(0, 0, m_cPic);
	m_vecBody.push_back(unit);
	m_iLength++;
	m_iSpeed -= 20;	
}

bool CSnake::eatFood(CFood *pFood)
{
	if (m_vecBody[0].m_iX == pFood->m_iX && m_vecBody[0].m_iY == pFood->m_iY)
	{
		growup();
		
		return true;
	}
	return false;
}