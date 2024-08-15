#pragma once
#pragma once
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<Windows.h>
#include<queue>
#include<vector>
#include<conio.h>
using namespace std;
class Error {
private:
	int cnt;
public:
	// Error typement
	//* 0 meet a boom
	//* 1 out of map
	//* 2 open two times
	//* 3 cannot download
	//* 4 too more marking
	//* 5 isn't a marking
	//
	Error(int x) {
		cnt = x;
	}
	string What() {
		switch (cnt) {
		case 0:
			return "boom";
		case 1:
			return "out line";
		case 2:
			return "open two times";
		case 3:
			return "download error";
		case 4:
			return "too more marking";
		case 5:
			return "isn't a marking";
		default:
			return "unknown error";
		}
	}
	int IWhat() {
		return cnt;
	}
};
class ChessBoard {
private:
	int Row;
	int Col;
	int Mine;
	int MarkNum;
	/*
	* '.' not open
	* '#' mine
	* '@' marking
	* '2' how many mine around
	* ' ' safe
	*/
	//showing to user
	vector<vector<char>> UserBoard;
	//answer
	vector<vector<int>> AnsBoard;
	//is visited
	vector<vector<int>> MarkBoard;
	int Dx[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };
	int Dy[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
	//Spread keyboard
	void Spread(int, int);
	//Check is the point out of the board
	bool JudgeIsOutMap(int, int) const;
public:
	//Find every mine around the point
	int FindMine(int, int);
	//define the board: 10 * 10 - 10
	ChessBoard();
	//define the board: x * y - z
	ChessBoard(int, int, int);
	//showing the board
	void Display();
	//showing the answer
	void AnsMapDisplay();
	//open point(x, y)
	void AddPoint(int, int);
	//set point(x, y) as flag
	void AddMarkPoint(int, int);
	//underset mark
	void DeleteMarkPoint(int, int);
	//check is it winning
	bool DefiningWinning();
	int IntRow() { return Row; }
	int IntCol() { return Col; }
	int IntMine() { return Mine; }
	vector<vector<int>> DisplayAnsBoard() { return AnsBoard; }
	vector<vector<char>> DisplayUserBoard() { return UserBoard; }
};
