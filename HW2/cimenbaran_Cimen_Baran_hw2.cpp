#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

bool digitCheck(string s) {
	int l = s.length();
	for(int i=0; i< l; i++) {
		if(s.at(i) < '0' || s.at(i) > '9') {
			return false;
		}
	}
	return true;
}

struct node {
	int months, years;
	vector<string> cards;
	node* next;

	node::node() {
		vector<string> cards;
		node* next = NULL;
	};

	node::node(int month, int year, string ccNumber, node* next) {
		node::months = month;
		node::years = year;
		node::cards.push_back(ccNumber);
		node::next = next;
	};
};

void DisplayList (node * head) {
	node * ptr = head;
	if(ptr == NULL) {
		cout << "List is empty!" << endl;
	}
    while (ptr != NULL) 
	{
		cout << "Expiration Date: " << ptr->months << " " <<ptr->years << endl;
		int size = ptr->cards.size();
		for(int i=1; i< size+1; i++) {
			cout << i << ") " << ptr->cards.at(i-1) << endl;
		}
		cout << "-------------------" << endl << endl;
		ptr = ptr->next;
	}
	cout << endl;
}

bool ccSearch (node * head, string cc) {
	node * ptr = head;
    while (ptr != NULL) 
	{
		
		int size = ptr->cards.size();
		for(int i=0; i< size; i++) {
			if(ptr->cards.at(i) == cc) {
				cout << "There exists a credit card given number " << cc << " with expiration date: " << ptr->months << " " << ptr->years << endl << endl << endl;
				return true; // No need to look further more
			}
		}
		ptr = ptr->next;
	}
	return false;
}

node * findNode(node * head, int month, int year) {
	node * ptr = head;
    while (ptr != NULL) 
	{
		if(ptr->months == month && ptr->years == year) {
			return ptr;
		}
		ptr = ptr->next;
	}
	// When Couldn't find
	return NULL;
}

node * addNewNode(node * head, int month, int year, string cc) {
    node *  ptr = head; 

    if (  head == NULL || head->years > year || (head->years == year && head->months > month)  )        
    {   
		return new node(month, year, cc, head);    
    }

    node * prev; //to point to the previous node
	while (ptr != NULL && (ptr->years < year || (ptr->years == year && ptr->months < month)))	
    {   
		prev = ptr;     
		ptr = ptr->next;
    } 

    //now insert node with month-year and credit card
    prev->next = new node(month, year, cc, ptr);   

    return head;
}

void DeleteOneNode(node * & head, int month, int year) {
	node * ptr;
		
	if(head == NULL) {
			cout << "There is no node with expiration date " << month << " " << year << ", nothing deleted!" << endl << endl;
	}
	else if (head->months == month && head->years == year) {
		// If it is the head of the linked list
		node * deletedNode = head;
		// Going to delete deletedNode for memory

		cout << "Node with expiration date " << month << " " << year << " and the following credit cards have been deleted!" << endl;
		int size = deletedNode->cards.size();
		for(int i=1; i< size+1; i++) {
			cout << i << ") " << deletedNode->cards.at(i-1) << endl;
		}
		cout << endl;
		
		head = head->next;
		delete deletedNode;
	}
	else {
		// If it is at the middle or at the end or doesn't exist
		ptr = head;
		while (ptr->next == NULL || !(ptr->next->months == month && ptr->next->years == year)) {
			ptr = ptr->next;
			if(ptr == NULL) {
				break;
			}
		}

		if(ptr == NULL) {
			cout << "There is no node with expiration date " << month << " " << year << ", nothing deleted!" << endl << endl;
		} else {
			node * deletedNode = ptr->next;
			// Going to delete deletedNode for memory

			cout << "Node with expiration date " << month << " " << year << " and the following credit cards have been deleted!" << endl;
			int size = deletedNode->cards.size();
			for(int i=1; i< size+1; i++) {
				cout << i << ") " << deletedNode->cards.at(i-1) << endl;
			}

			cout << endl;
			ptr->next = ptr->next->next;
			delete deletedNode;
			
		}
	}
}

void clearMemory(node * & head) {
	if(head != NULL) {
		node * next = head->next;
		while(head->next != NULL) {
			delete head;
			head = next;
			next = head->next;
		}
		delete head;
	}
}

int main() {
	ifstream file;
	string fileName;
	cout << "Please enter file name: " ;
	cin >> fileName;
	file.open(fileName);
	while(file.fail()) {
		cout << "Cannot find a file named " << fileName << endl;
		cout << "Please enter file name: " ;
		cin >> fileName;
		file.open(fileName);
	}
	node *head = NULL;
	string line;
	while(getline(file,line)) {
		string cc;
		int month, year;
		istringstream inp(line);
		inp >> cc >> month >> year;
		node * location = findNode(head, month, year);
		if(location != NULL) {
			cout << "Node with expiration date "<< month << " " << year << " already exists" << endl;
			// No need to add new node, just add the credit card number
			location->cards.push_back(cc);
		}
		else {
			cout << "New node is created with expiration date: " << month << " " << year << endl;
			// Add new node
			head = addNewNode(head, month, year, cc);
		}
		cout << "Credit card " << cc << " added to node " << month << " " << year << endl;
		cout << "***************" << endl << endl;
	}
	// finished creating linked list
	int choice;
	do{
		cout << "1)Display List "<< endl 
			 << "2)Card Search via Credit Number" << endl
			 << "3)Delete Card with respect to Expiration Date" << endl
			 << "4)Exit" << endl << endl
			 << "Please choose option from the menu: ";
		cin >> choice;
		cout << endl;

		if(choice == 1) {
			DisplayList(head);
		}
		else if(choice == 2) {
			cout << "Please enter the credit card number: ";
			string ccNum;
			cin >> ccNum;
			while(ccNum.length() != 16 || !digitCheck(ccNum)) {
				cout << "Invalid format!" << endl;
				cout << "Please enter the credit card number: ";	
				cin >> ccNum;
			}
			if(!ccSearch(head, ccNum)) {
				cout << "There is no credit card with given credit card number: " << ccNum << endl << endl;
			}
			// No need for else since ccSearch() function already prints the result

		}
		else if(choice == 3) {
			string deleteMonth, deleteYear;
			cout << "Please enter month and year: ";
			cin >> deleteMonth >> deleteYear;
			while( !digitCheck(deleteMonth) || !digitCheck(deleteYear) || stoi(deleteMonth) < 1 || stoi(deleteMonth) > 12) {
				cout << "Invalid Date!" << endl;
				cout << "Please enter month and year: ";
				cin >> deleteMonth >> deleteYear;
			}
			DeleteOneNode(head, stoi(deleteMonth), stoi(deleteYear));
		}
		else if(choice == 4) {
			cout << "Terminating!!!" << endl;
		}
		else {
			cout << "No such option!" << endl << endl;
		}
	} while (choice != 4);
	
	clearMemory(head);

	return 0;
}