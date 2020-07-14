#ifndef BOARDCLASS_PLAYERCLASS_BY_CIMENBARAN_26336_H
#define BOARDCLASS_PLAYERCLASS_BY_CIMENBARAN_26336_H

class Board
{
public:
	Board();
	void displayBoard();
	char getOwner(int i, int j);
	void setOwner(int i, int j, char ch);
	bool isFull();
	int countOwnedCells(char ch);

private:
	char theBoard[2][6];
};

class Player
{
public:
	Player(Board &theBoard, char theCh, int theDirection);
	void move(int cells);
	void claimOwnership();
	bool wins();
	int getRow();
	int getCol();

private:
	char ch;
	int i;
	int j;
	int direction;
	Board &myBoard;
};


#endif