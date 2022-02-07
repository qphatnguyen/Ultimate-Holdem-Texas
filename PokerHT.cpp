#include "PokerHT.h"

int main()
{
	bool stopped_con = false;
	displayMenu(stopped_con);
	system("cls");
	if (!stopped_con){
		playGame();
	}
	
	return 0;
}
