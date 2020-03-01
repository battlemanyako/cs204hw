#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cctype> // for isdigit()

using namespace std;

enum Way
{
	Right, Down, Left, Up, non
};

bool integerCheck(int row, int column, const int & rows, const int & columns) {
	if(row < rows &&
	   row > -2 &&
	   column < columns &&
	   column > -2) 
				{return true;}
	else {
		return false;
	}
}


void fillMatrix(ifstream & file, vector<vector<char>> & matrix, const int & rows, const int & columns) {
	// filling the matrix with the file's content;
	file.clear();
	file.seekg(0);
	string line;
	int row = 0, column = 0;
	char ch;
	while(getline(file,line)) {
		column = 0;
		istringstream input(line);
		while(input >> ch) {
			if(ch == 'x') {
				matrix[row][column] = 'x';
				column++;
			}
			else if(ch == 'o') {
				matrix[row][column] = 'o';
				column++;
			}
		}
		row++;
	}
}

void printMatrix(vector<vector<char>> & matrix, const int & rows, const int & columns) {
	for(int row=0; row < rows; row++) {
		for(int column=0; column < columns; column++) {
			cout << setw(4) << matrix[row][column];
		}
		cout << endl;
	}
}

void openFile(ifstream & inputFile, string & fileName) {
	cout << "Please enter file name: ";
	cin >> fileName;
	inputFile.open(fileName.c_str());
	while (inputFile.fail()) {
		cout << "Cannot find a file named "<< fileName << endl;
		cout << "Please enter file name: ";
		cin >> fileName;
		inputFile.open(fileName.c_str());
	}
}

bool charCheck(ifstream & inputFile) {
	// checking the file 
	string line;
	char ch;
	while(getline(inputFile,line)) {
		istringstream input(line);
		while(input >> ch) {
			if(!(ch == ' ' || ch == 'x' || ch == 'o')) {
				return false;
			}
		}
	}
	return true;
}

bool rowCheck(ifstream & inputFile, int & rows, int & columns) {
	string line;
	char ch;
	int firstCount = -1, tempCount = 0;
	inputFile.clear();
	inputFile.seekg(0);
	while(getline(inputFile,line)) {
		istringstream input(line);
		if (firstCount == -1) {
			rows++;
			firstCount = 0;
			while(input >> ch) {
				if(ch == 'x' || ch == 'o') {
				firstCount++;
				}
			}
			columns = firstCount;
		}
		else {
			rows++;
			while(input >> ch) {
				if(ch == 'x' || ch == 'o') {
				tempCount++;
				}
			}
			if(firstCount != tempCount) {
				return false;
			}
			tempCount = 0;
		}
	}
	return true;
}

int pathChecker(vector<int> & result,vector<vector<char>> & matrix, Way & Direction, int & row, int & column, const int & rows, const int & columns, int firstRow, int  firstColumn, bool & first, Way & last) {
	if(firstRow==row && firstColumn==column && first) {
	//	result.push_back(firstRow); 
	//	result.push_back(firstColumn); 
		return 2;
	} 
	first = true;
	// returns 0 if next element is 'o' or it's out of matrix's boundaries
	// returns 1 if next exists // never used return 1 since it's not needed
	// returns 2 if reached destination

	if(column + 1 < columns && matrix[row][column+1] == 'x' && last != Left) {
		result.push_back(row); 
		result.push_back(column);
		Direction = Right; column++, last = Right; 
		
		// recurssion
		int r = pathChecker(result, matrix, Direction, row, column, rows, columns, firstRow, firstColumn, first, last);
		if(r==2) {
			return 2;
		} 

		
	}
	if(row + 1 < rows && matrix[row+1][column] == 'x' && last != Up) {
		result.push_back(row); 
		result.push_back(column);
		Direction = Down; row++, last = Down;
		
		// recurssion
		int r = pathChecker(result, matrix, Direction, row, column, rows, columns, firstRow, firstColumn, first, last);
		if(r==2) {
			return 2;
		} 
	}
	if(column != 0 && matrix[row][column-1] == 'x' && last != Right) {
		result.push_back(row); 
		result.push_back(column);
		Direction = Left; column--, last = Left;

		// recurssion
		int r = pathChecker(result, matrix, Direction, row, column, rows, columns, firstRow, firstColumn, first, last);
		if(r==2) {
			return 2;
		} 
	}
	if(row != 0 && matrix[row-1][column] == 'x' && last != Down) {
		result.push_back(row); 
		result.push_back(column);
		Direction = Up; row--, last = Up;
		
		// recurssion
		int r = pathChecker(result, matrix, Direction, row, column, rows, columns, firstRow, firstColumn, first, last);
		if(r==2) {
			return 2;
		} 
	}
	return 0;
}


int main() {
	string fileName;
	ifstream inputFile;
	openFile(inputFile, fileName);
	int rows=0, columns=0;
	if(!charCheck(inputFile)) {
		cout << fileName << " includes invalid char(s)" << endl;
	}
	else if(!rowCheck(inputFile, rows, columns)) {
		cout << fileName <<" is invalid matrix, does not contain same amount of char each row!" << endl;
	}
	else {
		vector<vector<char>> mainMatrix(rows, vector<char>(columns));
		fillMatrix(inputFile, mainMatrix, rows, columns);
		printMatrix(mainMatrix, rows, columns);


		int row, column;
		do {
			cout << "Please enter starting coordinates, first row X then column Y: ";

			//string trashString, trashString2; // In order to get rid of wrong inputs // Not needed anymore

			while(!(cin >> row >> column) || !integerCheck(row,column,rows,columns)) {
			// while inputs are not integers or they are integers but out of index of the matrixes

				// if cin doesn't work because user didn't enter integer
				if(!cin.good()) {
					cin.clear();
					//cin >> trashString >> trashString2; // Doesn't work with inputs which has one integer and one string such as "three 3"
					cin.ignore(10000,'\n');
				}

				cout << "Invalid Coordinates" << endl << endl;
				cout << "Please enter starting coordinates, first row X then column Y: ";
			}
		
			if(row == -1 && column == -1) {
				cout << "Terminating..." << endl;
			} else if(mainMatrix[row][column] != 'x') {
				cout << "This cell is not occupied!" << endl << endl;
			} else {
				bool first = false; // how many times did the function called, it is initiated to understand when the function knows it reached it's destination
				Way Direction = Right, last = non;
				vector<int> results;
				int resCode = pathChecker(results, mainMatrix, Direction, row, column, rows, columns, row, column, first, last);
				if(resCode==2) {
					cout << "Found an enclosed area. The coordinates of the followed path:" << endl;
				}
				else if(resCode==0) {
					results.push_back(row); 
					results.push_back(column);
					cout << "Cannot found an enclosed area starting with given coordinate. The coordinates of the followed path:" << endl;
				}

				for(int i=0; i<results.size(); i+=2) {
					cout << results[i] << " " << results[i+1] << endl;
				}
				cout << endl;
			}
		} while (row != -1 || column != -1);
	}

	return 0;
}