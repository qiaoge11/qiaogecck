#include "Game.h"
#include <conio.h>
#include <iostream>
using namespace std;

const int CGame::KLEFT = 5;
const int CGame::KUP = 2;
const int CGame::KWIDTH = 110;
const int CGame::KHEIGHT = 25;
//const int CGame::KSCORE_OFFSET = 50;
//const int CGame::KLEVEL_OFFSET = 65;


CGame::CGame()
{
	m_pFood = new CFood();
	m_pSnake = new CSnake();	
}

CGame::~CGame()
{
	delete m_pFood;
	delete m_pSnake;
	m_pFood = NULL;
	m_pSnake = NULL;
	CSnake::m_iScore = 0;
	CSnake::m_iLevel = 1;
}

/*
-------------------------
|                       |
|-----------------------|
|                       |
|                       |
|        ****           |
|                       |
|                       |
|                       |
-------------------------
 */

void CGame::drawGameArea()
{
	/*SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);*/
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	CUnit::gotoxy(KLEFT, KUP);
	for (int j = 0; j < KWIDTH; j++)//第一行
	{
		cout << "-";
	}

	for (int i = 0; i < KHEIGHT; i++)//左右列
	{
		CUnit::gotoxy(KLEFT, KUP + 1 + i);
		cout << "|";
		CUnit::gotoxy(KLEFT + KWIDTH - 1, KUP + 1 + i);
		cout << "|";
	}

	CUnit::gotoxy(KLEFT, KUP + KHEIGHT + 1);//最后一行
	for (int k = 0; k < KWIDTH; k++)
	{
		cout << "-";
	}

	CUnit::gotoxy(KLEFT + 1, KUP + 2);//第二个行
	for (int i = 0; i < KWIDTH - 2; i++)
	{
		cout << "-";
	}

	CUnit::gotoxy(KLEFT + 26, KUP + 1);
	cout << "|";
	CUnit::gotoxy(KLEFT + 56, KUP + 1);
	cout << "|";
	CUnit::gotoxy(KLEFT + 86, KUP + 1);
	cout << "|";
}

void CGame::drawGameInfo()
{
	CUnit::gotoxy(KLEFT + 1, KUP + 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << "游戏名称：贪吃蛇";

	CUnit::gotoxy(KLEFT + 35, KUP + 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	cout << "编写者：谯各";

	CUnit::gotoxy(KLEFT + 65, KUP + 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout << "当前得分：";

	CUnit::gotoxy(KLEFT + 75, KUP + 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	cout << CSnake::m_iScore;

	CUnit::gotoxy(KLEFT + 93, KUP + 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << "当前关卡：";

	CUnit::gotoxy(KLEFT + 103, KUP + 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	cout << CSnake::m_iLevel;
	
}



int CGame::run()
{
	
	drawGameArea();
	drawGameInfo();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	m_pFood->createPos(&(m_pSnake->m_vecBody));

	m_pFood->show();

	m_pSnake->showSnake();

	int key = 0;

	bool stopFlag = true;

	bool pauseFlag = true;

	while (key != VK_ESCAPE && stopFlag)  //0x1b
	{
		if (_kbhit())
		{
			key = _getch();

			if (key == VK_SPACE)
			{
				pauseFlag = !pauseFlag;

			}

			m_pSnake->changeDirection(key);
		}
		else
		{
			if (pauseFlag)
			{
				continue;
			}

			m_pSnake->move();

			if (m_pSnake->eatFood(m_pFood))
			{
				//加分   检测过关  改变游戏信息
				CSnake::m_iScore += 10;

				if (checkLevel())
				{
					stopFlag = false;
				}

				changeInfo();

				if (stopFlag)
				{
					m_pFood->createPos(&(m_pSnake->m_vecBody));

					m_pFood->show();
				}
				/*else
				{
					CUnit::gotoxy(KLEFT + 5, KUP + 26);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					cout << "  ";
				}*/
			}

			//检测是否撞墙
			//检测是否自残
			if (checkFailed())
			{
				stopFlag = false;
				/*this->~CGame();*/
				int info_flag=game_over();

				if(info_flag==0)
				     exit(0);
				else 
					return  true;
			}

		}

	}
}

bool CGame::checkFailed()
{
	//检测是否撞墙

	//检测左墙
	if (m_pSnake->m_vecBody[0].m_iX <= CGame::KLEFT)
	{
		return true;
	}

	//检测右墙
	if (m_pSnake->m_vecBody[0].m_iX >= CGame::KLEFT + CGame::KWIDTH - 1)
	{
		return true;
	}

	//检测上墙
	if (m_pSnake->m_vecBody[0].m_iY <= CGame::KUP + 2)
	{
		return true;
	}

	//检测下墙
	if (m_pSnake->m_vecBody[0].m_iY >= CGame::KUP + CGame::KHEIGHT + 1)
	{
		return true;
	}

	//检测是否自残
	for (int i = 4; i < m_pSnake->m_iLength; i++)
	{
		if (m_pSnake->m_vecBody[0].m_iX == m_pSnake->m_vecBody[i].m_iX && m_pSnake->m_vecBody[0].m_iY == m_pSnake->m_vecBody[i].m_iY)
		{
			return true;
		}
	}

	return false;
}

bool CGame::checkLevel()
{
	int temp = CSnake::m_iScore / 30 + 1;

	if (temp == CSnake::m_iLevel)
	{
		return false;
	}

	CSnake::m_iLevel = temp;

	//switch (CSnake::m_iLevel)
	//{
	//case 1:
	//	break;
	//case 2:
	//	break;
	//case 3:
	//	break;
	//case 4:
	//	break;
	//case 5:
	//	//通关
	//	CUnit::gotoxy(30, 10);
	//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	//	cout << "游戏通关，VERY GOOD!!!" << endl;
	//	return true;
	//	break;
	//}
	return false;
}

void CGame::changeInfo()
{

	CUnit::gotoxy(KLEFT + 75, KUP + 1);
	cout << "  ";
	CUnit::gotoxy(KLEFT + 75, KUP + 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	cout << CSnake::m_iScore;

	CUnit::gotoxy(KLEFT + 103, KUP + 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "  ";
	CUnit::gotoxy(KLEFT + 103, KUP + 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	cout << CSnake::m_iLevel;
	
}

void CGame::welcome_game()
{
	int n=0;
	int i, j = 1;

	CUnit::gotoxy(54, 10);

	//color(11);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << "贪吃蛇游戏";

	//color(14);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	for (i = 14; i <= 20; i++)
	{
		for (j = 35; j <= 82; j++)
		{
			CUnit::gotoxy(j, i);
			if (i == 20 || i == 14)
				cout<<"-";
			else
				if (j == 35 || j == 82)
					cout<<"|";
		}
	}

	//color(12);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	CUnit::gotoxy(43, 16);
	printf("1.开始游戏");

	CUnit::gotoxy(63, 16);
	printf("2.游戏说明");

	CUnit::gotoxy(43, 18);
	printf("3.退出游戏");

	CUnit::gotoxy(50, 23);
	//color(3); 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	cout << "请选择[1 2 3]:[ ]\b\b";     //b为退格，使得光标处于0中间
	
    //color(14);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |FOREGROUND_GREEN | FOREGROUND_BLUE);
	cin >> n;          //输入选项
	
	switch(n)          //3个选项
	{
	case 1:              //选项1
		system("cls");        //清屏		 
		run();		
		break;
	case 2:            //选项2
		explation();
		break;
	case 3:             //选项3
		exit(0);                   //退出程序
		break;//输入非1~3的选项
	default:
		//color(12); 
		/*CUnit::gotoxy(40, 28);
		cout << "请输入1~3之间的数:";*/	                     //输入任意键
		
		system("cls");       //清屏

		welcome_game();
		
	}
}

void CGame::explation()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	int i, j = 1;
	system("cls");
 
	CUnit::gotoxy(54, 3);
	cout << "游戏说明";

	for (i = 6; i <= 22; i++)//输出上下边框===
	{
		for (j = 24; j <= 94; j++)//输出左右边框|| 
		{
			CUnit::gotoxy(j, i);
			if (i == 6 || i == 22)     cout << "=";
			else if (j == 24 || j == 94)  cout << "||";

		}

	}

	//color(3);
	CUnit::gotoxy(33, 8);
	cout << "1:不能穿墙，不能咬到自己。";

	//color(10);
	CUnit::gotoxy(33, 11);
	cout << "2:用↑.↓.←.→或者W,S,A,D或者w,s,a,d分别控制蛇的移动。";

	//color(14);
	CUnit::gotoxy(33, 14);
	cout << "3:按空格键暂停游戏，再按空格键继续。";

	//color(11);
	CUnit::gotoxy(33, 17);
	cout << "4:ESC :退出游戏。   space(空格):暂停游戏。";

	CUnit::gotoxy(33, 20);
	cout << "5;现在按任意键返回首页";

	CUnit::gotoxy(49, 25);

	system("pause");
	system("exit");

	system("cls");

	//printsnake();
	welcome_game();
}

int CGame::game_over()
{
	system("cls");
	CUnit::gotoxy(53, 7);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "GAME OVER!!!";

	for (int i = 11; i <= 19; i++)//输出上下边框===
	{
		for (int j = 40; j <= 76; j++)//输出左右边框|| 
		{
			CUnit::gotoxy(j, i);
			if (i == 11 || i == 19)     cout << "=";
			else if (j == 40 || j == 75)  cout << "||";
		}

	}

	CUnit::gotoxy(44, 15);
	cout << "1:重新开始  ";

	CUnit::gotoxy(62, 15);
	cout << "0：退出游戏 ";

	CUnit::gotoxy(40, 26);
	cout << "注意：输入“0”或者其他数，默认为退出游戏 ";

	CUnit::gotoxy(51, 22);
	cout << "请选择[0 1]:[ ]\b\b";

	
	int val;
	cin >> val;
	while (1)
	{
		if (val == 1)
		{
			return 1;
		}
		else if (val == 0)
		{
			return 0;
		}
		else
		{			
		
				return 0;
			
		}
	}
}