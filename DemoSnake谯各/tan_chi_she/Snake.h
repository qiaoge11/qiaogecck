#pragma once
#include <vector>
#include "Food.h"
#include <iostream>
using namespace std;

typedef enum {
	UP,DOWN,LEFT,RIGHT
}Directions;

class CSnake
{
public:
	CSnake(int x = 40, int y = 10, int length = 4, Directions direction = RIGHT, char pic = '*');
	virtual ~CSnake();

	void changeDirection(int vkValue);//WSAD
	void move();
	bool eatFood(CFood *pFood);
	void showSnake();
	void eraseSnake();
	void growup();
	
	static int m_iScore;
	static int m_iLevel;
	static int m_iSpeed;
public:
	int m_iLength;
	int m_iHeadX;
	int m_iHeadY;
	
	int m_cPic;
	Directions m_enumCurrentDirection;
	vector<CUnit> m_vecBody;
};

