#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#ifndef CardList
#include "CardList.h"
#endif

using namespace std;

bool digitCheck(string s) { // my own code from hw2
	int l = s.length();
	for(int i=0; i< l; i++) {
		if(s.at(i) < '0' || s.at(i) > '9') {
			return false;
		}
	}
	return true;
}

void uploadFile(CardList & lists) {
	ifstream file;
	string fileName;
	cout << "Please enter file name: " ;
	cin >> fileName;
	file.open(fileName);
	if(file.fail()) {
		cout << "Cannot find a file named " << fileName << endl << endl ;
	} 
	else {
		cout << endl;
		string line;
		while(getline(file,line)) {
			istringstream input(line);
			string cc;
			int month, year;
			input >> cc >> month >> year;
			// add these to database
			lists.insertCard(cc, month, year);
		}
		file.close();
	}
	cout << endl;
}


int main() {
	string choice;
	CardList lists;
	do {
		cout << "1) Upload Card(s) from a File\n" <<
				"2) Display List Chronological\n" <<
				"3) Display List Reverse Chronological\n" <<
				"4) Card Search\n" <<
				"5) Bulk Delete\n" <<
				"6) Exit\n" <<
				"Please choose option from the menu: ";
		cin >> choice;
		if(choice == "1") {
			uploadFile(lists);
		}
		else if(choice == "2") {lists.displayListChronological();}
		else if(choice == "3") {lists.displayListReverseChronological();}
		else if(choice == "4") {
			cout << "Please enter the credit card number: ";
			string ccNum;
			cin >> ccNum;
			lists.cardSearch(ccNum);
		}
		else if(choice == "5") {
			cout << "Please enter month and year: ";
			string month, year;
			cin >> month >> year;
			if(digitCheck(month) && digitCheck(year) && (stoi(month) <=12 && stoi(month) >= 1) ) {
				cout << endl;
				lists.bulkDelete(stoi(month), stoi(year));
			}
			else {
				cout << "Invalid format!" << endl << endl;
			}
		}
		else if(choice == "6") {
			lists.deleteAll(); //All the nodes have been deleted!
			cout << "Terminating!!!" << endl;
		}
		else {
			cout << "Invalid operation!" << endl << endl;
		}

	} while(choice != "6");

	return 0;
}

