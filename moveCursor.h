#pragma once

#include <windows.h> // SetConsoleCursorPosition(HANDLE,COORD)

void moveCursor(int x, int y)
{
	COORD c = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
