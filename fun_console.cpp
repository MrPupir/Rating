#include <windows.h>
#include "fun_console.h"

void GotoXY(short x, short y) {
	COORD coord = { x,  y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Clear()
{
	SetConsoleSize(120, 30);
	system("cls");
}

void SetColor(short textcolor, short bgcolor) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((bgcolor << 4) | textcolor));
}

void SetConsoleSize(short x, short y)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD bufferSize;
	bufferSize.X = x;
	bufferSize.Y = y;

	SetConsoleScreenBufferSize(consoleHandle, bufferSize);
}

void SetSize(short x, short y)
{
	COORD coord = { x, y };
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int GetRows()
{
	CONSOLE_SCREEN_BUFFER_INFO c;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c))
		return 0;
	return c.dwSize.Y;
}

int GetCols()
{
	CONSOLE_SCREEN_BUFFER_INFO c;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c))
		return 0;
	return c.dwSize.X;
}

int GetCurrentY()
{
	CONSOLE_SCREEN_BUFFER_INFO c;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c))
		return 0;
	return c.dwCursorPosition.Y;
}

int GetCurrentX()
{
	CONSOLE_SCREEN_BUFFER_INFO c;
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &c))
		return 0;
	return c.dwCursorPosition.X;
}

bool GetCaret() {
	CONSOLE_CURSOR_INFO ci;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
	return ci.bVisible;
}

void ShowCaret(bool show)
{
	CONSOLE_CURSOR_INFO ci;
	ci.bVisible = show;
	ci.dwSize = 100;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
}