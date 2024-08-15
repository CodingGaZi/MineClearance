#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<Windows.h>
#include<conio.h>
#include "ChessBoard.h"
namespace ColorWriting {
	void SetColor(int FroeColor, int BlackColor) {
		/*0 = 黑色   1 = 蓝色
		  2 = 绿色   3 = 湖蓝色
		  4 = 红色   5 = 紫色
		  6 = 黄色   7 = 白色
		  8 = 灰色   9 = 淡蓝色
		  10 = 淡绿色  11 = 淡浅绿
		  12 = 淡红色  13 = 淡紫色
		  14 = 淡黄色  15 = 亮白色
		  */
		SetConsoleTextAttribute(
			GetStdHandle(STD_OUTPUT_HANDLE),
			FroeColor + BlackColor * 0x10);
	}
	template<typename T>
	void ColorOut(T t, int FroeColor, int BackColor = 0) {
		/*0 = 黑色   1 = 蓝色
		  2 = 绿色   3 = 湖蓝色
		  4 = 红色   5 = 紫色
		  6 = 黄色   7 = 白色
		  8 = 灰色   9 = 淡蓝色
		  10 = 淡绿色  11 = 淡浅绿
		  12 = 淡红色  13 = 淡紫色
		  14 = 淡黄色  15 = 亮白色
		  */
		SetColor(FroeColor, BackColor);
		cout << t;
		SetColor(15, 0);
	}
}
namespace Read {
	inline static int IntRead() {
		int num = 0, f = 1; char ch = getchar();
		for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
		for (; isdigit(ch); ch = getchar()) num = (num << 1) + (num << 3) + ch - '0';
		return num * f;
	}
	inline static char CharRead() {
		return getchar();
	}
	inline static char* ArrayCharRead() {
		char cha[100010] = {};
		int id = 0;
		while (true) {
			char ch;
			ch = getchar();
			if (ch == ' ' || ch == '\n') break;
			else cha[id++] = ch;
		}
		return cha;
	}
}
using namespace std;
using namespace ColorWriting;
using namespace Read;
void FirstGraph(void) {
	char ch[][1000] = {
		"                          ",
		"   ***  ***     *** ***   ",
		"   *    * *       *  *    ",
		"   * ** ***      *   *    ",
		"   * *  * *     *    *    ",
		"   ***  * *     *** ***   ",
		"                          "
		//  "       Ga Zi Studio       "
	};
	for (int i = 0; i < 7; i++) {
		int len = strlen(ch[i]);
		for (int j = 0; j < len; j++) {
			if (ch[i][j] != '*') ColorOut(" ", 0, 1);
			else ColorOut(" ", 0, 4);
		}
		cout << endl;
	}
	ColorOut("       ", 0, 1);
	ColorOut("Ga", 3, 4);
	ColorOut(" ", 0, 4);
	ColorOut("Zi", 3, 4);
	ColorOut(" ", 0, 4);
	ColorOut("Studio", 3, 4);
	ColorOut("       ", 0, 1);
	cout << endl;
	cout << "Minesweeper 1.0 \n";
	Sleep(2000);
	system("CLS");
}
void Meum() {
	ColorOut("***************************\n", 3, 0);
	ColorOut("****    Minesweeper    ****\n", 3, 0);
	ColorOut("****     1. primary    ****\n", 3, 0);
	ColorOut("****     2. junior     ****\n", 3, 0);
	ColorOut("***      3. custom     ****\n", 3, 0);
	ColorOut("****     0. exit       ****\n", 3, 0);
	ColorOut("***************************\n", 3, 0);
	ColorOut("Please input you chouse>> ", 2, 0);
}
void Exit() {
	ColorOut("Thank you for playing!\n", 2, 0);
	ColorOut("Goodbye!\n", 2, 0);
	Sleep(1000);
	exit(0);
}
void Lose(ChessBoard& board) {
	ColorOut("Oh no you hit a boom!\n", 4, 0);
	ColorOut("YOU DIED!\n", 4, 0);
	ColorOut("Please try a again!\n", 4, 0);
	vector<vector<int>> Ans = board.DisplayAnsBoard();
	for (int i = 1; i <= board.IntRow(); i++) {
		for (int j = 1; j <= board.IntCol(); j++) {
			if (Ans[i][j] == 1) {
				ColorOut("#", 4, 0);
			}
			else {
				if (board.FindMine(i, j) == 0) {
					ColorOut(" ", 3, 0);
				}
				else ColorOut(char('0' + board.FindMine(i, j)), 3, 0);
			}
		}
		printf("\n");
	}
	ColorOut("Press ANY keys to Meum. \n", 4, 0);
	_getch();
	return;
}
void Winning(ChessBoard& board) {
	ColorOut("Hooery! You find every boom!\n", 2, 0);
	ColorOut("Good!\n", 2, 0);
	vector<vector<int>> Ans = board.DisplayAnsBoard();
	for (int i = 1; i <= board.IntRow(); i++) {
		for (int j = 1; j <= board.IntCol(); j++) {
			if (Ans[i][j] == 1) {
				ColorOut("#", 4, 0);
			}
			else {
				if (board.FindMine(i, j) == 0) {
					ColorOut(" ", 3, 0);
				}
				else ColorOut(char('0' + board.FindMine(i, j)), 3, 0);
			}
		}
		printf("\n");
	}
	ColorOut("Press ANY keys to Meum. \n", 4, 0);
	_getch();
	return;
}
void Play(int x, int y, int z) {
	ChessBoard board(x, y, z);
	while (true) {
		board.Display();
		int x, y, type;
		//colortry
		SetColor(2, 0);
		printf("%d * %d --- minemark : %d\n", board.IntRow(), board.IntCol(), board.IntMine());
		SetColor(15, 0);
		//end colortry
		ColorOut("Marking: . nothing | # mine | @ marking\n", 2, 0);
		ColorOut("Typement: 1 open  2 mark 3 undermark 0 exit\n", 2, 0);
		ColorOut("                 Row   Col  type\n", 2, 0);
		ColorOut("Please input>>>> ", 2, 0);
		x = Read::IntRead(), y = Read::IntRead(), type = Read::IntRead();
		try {
			if (type == 1) {
				board.AddPoint(x, y);
			}
			else if (type == 2) {
				board.AddMarkPoint(x, y);
			}
			else if (type == 0) {
				return;
			}
			else {
				board.DeleteMarkPoint(x, y);
			}
			if (board.DefiningWinning() == true) {
				Winning(board);
				break;
			}
		}
		catch (Error& e) {
			if (e.IWhat() == 0) {
				Lose(board);
				return;
			}
			else if (e.IWhat() == 1) {
				ColorOut("Point Error. Please input again.\n", 4, 0);
				Sleep(1000);
				system("CLS");
				continue;
			}
			else if (e.IWhat() == 2) {
				ColorOut("Open Point two times. Please input again.\n", 4, 0);
				Sleep(1000);
				system("CLS");
				continue;
			}
			else if (e.IWhat() == 3) {
				ColorOut("Cannot built map.\n", 4, 0);
				Sleep(1000);
				system("CLS");
				return;
			}
			else if (e.IWhat() == 4) {
				ColorOut("Not enough marking.\n", 4, 0);
				Sleep(1000);
				system("CLS");
				continue;
			}
			else if (e.IWhat() == 5) {
				ColorOut("Point isn't a marking.\n", 4, 0);
				Sleep(1000);
				system("CLS");
				continue;
			}
			else {
				ColorOut("Unknow error", 4, 0);
				Sleep(1000);
				system("CLS");
				return;
			}
		}
		Sleep(1000);
		system("CLS");
	}
	return;
}
int main() {
	FirstGraph();
	while (true) {
		Meum();
#if 1
		int x = Read::IntRead();
		if (x == 1) {
			Sleep(1000);
			system("CLS");
			Play(10, 10, 10);
		}
		else if (x == 2) {
			Sleep(1000);
			system("CLS");
			Play(15, 15, 40);
		}
		else if (x == 3) {
			int x, y, z;
			ColorOut("Please input Length>> ", 2, 0);
			x = Read::IntRead();
			ColorOut("Please input Width>> ", 2, 0);
			y = Read::IntRead();
			ColorOut("Please input Number of Mine>> ", 2, 0);
			z = Read::IntRead();
			if (x * y <= z) {
				ColorOut("Cannot built map.\n", 4, 0);
				Sleep(1000);
				system("CLS");
				continue;
			}
			system("CLS");
			Play(x, y, z);
		}
		else if (x == 0) {
			Exit();
		}
		else {
			ColorOut("Chosen error. Please input again.\n", 4, 0);
			Sleep(1000);
		}
		system("CLS");
#endif
#if 0
		ChessBoard x(20, 20, 20);
		Winning(x);
		_getch();
		system("CLS");
#endif
	}
}