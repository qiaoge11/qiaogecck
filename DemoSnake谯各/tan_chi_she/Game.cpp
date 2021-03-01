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
	for (int j = 0; j < KWIDTH; j++)//��һ��
	{
		cout << "-";
	}

	for (int i = 0; i < KHEIGHT; i++)//������
	{
		CUnit::gotoxy(KLEFT, KUP + 1 + i);
		cout << "|";
		CUnit::gotoxy(KLEFT + KWIDTH - 1, KUP + 1 + i);
		cout << "|";
	}

	CUnit::gotoxy(KLEFT, KUP + KHEIGHT + 1);//���һ��
	for (int k = 0; k < KWIDTH; k++)
	{
		cout << "-";
	}

	CUnit::gotoxy(KLEFT + 1, KUP + 2);//�ڶ�����
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
	cout << "��Ϸ���ƣ�̰����";

	CUnit::gotoxy(KLEFT + 35, KUP + 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	cout << "��д�ߣ��۸�";

	CUnit::gotoxy(KLEFT + 65, KUP + 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout << "��ǰ�÷֣�";

	CUnit::gotoxy(KLEFT + 75, KUP + 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	cout << CSnake::m_iScore;

	CUnit::gotoxy(KLEFT + 93, KUP + 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << "��ǰ�ؿ���";

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
				//�ӷ�   ������  �ı���Ϸ��Ϣ
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

			//����Ƿ�ײǽ
			//����Ƿ��Բ�
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
	//����Ƿ�ײǽ

	//�����ǽ
	if (m_pSnake->m_vecBody[0].m_iX <= CGame::KLEFT)
	{
		return true;
	}

	//�����ǽ
	if (m_pSnake->m_vecBody[0].m_iX >= CGame::KLEFT + CGame::KWIDTH - 1)
	{
		return true;
	}

	//�����ǽ
	if (m_pSnake->m_vecBody[0].m_iY <= CGame::KUP + 2)
	{
		return true;
	}

	//�����ǽ
	if (m_pSnake->m_vecBody[0].m_iY >= CGame::KUP + CGame::KHEIGHT + 1)
	{
		return true;
	}

	//����Ƿ��Բ�
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
	//	//ͨ��
	//	CUnit::gotoxy(30, 10);
	//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	//	cout << "��Ϸͨ�أ�VERY GOOD!!!" << endl;
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
	cout << "̰������Ϸ";

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
	printf("1.��ʼ��Ϸ");

	CUnit::gotoxy(63, 16);
	printf("2.��Ϸ˵��");

	CUnit::gotoxy(43, 18);
	printf("3.�˳���Ϸ");

	CUnit::gotoxy(50, 23);
	//color(3); 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	cout << "��ѡ��[1 2 3]:[ ]\b\b";     //bΪ�˸�ʹ�ù�괦��0�м�
	
    //color(14);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |FOREGROUND_GREEN | FOREGROUND_BLUE);
	cin >> n;          //����ѡ��
	
	switch(n)          //3��ѡ��
	{
	case 1:              //ѡ��1
		system("cls");        //����		 
		run();		
		break;
	case 2:            //ѡ��2
		explation();
		break;
	case 3:             //ѡ��3
		exit(0);                   //�˳�����
		break;//�����1~3��ѡ��
	default:
		//color(12); 
		/*CUnit::gotoxy(40, 28);
		cout << "������1~3֮�����:";*/	                     //���������
		
		system("cls");       //����

		welcome_game();
		
	}
}

void CGame::explation()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	int i, j = 1;
	system("cls");
 
	CUnit::gotoxy(54, 3);
	cout << "��Ϸ˵��";

	for (i = 6; i <= 22; i++)//������±߿�===
	{
		for (j = 24; j <= 94; j++)//������ұ߿�|| 
		{
			CUnit::gotoxy(j, i);
			if (i == 6 || i == 22)     cout << "=";
			else if (j == 24 || j == 94)  cout << "||";

		}

	}

	//color(3);
	CUnit::gotoxy(33, 8);
	cout << "1:���ܴ�ǽ������ҧ���Լ���";

	//color(10);
	CUnit::gotoxy(33, 11);
	cout << "2:�á�.��.��.������W,S,A,D����w,s,a,d�ֱ�����ߵ��ƶ���";

	//color(14);
	CUnit::gotoxy(33, 14);
	cout << "3:���ո����ͣ��Ϸ���ٰ��ո��������";

	//color(11);
	CUnit::gotoxy(33, 17);
	cout << "4:ESC :�˳���Ϸ��   space(�ո�):��ͣ��Ϸ��";

	CUnit::gotoxy(33, 20);
	cout << "5;���ڰ������������ҳ";

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

	for (int i = 11; i <= 19; i++)//������±߿�===
	{
		for (int j = 40; j <= 76; j++)//������ұ߿�|| 
		{
			CUnit::gotoxy(j, i);
			if (i == 11 || i == 19)     cout << "=";
			else if (j == 40 || j == 75)  cout << "||";
		}

	}

	CUnit::gotoxy(44, 15);
	cout << "1:���¿�ʼ  ";

	CUnit::gotoxy(62, 15);
	cout << "0���˳���Ϸ ";

	CUnit::gotoxy(40, 26);
	cout << "ע�⣺���롰0��������������Ĭ��Ϊ�˳���Ϸ ";

	CUnit::gotoxy(51, 22);
	cout << "��ѡ��[0 1]:[ ]\b\b";

	
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