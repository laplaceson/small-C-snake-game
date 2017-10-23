#include <iostream>
#include <windows.h>
#include <conio.h>
#include<stdlib.h>
#include<ctime>
using namespace std;

void SetColor(int f = 7, int b = 0)
{
	unsigned short ForeColor = f + 16 * b;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, ForeColor);
}
void gotoxy(int xpos, int ypos)// jump the  cursor tp (xpos,ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void draw(int x, int y, char s)
{
	gotoxy(x, y);
	if (s == '@'){ SetColor(6, 0); cout << s; SetColor(); }
	if (s == '#'){ SetColor(7, 0); cout << s; SetColor(); }
	if (s == '*'){ SetColor(4, 0); cout << s; SetColor(); }
	if (s == ' '){ cout << s; }
}
struct XY    // a structure to save direction vector X Y position 
{
	int x, y;
	void set(int X, int Y) { x = X; y = Y; }
};

int main()
{
	int i, egg = 0, len1 = 1, point = 0, eatme = 0;
	char p, status = 'y';
	srand(time(0));
	XY body[80];

	int x, y;
	while (status = 'y')// continue the game
	{
		for (i = 0; i < 60; i++){ draw(i, 0, '#'); draw(i, 20, '#'); }//room 恆X橫的Y直的
		for (i = 0; i < 20; i++){ draw(0, i, '#'); draw(60, i, '#'); }//room 直
		status = 'y';
		XY v = { 0, 0 };
		len1 = 1; eatme = 0; egg = 0; point = 0;
		x = rand() % 59 + 1;//生蛋
		y = rand() % 19 + 1;//生蛋
		draw(x, y, '*');//生蛋
		egg = 1;//生蛋
		body[0].x = 10;
		body[0].y = 10;
		body[0].x = 10;
		body[0].y = 10;
		while (1)//gaming loop
		{
			if (_kbhit())//if keyboard input 
			{
				p = _getch();
				switch (p)// limit the direction Ex.(a snake is going up, if you press down, it will be no use )
				{
				case 72:if (v.y != 1) v.set(0, -1); break;
				case 80:if (v.y != -1) v.set(0, 1); break;
				case 75:if (v.x != 1) v.set(-1, 0); break;
				case 77:if (v.x != -1) v.set(1, 0); break;
				}
			}
			if (body[0].x == 0 || body[0].x == 60 || body[0].y == 0 || body[0].y == 20){ gotoxy(62, 0); cout << "YOU HIT THE WALL" << endl; break; }
			for (int i = 1; i < len1; i++){ if (body[0].x == body[i].x&&body[0].y == body[i].y){ gotoxy(62, 1); cout << "YOU EAT YOURSELF" << endl; eatme = 1; break; } }
			if (eatme == 1){ break; }
			if (egg == 0){
				x = rand() % 59 + 1;
				y = rand() % 19 + 1;
				draw(x, y, '*');
				egg = 1;
			}
			if (body[0].x == x&&body[0].y == y){ egg = 0; point++; len1++; gotoxy(62, 4); cout << "POINT==" << point << endl; }
			draw(body[len1 - 1].x, body[len1 - 1].y, ' ');//移除尾
			for (i = len1 - 1; i > 0; --i)
			{
				body[i] = body[i - 1];
			}
			body[0].x += v.x;
			body[0].y += v.y;

			draw(body[0].x, body[0].y, '@');//draw the snake's head
			Sleep(100 - len1 * 10);
		}
		status = 'f';
		gotoxy(62, 2); cout << "YOU LOSE" << endl;
		cout << "DO YOU WANT TO CONTINUE?:";
		cin >> status;
		if (status == 'y'){ system("cls"); }//restart game? 'y'
		else break;
	}
}










