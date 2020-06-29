#include <windows.h>
#include <iostream>
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 77
#define KEY_RIGHT 75
#define KEY_ENTER 13

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTAQUA 11
#define LIGHTRED 12
#define LIGHTPURPLE 13
#define LIGHTYELLOW 14
#define BRIGHTWHITE 15

//Changes writing color
void textcolor(int text, int background)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(text | background << 4));
}

//Jumps to position x,y in the cmd
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void header()
{
    gotoxy(0, 0);
    textcolor(LIGHTYELLOW, BLACK);
    std::cout << "Critical path method";
    gotoxy(0, 1);
    textcolor(YELLOW, BLACK);
    std::cout << "Engenharia de Computacao - UNIVALI";
    gotoxy(0, 2);
    std::cout << "Graphs";
    gotoxy(0, 3);
    std::cout << "Andriy Fujii Pendloski";

    textcolor(BLACK, WHITE);
    gotoxy(0, 5);
    system("pause");
    textcolor(BRIGHTWHITE, BLACK);
}