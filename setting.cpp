#include "PokerHT.h"

void gotoXY(int x, int y)
{
	short X = (short)x, Y = (short)y;
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = {X, Y};
	hConsoleOutput = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}

void hidecursorscr()
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ci;
    ci.dwSize = 25;
    ci.bVisible = FALSE;
    SetConsoleCursorInfo(output, &ci);
}

void textcolor(int x)
{
   	HANDLE hConsoleColor;
    	hConsoleColor = GetStdHandle ( STD_OUTPUT_HANDLE);
      SetConsoleTextAttribute(hConsoleColor, x);
}
