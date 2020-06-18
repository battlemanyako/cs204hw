#include <iostream>
#include <string>
#include "CardList.h"

using namespace std;


int isBiggerCreditCard(string cc1, string cc2) {
	for(int i=0; i<16; i++) {
		if(cc1[i] > cc2[i]) {return 1;} // cc1 is bigger than cc2
		else if(cc1[i] < cc2[i]) {return 0;} // continue searching
	}
	return -1; // same credit cards 
}

bool ccCheck(string s) {
	int l = s.length();
	if(l!=16) {return false;}

	for(int i=0; i< l; i++) {
		if(s.at(i) < '0' || s.at(i) > '9') {
			return false;
		}
	}

	return true;
}

void clearMemory(creditCardNode * & ccHead) {
	int i=0;
	while(ccHead != NULL) {
		i++;
		cout << i << ") " << ccHead->creditCardNo << endl;
		creditCardNode * temp = ccHead;
		ccHead = ccHead->next;
		delete temp;
	}
}

void clearMemoryWithoutCount(creditCardNode * & ccHead) { // for delete all
	while(ccHead != NULL) {
		creditCardNode * temp = ccHead;
		ccHead = ccHead->next;
		delete temp;
	}
}

CardList::CardList() {
	head = NULL; 
	tail = NULL;
};
	//default constructor that creates an empty list 
void CardList::insertCard (string creditCardNo, int month, int year) {
	expirationNode * temp = head;
	if(temp == NULL) { // if it's empty
		creditCardNode * cCard = new creditCardNode(creditCardNo, NULL);
		temp = new expirationNode(month, year, cCard, NULL, NULL);
		head = temp;
		tail = temp;
		cout << creditCardNo << " " << month << " " << year << ": added to a new expiration date node" << endl;
	}
	else { // linked list is not empty (at least 1 node)
		if(head->year > year || (head->year == year && head->month > month)) { // if we need to add it to the beginning
			creditCardNode * tempCC = new creditCardNode(creditCardNo, NULL);
			expirationNode * node = new expirationNode(month, year, tempCC, head, NULL);
			head->prev = node;
			head = node;
			cout << creditCardNo << " " << month << " " << year << ": added to a new expiration date node" << endl;
		}
		else { 
			bool outerCheck = true; // boolean flag
			while(temp != NULL && outerCheck) {
				if(temp->year == year && temp->month == month) { // Add card to creditCardNode List
					// add it to CCNode ""TODO"
					creditCardNode * prevCC = NULL;
					creditCardNode * tempCardList = temp->cHead; 
					int res;
					bool check = true; // boolean flag
					while(tempCardList != NULL && check) {
						res = isBiggerCreditCard(tempCardList->creditCardNo, creditCardNo);
						if(res == 1) { // added before this node
							if(prevCC == NULL) { // must be the first node
								creditCardNode * tempCC = new creditCardNode(creditCardNo, tempCardList);
								temp->cHead = tempCC;
								cout << creditCardNo << " " << month << " " << year << ": inserted to an existing expiration date node" << endl;
							}
							else { // not the first node
								creditCardNode * tempCC = new creditCardNode(creditCardNo, tempCardList);
								prevCC ->next = tempCC;
								cout << creditCardNo << " " << month << " " << year << ": inserted to an existing expiration date node" << endl;
							}
							check = false;
						}
						else if(res == -1) { // Already inserted once / same card exists
							cout << creditCardNo << " " << month << " " << year << ": this card was already inserted" << endl;
							check = false;
						}
						if (check) {
							prevCC = tempCardList;
							tempCardList = tempCardList->next;
						}
					}
					if(tempCardList == NULL && res == 0) { // add at the end
						creditCardNode * tempCC = new creditCardNode(creditCardNo, NULL);
						prevCC->next = tempCC;
						cout << creditCardNo << " " << month << " " << year << ": inserted to an existing expiration date node" << endl;
					}

					outerCheck = false;
				}
				else if(temp->year > year || (temp->year == year && temp->month > month)) { // between two nodes
					creditCardNode * tempCC = new creditCardNode(creditCardNo, NULL);
					expirationNode * node = new expirationNode(month, year, tempCC, temp, temp->prev);
					(temp->prev)->next = node;
					temp->prev = node;
					cout << creditCardNo << " " << month << " " << year << ": added to a new expiration date node" << endl;
					outerCheck = false;
				}
						
				else if(temp->next == NULL) { // temp is the last node
					creditCardNode * tempCC = new creditCardNode(creditCardNo, NULL);
					expirationNode * node = new expirationNode(month, year, tempCC, NULL, temp);
					temp->next = node;
					tail = node;
					cout << creditCardNo << " " << month << " " << year << ": added to a new expiration date node" << endl;
					outerCheck = false;
				}
				if(outerCheck) {
					temp = temp->next; // Go the the next node
				}
			}
		}
	}
};
	//inserts a new card to the structure in sorted fashion 
void CardList::displayListChronological () {
	//displays entire structure in chronological order 
	expirationNode * temp = head;
	if(temp == NULL) {
		cout << endl << "List is empty!" << endl;
	}
	else {
		while(temp != NULL) {
			creditCardNode * tempCC = temp->cHead;
			cout << "Expiration Date: " << temp->month << " " << temp->year << endl;
			int i = 1;
			while(tempCC != NULL) {
				cout << i << ") "<< tempCC->creditCardNo << endl;

				i++;
				tempCC = tempCC->next;
			}
			cout << "-------------------" << endl;

			temp = temp->next;
		}
	}
	cout << endl;
};
void CardList::displayListReverseChronological () {
	//displays entire structure in reverse chronological order	
	expirationNode * temp = tail;
	if(temp == NULL) {
		cout << endl << "List is empty!" << endl;
	}
	else {
		while(temp != NULL) {
			creditCardNode * tempCC = temp->cHead;
			cout << "Expiration Date: " << temp->month << " " << temp->year << endl;
			int i = 1;
			while(tempCC != NULL) {
				cout << i << ") "<< tempCC->creditCardNo << endl;

				i++;
				tempCC = tempCC->next;
			}
			cout << "-------------------" << endl;

			temp = temp->prev;
		}
	}
	cout << endl;
}; 

void CardList::cardSearch (string creditCardNo) {
	//displays all of the occurrences of the given card number 
	if(!ccCheck(creditCardNo)) { // error message
		cout << "Invalid format!" << endl;
	}
	else { // do the search
		cout << endl;
		bool found = false;
		expirationNode * temp = head;

		while(temp != NULL) {
			creditCardNode * tempCC = temp->cHead;
			while(tempCC != NULL) {
				if(tempCC->creditCardNo == creditCardNo) {
					cout << "There exists a credit card given number " << creditCardNo << " with expiration date: " << temp->month << " " << temp->year << endl;
					found = true;
				}
				tempCC = tempCC->next;
			}

			temp = temp->next;
		}
		if(!found) {
			cout << "There is no credit card with given credit card number: " << creditCardNo << endl;
		}
	}
	cout << endl;
}; 
void CardList::bulkDelete (int month, int year) {
	//deletes all nodes up to and including given expiration date 
	expirationNode * temp = head;
	if(temp == NULL) {
		cout << "List is empty!" << endl;
	}
	else {
		expirationNode * toBeDelete;
		bool isFound = false;
		while(temp->next != NULL && (temp->year < year || (temp->year == year && temp->month <= month))) {
			cout << "Node with expiration date "<< temp->month << " " << temp->year << " and the following credit cards have been deleted!" << endl;
			clearMemory(temp->cHead);
			toBeDelete = temp;
			temp = temp->next;
			head = temp;
			temp->prev = NULL;
			delete toBeDelete;
			isFound = true;
			
		}
		if(temp->year < year || (temp->year == year && temp->month <= month)) { // check for last node
			cout << "Node with expiration date "<< temp->month << " " << temp->year << " and the following credit cards have been deleted!" << endl;
			clearMemory(temp->cHead);
			delete temp;
			isFound = true;
			head = NULL;
			tail = NULL;
		}
		if(!isFound) { // No deletion was done
			cout << "No node has been found so no node has been deleted!" << endl;
		}
	}
	cout << endl;
}; 
void CardList::deleteAll () {
	//deletes the entire structure 
	expirationNode * temp = head;
	if(temp != NULL) {
		expirationNode * toBeDelete;
		while(temp->next != NULL) {
			clearMemoryWithoutCount(temp->cHead);
			toBeDelete = temp;
			temp = temp->next;
			delete toBeDelete;
		}
		delete temp; // delete the last node
	}
	cout << "All the nodes have been deleted!" << endl;
};
