#include "ChessBoard.h"
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<Windows.h>
#include<queue>
#include<vector>
#include<conio.h>
using namespace std;
int ChessBoard::FindMine(int x, int y) {
	int cnt = 0;
	for (int d = 0; d < 8; d++) {
		int dx = x + Dx[d];
		int dy = y + Dy[d];
		if (JudgeIsOutMap(dx, dy) != true) {
			cnt += AnsBoard[dx][dy];
		}
	}
	return cnt;
}
ChessBoard::ChessBoard() {
	*this = ChessBoard(10, 10, 10);
	return;
}
ChessBoard::ChessBoard(int x, int y, int z) {
	Row = x, Col = y, Mine = z;
	MarkNum = 0;
	if (Mine >= Row * Col) throw Error(3);
	int Size = max(Row, Col);
	UserBoard = vector<vector<char>>(Size + 2, vector<char>(Size + 2, '.'));
	AnsBoard = vector<vector<int>>(Size + 2, vector<int>(Size + 2, 0));
	MarkBoard = vector<vector<int>>(Size + 2, vector<int>(Size + 2, 0));
	int cnt = Mine;
	srand(time(0));
	while (true) {
		if (cnt == 0) break;
		int x = rand() % Row + 1, y = rand() % Col + 1;
		if (JudgeIsOutMap(x, y) != true) {
			if (AnsBoard[x][y] == 0) {
				AnsBoard[x][y] = 1;
				cnt--;
			}
		}
		if (cnt == 0) break;
	}
	return;
}
bool ChessBoard::JudgeIsOutMap(int x, int y) const {
	return !(x >= 1 && x <= Row && y >= 1 && y <= Col);
}

void ChessBoard::Display() {
	for (int i = 1; i <= Row; i++) {
		for (int j = 1; j <= Col; j++) {
			printf("%c", UserBoard[i][j]);
		}
		printf("\n");
	}
	return;
}

void ChessBoard::AnsMapDisplay() {
	for (int i = 1; i <= Row; i++) {
		for (int j = 1; j <= Col; j++) {
			printf("%d", AnsBoard[i][j]);
		}
		printf("\n");
	}
	return;
}

void ChessBoard::AddPoint(int x, int y) {
	if (JudgeIsOutMap(x, y) == true) throw Error(1);
	if (MarkBoard[x][y] == 1) throw Error(2);
	if (AnsBoard[x][y] == 1) throw Error(0);
	MarkBoard[x][y] = 1;
	if (FindMine(x, y) == 0) {
		UserBoard[x][y] = ' ';
		for (int d = 0; d < 8; d++) {
			int dx = x + Dx[d];
			int dy = y + Dy[d];
			if (JudgeIsOutMap(dx, dy) != true) {
				if (AnsBoard[dx][dy] != 1) {
					if (MarkBoard[dx][dy] != 1) {
						Spread(dx, dy);
					}
				}
			}
		}
	}
	else {
		UserBoard[x][y] = '0' + FindMine(x, y);
	}
}

void ChessBoard::AddMarkPoint(int x, int y) {
	if (JudgeIsOutMap(x, y) == true) throw Error(1);
	if (MarkBoard[x][y] == 1) throw Error(2);
	if (MarkNum == Mine) throw Error(4);
	MarkBoard[x][y] = 1;
	UserBoard[x][y] = '@';
	MarkNum++;
}

void ChessBoard::DeleteMarkPoint(int x, int y) {
	if (JudgeIsOutMap(x, y) == true) throw Error(1);
	if (UserBoard[x][y] != '@') throw Error(5);
	if (MarkBoard[x][y] != 1) throw(6);
	MarkBoard[x][y] = 0;
	UserBoard[x][y] = '.';
	MarkNum--;
}

bool ChessBoard::DefiningWinning() {
	for (int i = 1; i <= Row; i++) {
		for (int j = 1; j <= Col; j++) {
			if (AnsBoard[i][j] == 1 && UserBoard[i][j] != '@') return false;
			if (AnsBoard[i][j] == 0 && UserBoard[i][j] == '@') return false;
		}
	}
	return true;
}

void ChessBoard::Spread(int x, int y) {
	if (JudgeIsOutMap(x, y) == true) return;
	if (MarkBoard[x][y] == 1) return;
	if (AnsBoard[x][y] == 1) return;
	MarkBoard[x][y] = 1;
	if (FindMine(x, y) == 0) {
		UserBoard[x][y] = ' ';
		for (int d = 0; d < 8; d++) {
			int dx = x + Dx[d];
			int dy = y + Dy[d];
			if (JudgeIsOutMap(dx, dy) != true) {
				if (AnsBoard[dx][dy] != 1) {
					if (MarkBoard[dx][dy] != 1) {
						Spread(dx, dy);
					}
				}
			}
		}
	}
	else {
		UserBoard[x][y] = '0' + FindMine(x, y);
	}
}