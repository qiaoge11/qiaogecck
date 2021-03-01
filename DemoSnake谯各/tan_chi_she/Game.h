#pragma once

#include "Snake.h"
#include<stdio.h>
class CGame
{
public:
	CGame();
	virtual ~CGame();
	bool checkFailed();
	bool checkLevel();
	void changeInfo(); 
	void drawGameArea();
	void drawGameInfo();
	void welcome_game();
	void explation();
	int game_over();
	int run();

public:
	static const int KLEFT;
	static const int KUP;
	static const int KWIDTH;
	static const int KHEIGHT;
	//static const int KSCORE_OFFSET;
	//static const int KLEVEL_OFFSET;
	
public:
	CFood* m_pFood;
	CSnake *m_pSnake;
	
};

