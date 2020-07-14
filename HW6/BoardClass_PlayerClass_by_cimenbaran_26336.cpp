#include <iostream>

#ifndef BOARDCLASS_PLAYERCLASS_BY_CIMENBARAN_26336_H
#include "BoardClass_PlayerClass_by_cimenbaran_26336.h"
#endif

using namespace std;

// Board Class Member Functions

Board::Board() {
	for(int i=0; i<2; i++) {
		for(int j=0; j<6; j++) {
			theBoard[i][j] = '-';
		}
	}
}

void Board::displayBoard() {
	for(int i=0; i<2; i++) {
		for(int j=0; j<6; j++) {
			cout << theBoard[i][j] << " ";
		}
		cout << endl;
	}
}

char Board::getOwner(int i, int j) {
	return theBoard[i][j];
}

void Board::setOwner(int i, int j, char ch) {
	theBoard[i][j] = ch;
}

bool Board::isFull() {
	for(int i=0; i<2; i++) {
		for(int j=0; j<6; j++) {
			if(theBoard[i][j] == '-') {
				return false;
			}
		}
	}
	return true;
}

int Board::countOwnedCells(char ch) {
	int count=0;
	for(int i=0; i<2; i++) {
		for(int j=0; j<6; j++) {
			if(theBoard[i][j] == ch) {
				count++;
			}
		}
	}
	return count;
}

// Player Class Member Functions

Player::Player(Board &theBoard, char theCh, int theDirection) 
	: myBoard(theBoard), ch(theCh), direction(theDirection), i(0), j(0)
	{}


void Player::move(int cells) {
	int count = cells;
	if(direction == 1) {
		while(count !=0) {
			while(count !=0 && i==1) {
				if (j==0) {
					count--;
					i--;
				}
				else {
					count--;
					j--;
				}
			}
			while(count !=0 && i==0) {
				if (j==5) {
					count--;
					i++;
				}
				else {
					count--;
					j++;
				}
			}
			
		}
	}
	else {
		while(count !=0) {
			while(count !=0 && i==1) {
				if (j==5) {
					count--;
					i--;
				}
				else {
					count--;
					j++;
				}
			}
			while(count !=0 && i==0) {
				if (j==0) {
					count--;
					i++;
				}
				else {
					count--;
					j--;
				}
			}
			
		}
	}
}

void Player::claimOwnership() {
	if(myBoard.getOwner(i,j) == '-') {
		myBoard.setOwner(i,j,ch);
	}
}

bool Player::wins() {
	if(myBoard.countOwnedCells(ch) > 6) {
		return true;
	}
	else {
		return false;
	}
}

int Player::getRow() {
	return i;
}

int Player::getCol() {
	return j;
}