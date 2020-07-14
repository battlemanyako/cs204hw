#include <iostream>
#include "DynamicIntStackByBaran.h"
using namespace std;



DynIntStack::DynIntStack() // constructor
{
	top = NULL; 
}

DynIntStack::DynIntStack(const DynIntStack & copy) {
	top = copy.createClone();
}

DynIntStack::~DynIntStack() {
	StackNode * topNode = top;
	while(topNode != NULL) {
		StackNode * tempNode = topNode->next;
		delete topNode;
		topNode = tempNode;
	}
}
 // MODIFIED FROM LinkedListExtraOper.cpp 
const DynIntStack & DynIntStack::operator = (const DynIntStack & stack) {
	if( this != &stack) {
		StackNode * topNode = top;
		while(topNode != NULL) {
			StackNode * tempNode = topNode->next;
			delete topNode;
			topNode = tempNode;
		}
		top = stack.createClone();
	}
	return *this;
}
// END OF LinkedListExtraOper.cpp 

void DynIntStack::push(int num)
{
	StackNode *newNode;

	// Allocate a new node & store Num
	newNode = new StackNode;
	newNode->value = num;

	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty())
	{
		top = newNode;
		newNode->next = NULL;
	}
	else	// Otherwise, insert NewNode before top
	{
		newNode->next = top;
		top = newNode;
	}
}

void DynIntStack::pop(int &num)
{
	StackNode *temp;

	if (isEmpty())
	{
		cout << "The stack is empty.\n";
	}
	else	// pop value off top of stack
	{
		num = top->value;
		temp = top->next;
		delete top;
		top = temp;
	}
}

bool DynIntStack::isEmpty(void)
{
	bool status;

	if (top == NULL)
		status = true;
	else
		status = false;

	return status;
}
