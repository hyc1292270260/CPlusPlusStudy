#include <stdio.h>
#include <windows.h>
#include<conio.h>
#include <stdlib.h>
#include<time.h>

#define X 23//地图的x轴
#define Y 75//地图的y轴

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define WAIT_TIME 200//等待蛇刷新的时间,可以说是速度  修改可变速

int map_0[X][Y];//地图
int Snake[X*Y][2]; // 蛇
int Slength; //蛇的长度
int direction;
int score = 0;

bool pdEatFood = false;

void csh();
void huaMap();
void huaSnake();
void gotoxy(int x, int y);
void move();
void intokey();
int check(int x, int y);
void putfood();
bool gameover();
void dy_fs();

int main()
{
	csh();
	huaMap();
	putfood();
	while (1)
	{
		huaSnake();
		Sleep(WAIT_TIME);
		intokey();
		move();
		dy_fs();
		if (gameover())
		{
			system("cls");          //清除屏幕内容
			printf("Game Over\n");
			system("pause");
			getchar();
			break;
		}
		if (map_0[Snake[0][0]][Snake[0][1]] == -1)
		{
			map_0[Snake[0][0]][Snake[0][1]] = 0;
			pdEatFood = true;
			putfood();
			score += 10;
		}
	}
	return 0;
}
void csh()//初始化 
{
	srand((unsigned)time(NULL)); //设置种子为现在的时间
	Slength = 4;
	gotoxy(0, 0);
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 }; //清除光标 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	int x, y;
	Snake[0][0] = X / 2;
	Snake[0][1] = Y / 2;
	for (x = 0; x < X; x++) {
		map_0[x][0] = 1;
		map_0[x][Y - 1] = 1;
	}
	for (y = 1; y < Y - 1; y++) {
		map_0[0][y] = 1;
		map_0[X - 1][y] = 1;
	}
	for (x = 1; x < 4; x++) {	//初始化蛇的坐标 
		Snake[x][0] = Snake[0][0] + x;
		Snake[x][1] = Snake[0][1];
	}
	direction = UP;

}
void huaMap()//画地图 
{
	int x, y;
	for (x = 0; x < X; x++) {
		for (y = 0; y < Y; y++) {
			if (map_0[x][y] == 1) {
				printf("#");
			}
			if (map_0[x][y] == 0) {
				printf(" ");
			}
		}
		printf("\n");
	}
}
void huaSnake()//画蛇 
{
	int x;
	for (x = 0; x < Slength; x++)
	{
		gotoxy(Snake[x][0], Snake[x][1]);
		printf("@");
	}
}
void gotoxy(int i, int j)//移动光标 
{
	COORD position = { j,i };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
void move()
{
	int i;
	gotoxy(Snake[Slength - 1][0], Snake[Slength - 1][1]);//擦除尾巴
	printf(" ");
	for (i = Slength - 1; i > 0; i--)    //从尾巴开始，每一个点的位置等于它前面一个点的位置
	{
		Snake[i][0] = Snake[i - 1][0];
		Snake[i][1] = Snake[i - 1][1];
	}
	switch (direction)
	{
	case UP:
		Snake[0][0]--;
		break;
	case DOWN:
		Snake[0][0]++;
		break;
	case LEFT:
		Snake[0][1]--;
		break;
	case RIGHT:
		Snake[0][1]++;
		break;
	}
	if (pdEatFood) {
		Slength++;
		pdEatFood = false;
	}

}
void intokey()
{
	if (_kbhit() != 0)          //kbhit()函数 检查当前是否有键盘输入，若有则返回一个非0值，否则返回0
	{
		char in;
		while (!_kbhit() == 0)  //如果玩家输入了多个按键，以最后一个按键为准
			in = _getch();
		switch (in)
		{
		case 'w':
		case 'W':
			if (direction != DOWN)         //防止缩头
				direction = UP;
			break;
		case 's':
		case 'S':
			if (direction != UP)
				direction = DOWN;
			break;
		case 'a':
		case 'A':
			if (direction != RIGHT)
				direction = LEFT;
			break;
		case 'd':
		case 'D':
			if (direction != LEFT)
				direction = RIGHT;
			break;
		case 'p':
		case 'P':
			gotoxy(X, 0);
			system("pause");
			gotoxy(X, 0);
			printf("                   ");  //	消去下面的按任意键继续
			break;
		}
	}
}
int check(int ii, int jj) {// 检查是否能投放食物
	if (map_0[ii][jj] == 1)
		return 0;
	if (ii == 0 || jj == 0 || ii == X - 1 || jj == Y - 1)
		return 0;
	int i;
	for (i = 0; i < Slength; i++) {
		if (ii == Snake[i][0] && jj == Snake[i][1])
			return 0;
	}
	return 1;
}
void putfood()
{
	int i, j;
	do {
		i = rand() % X;
		j = rand() % Y;
	} while (check(i, j) == 0);
	map_0[i][j] = -1;
	gotoxy(i, j);
	printf("$");
}
bool gameover()
{
	bool isgameover = false;
	int sX, sY;
	sX = Snake[0][0], sY = Snake[0][1];
	if (sX == 0 || sX == X - 1 || sY == 0 || sY == Y - 1)
		isgameover = true;
	int i;
	for (i = 1; i < Slength; i++) {
		if (sX == Snake[i][0] && sY == Snake[i][1])
			isgameover = true;
	}
	return isgameover;
}
void dy_fs()
{
	gotoxy(X, 0);
	printf("(c)Geek------2018.1.22");
	gotoxy(X + 1, 0);
	printf("最终得分: %d", score);
}
