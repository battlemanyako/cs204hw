#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#ifndef DynIntStack
#include "DynamicIntStackByBaran.h"
#endif

using namespace std;

bool DigitCheck(string s) { // my own function from hw2/hw3
	int l = s.length();
	for(int i=0; i< l; i++) {
		if(s.at(i) < '0' || s.at(i) > '9') {
			return false;
		}
	}
	return true;
}

void TakeInputs(string & rows, string & columns) {
	cout << "Enter the number of rows: ";
	cin >> rows;
	while(!DigitCheck(rows) || stoi(rows) < 3) { // input check
		cout << rows << " is not valid!" << endl
			 << "Enter the number of rows: ";
		cin >> rows;
	}
	cout << "Enter the number of columns: ";
	cin >> columns;
	while(!DigitCheck(columns) || stoi(columns) < 3) { // input check
		cout << columns << " is not valid!" << endl
			 << "Enter the number of columns: ";
		cin >> columns;
	}
}

void OpenFile(ifstream & file) {
	string fileName;
	cout << "Please enter file name: ";
	cin >> fileName;
	file.open(fileName.c_str());
	while(file.fail()) {
		cout << "Cannot open a file named " << fileName << endl
		     << "Please enter file name: ";
		cin >> fileName;
		file.open(fileName.c_str());
	}
}

/* Begin: code taken from matrixnoclass.cpp */
char ** CreateMatrix(ifstream & file, const string & rows, const string & columns) {
	// This function is heavily modified by me
	char ** matrix = new char* [stoi(rows)];
	for(int i=0; i< stoi(rows); i++) {
		string line;
		getline(file,line);
		matrix[i] = new char [stoi(columns)];
		for(int j=0; j< stoi(columns); j++) {
			char tempChar = line.at(j);
			matrix[i][j] = tempChar;
		}
	}
	file.close();
	return matrix;
}

void Print_table(char** values,  int char_rows, int char_cols) 
{ 
	int i, j; 
	for (i = 0; i < char_rows; i++) { 
		for (j= 0 ; j< char_cols ; j++) 
			cout << values[i][j]; 
		cout << endl;
	} 
} 
/* End: code taken from matrixnoclass.cpp */

void Fill(DynIntStack & stack, char ** & matrix, const int & r, const int & c, const char & filling) {
	matrix[r][c] = filling;
	stack.push(r);
	stack.push(c);
}


// Recursive Solution (It's not used)

//void RecursivePathfinder(DynIntStack & stack, char ** & matrix, int & r, int & c, const char & filling, const int & rows, const int & columns) {
//	if(r > 0 && matrix[r-1][c] != 'x' && matrix[r-1][c] != 'X' && matrix[r-1][c] != filling) { // North
//		r--;
//		Fill(stack, matrix, r, c, filling);
//		RecursivePathfinder(stack, matrix, r, c, filling, rows, columns);
//	}
//
//	if(c+1 < columns && matrix[r][c+1] != 'x' && matrix[r][c+1] != 'X' && matrix[r][c+1] != filling) { // East
//		c++;
//		Fill(stack, matrix, r, c, filling);
//		RecursivePathfinder(stack, matrix, r, c, filling, rows, columns);
//	}
//
//	if(r+1 < rows && matrix[r+1][c] != 'x' && matrix[r+1][c] != 'X' && matrix[r+1][c] != filling) { // South
//		r++;
//		Fill(stack, matrix, r, c, filling);
//		RecursivePathfinder(stack, matrix, r, c, filling, rows, columns);
//	}
//	
//	if(c > 0 && matrix[r][c-1] != 'x' && matrix[r][c-1] != 'X' && matrix[r][c-1] != filling) { // West
//		c--;
//		Fill(stack, matrix, r, c, filling);
//		RecursivePathfinder(stack, matrix, r, c, filling, rows, columns);
//	}
//	stack.pop(c);
//	stack.pop(r);
//}


bool Pathfinder(DynIntStack & stack, char ** & matrix, int & r, int & c, const char & filling, const int & rows, const int & columns) {
	int result =0;
	if(r > 0 && matrix[r-1][c] != 'x' && matrix[r-1][c] != 'X' && matrix[r-1][c] != filling) { // North
		r--;
		Fill(stack, matrix, r, c, filling);
		result=1;
	}

	else if(c-1 < columns && matrix[r][c+1] != 'x' && matrix[r][c+1] != 'X' && matrix[r][c+1] != filling) { // East
		c++;
		Fill(stack, matrix, r, c, filling);
		result=1;
	}

	else if(r-1 < rows && matrix[r+1][c] != 'x' && matrix[r+1][c] != 'X' && matrix[r+1][c] != filling) { // South
		r++;
		Fill(stack, matrix, r, c, filling);
		result=1;
	}
	
	else if(c > 0 && matrix[r][c-1] != 'x' && matrix[r][c-1] != 'X' && matrix[r][c-1] != filling) { // West
		c--;
		Fill(stack, matrix, r, c, filling);
		result=1;
	}
	return result;
}

int main() {
	string rows, columns;
	// take inputs
	TakeInputs(rows, columns);
	
	//open file
	ifstream file;
	OpenFile(file);	
	char ** matrix = CreateMatrix(file, rows, columns);

	cout << "Enter the starting point: ";
	string row, column;
	cin >> row >> column;
	while(!DigitCheck(row) || !DigitCheck(column) || stoi(row) >= stoi(rows) || stoi(column) >= stoi(columns)) {
		cout << "Invalid coordinate!" << endl
			 << "Enter the starting point: ";
		cin >> row >> column;
	}
	if(matrix[stoi(row)][stoi(column)] != ' ') { 
		cout << "Starting point is already occupied." << endl
			 << "Terminating..." << endl;
	}
	else {
		char filling;
		cout << "Enter the filling char: ";
		cin >> filling;
		while(filling == 'x' || filling == 'X') {
			cout << "Filling char is not valid!" << endl
				 << "Enter the filling char: ";
			cin >> filling;
		}

		int r = stoi(row), c = stoi(column);
		DynIntStack stack;
		
		Fill(stack, matrix, r, c, filling);
		for(int i=0; i<3; i++) { // Fill() function already pushes the r and c couple into the stack but I need to push it 3 more times so I can check for all 4 directions (read the while loop down below)
			stack.push(r);
			stack.push(c);
		}

		int rowsInt = stoi(rows), columnsInt = stoi(columns); // At this point, I was sick of using stoi() so I did what I should have done in the first place

		// I have created a soultion with recursive algorithm but I heard there might be some performance issues so It's here, not the solution since It needs some work on it
		
		//RecursivePathfinder(stack, matrix, r, c, filling, rowsInt, columnsInt);

		// My solution is the Pathfinder() function

		while(!stack.isEmpty()) { // Normally the stack would be empty when it checks the first available direction of the first (r,c) pair since the stack becomes empty but I pushed them 4 times so that this while loop can run for all directions of the first (r,c) pair
			if(!Pathfinder(stack, matrix, r, c, filling, rowsInt, columnsInt)) {
				stack.pop(c);
				stack.pop(r);
			}
		}
		cout <<endl;
		Print_table(matrix, stoi(rows), stoi(columns));
		
		for (int ii = 0; ii < rowsInt; ++ii) {
			delete[] matrix[ii];
		}
		delete[] matrix; 
	 		
	}
}