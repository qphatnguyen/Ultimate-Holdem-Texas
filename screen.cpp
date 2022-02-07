#include "PokerHT.h"
// ----- Menu -----
char BoxMenu[HEIGHT][WIDTH] = {"\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb",
				 "\xdb                                                               \xdb",
				 "\xdb                                   \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb   \xdb",
				 "\xdb    \x03                         \x03    \xba                       \xba   \xdb",
				 "\xdb                                   \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc   \xdb",
				 "\xdb                                                               \xdb",
				 "\xdb                                   \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb   \xdb",
				 "\xdb    \x04                         \x04    \xba                       \xba   \xdb",
				 "\xdb                                   \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc   \xdb",
				 "\xdb    \x03                         \x03                                \xdb",
				 "\xdb                                   \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb   \xdb",
				 "\xdb                                   \xba                       \xba   \xdb",
				 "\xdb                                   \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc   \xdb",
				 "\xdb    \x04                         \x04                                \xdb",
				 "\xdb                                                               \xdb",
				 "\xdb                                                               \xdb",
				 "\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb"};


char AceOfSpade_Logo[HEIGHT-3][WIDTH-2] = {"\xd6\xc4        @        \xc4\xb7",
							 "\xba        @@@        \xba",
							 "       @@@@@@@       ",
							 "     @@@@@@@@@@@     ",
							 "   @@@@@@@@@@@@@@@   ",
							 " @@@@@@@@@@@@@@@@@@@ ",
							 "@@@@@@@@@@@@@@@@@@@@@",
							 "@@@@@@@@@@@@@@@@@@@@@",
							 " @@@@@@@ @@@ @@@@@@@ ",
							 "  @@@@@  @@@  @@@@@  ",
							 "         @@@         ",
							 "\xba       @@@@@       \xba",
							 "\xd3\xc4     @@@@@@@     \xc4\xbd"};

// ----- Record Table -----
char RecordTable[HEIGHT-8][WIDTH-19] = {
	"\xc9\xcd\xcd\xcd\xcb\xcd\xcd\xcd\xcd\xcd\xcb\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcb\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb",
	"\xbaNo.\xbaRound\xba Chips \xba           Time           \xba",
	"\xcc\xcd\xcd\xcd\xce\xcd\xcd\xcd\xcd\xcd\xce\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xce\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xb9",
	"\xba 1 \xba\x65mpty\xba empty \xba          empty           \xba",
	"\xcc\xcd\xcd\xcd\xce\xcd\xcd\xcd\xcd\xcd\xce\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xce\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xb9",
	"\xba 2 \xba\x65mpty\xba empty \xba          empty           \xba",
	"\xcc\xcd\xcd\xcd\xce\xcd\xcd\xcd\xcd\xcd\xce\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xce\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xb9",
	"\xba 3 \xba\x65mpty\xba empty \xba          empty           \xba",
	"\xc8\xcd\xcd\xcd\xca\xcd\xcd\xcd\xcd\xcd\xca\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xca\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc"
};

// ----- Play game -----
void NameOfTheboxGame()
{
	gotoXY(17, 2);
	textcolor(13);
	cout << "\x10{ POKER HOLD'EM TEXAS }\x11";
	textcolor(7);
}

void NameOfTheboxInfo()
{
	gotoXY(58, 2);
	textcolor(15);
	cout << "INFORMATION";
	textcolor(7);
}

void NameOfTheboxBet()
{
	gotoXY(59, 12);
	textcolor(15);
	cout << "\x11{-BET-}\x10";
	textcolor(7);
}

void backspace_insideboxGame()
{
	int y = 3;
	while(y <= 17){
		gotoXY(4, y);
		cout << "                                                    ";
		y++;
	}
}

void drawboxGame()
{
	int height = 17, width = 55, y = 2;
	for (int i = 0; i < height; i++){
		gotoXY(2, y);
		if (i == 0 || i == height - 1){
			for (int j = 0; j < width; j++)
				cout << "\xdb";
			cout << endl;
		}
		else{
			for (int j = 0; j < width; j++){
				if (j == 0 || j == width - 1)
					cout << "\xdb";
				else
					cout << " ";
			}
			cout << endl;
		}
		y++;
	}
}

void backspace_insideboxInfo()
{
	int height = 9, width = 13, x = 57, y = 3;
	
	for (int i = 0; i < height; i++){
		gotoXY(x, y);
		for (int j = 0; j < 13; j++)
			cout << " ";
		y++;
	}
}

void drawboxInfo()
{
	int height = 11, width = 15, x = 56, y = 2;
	
	for (int i = 0; i < height; i++){
		gotoXY(x, y);
		if (i == 0 || i == height - 1){
			for (int j = 0; j < width; j++)
				cout << "\xdb";
			cout << endl;
		}
		else{
			for (int j = 0; j < width; j++){
				if (j == 0 || j == width - 1)
					cout << "\xdb";
				else
					cout << " ";
			}
			cout << endl;
		}
		y++;
	}
}

void backspace_insideboxBet()
{
	int height = 5, width = 13, x = 57, y = 13;
	
	for (int i = 0; i < height; i++){
		gotoXY(x, y);
		for (int j = 0; j < 13; j++)
			cout << " ";
		y++;
	}
}

void drawboxBet()
{
	int height = 7, width = 15, x = 56, y = 12;
	
	for (int i = 0; i < height; i++){
		gotoXY(x, y);
		if (i == 0 || i == height - 1){
			for (int j = 0; j < width; j++)
				cout << "\xdb";
			cout << endl;
		}
		else{
			for (int j = 0; j < width; j++){
				if (j == 0 || j == width - 1)
					cout << "\xdb";
				else
					cout << " ";
			}
			cout << endl;
		}
		y++;
	}
}
