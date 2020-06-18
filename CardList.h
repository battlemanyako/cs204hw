#ifndef _CARDLIST_H
#define _CARDLIST_H

using namespace std;


int isBiggerCreditCard(string cc1, string cc2);

struct creditCardNode { 
	string creditCardNo; 
	creditCardNode * next; 

	// constructors come here 

	creditCardNode::creditCardNode() {}

	creditCardNode::creditCardNode(const string & cc, creditCardNode * node) 
		: creditCardNo(cc), next(node)
	{}
};

struct expirationNode { 
	int month, year; 
	creditCardNode * cHead; 
	expirationNode * next; 
	expirationNode * prev;
	
	// constructors come here 

	expirationNode::expirationNode() {}

	expirationNode::expirationNode(const int & monthInp, const int & yearInp, creditCardNode * head, expirationNode * nextExp, expirationNode * prevExp) 
		:	month(monthInp), year(yearInp), cHead(head), next(nextExp), prev(prevExp) 
	{}

};

class CardList { 
	public: CardList();
			//default constructor that creates an empty list 
		void insertCard (string creditCardNo, int month, int year);
			//inserts a new card to the structure in sorted fashion 
		void displayListChronological (); 
			//displays entire structure in chronological order 
		void displayListReverseChronological (); 
			//displays entire structure in reverse chronological order	
		void cardSearch (string creditCardNo); 
			//displays all of the occurrences of the given card number 
		void bulkDelete (int month, int year); 
			//deletes all nodes up to and including given expiration date 
		void deleteAll (); 
			//deletes the entire structure 
	private: 
		expirationNode * head; 
		expirationNode * tail;
// any helper functions you see necessary
};
#endif