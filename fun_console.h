#ifndef FUN_CONSOLE_H
#define FUN_CONSOLE_H
enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

void GotoXY(short x, short y);
void Clear();
void SetColor(short textcolor, short bkcolor);
void SetConsoleSize(short X, short Y);
void SetSize(short x, short y);
int GetRows();
int GetCols();
int GetCurrentY();
int GetCurrentX();
bool GetCaret();
void ShowCaret(bool show = true);

#endif