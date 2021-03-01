#include "Game.h"
#include <stdlib.h>
int main(void)
{
	CGame game1;
	game1.welcome_game();
	int flag = 1;
	while (flag)
	{
		system("cls");
		CGame game2;	
		flag=game2.run();
	}
	return 0;
	
}