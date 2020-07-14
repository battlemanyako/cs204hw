#include <iostream>
#include <string>

#ifndef INTEGERSET_BY_BARAN_H
#include "IntegerSetByBaran.h"
#endif

using namespace std;

// Public Funtions (Operator Overloadings)

ostream & operator <<( ostream & out, const IntegerSet & rhs) { // << Operator
	string res = "{";
	int size = rhs.getSize();
	int i=0;
	for(; i<size-1; i++) {
		res += to_string(rhs.getSetNum(i)) + ", ";
	}
	if(size > 0) {
		res += to_string(rhs.getSetNum(i));
	}
	res += + "}";
	out << res;
	return out;
};

IntegerSet operator+(const IntegerSet & lhs, int num) { // + Operator

	int size= lhs.getSize();
	bool check = false;
	// Check if num in lhs
	for(int j=0; j<size;j++) {
		if(lhs.getSetNum(j) == num) {
			check = true;
			j = size-1; // break the loop
		}
	}
	if(check) {
		return lhs;
	}
	else {
		IntegerSet tempSet;
		size++;
		int * temp = new int[size];
		int i=0;
		for(;i<size-1;i++) {
			temp[i] = lhs.getSetNum(i);
		}
		temp[i] = num;
		tempSet.setSet(temp);
		tempSet.setSize(size);
		return tempSet;
	}
}

bool operator!=(const IntegerSet & lhs, const IntegerSet & rhs) { // != Operator
	int lhsSize = lhs.getSize();
	int rhsSize = rhs.getSize();
	for(int i=0; i<lhsSize; i++) {
		int lhsNum = lhs.getSetNum(i);
		bool check = false;
		for(int j=0; j<rhsSize; j++) {
			if(lhsNum == rhs.getSetNum(j)) {
				check = true;
				j = rhsSize-1; // to break loop
			}
		}
		if(!check || (lhsSize != rhsSize)) {
			return true;
		}
	}
	return false;
}

bool operator<=(const IntegerSet & lhs, const IntegerSet & rhs) {
	int lhsSize = lhs.getSize();
	int rhsSize = rhs.getSize();
	for(int i=0; i<lhsSize; i++) {
		int lhsNum = lhs.getSetNum(i);
		bool check = false;
		for(int j=0; j<rhsSize; j++) {
			if(lhsNum == rhs.getSetNum(j)) {
				check = true;
				j = rhsSize-1; // to break loop
			}
		}
		if(!check || (lhsSize == rhsSize)) {
			return false;
		}
	}
	return true;
}

bool operator<=(const int & lhs, const IntegerSet & rhs) {
	int rhsSize = rhs.getSize();
	for(int i=0; i< rhsSize; i++) {
		if(lhs == rhs.getSetNum(i)) {
			return true;
		}
	}
	return false;
}

// Private Functions

IntegerSet::IntegerSet() { // Default constructor
	size=0;
	set= NULL;
}
IntegerSet::IntegerSet(int sizeInp) { // Constructor with number of elements parameter
	size = sizeInp;
	if(size >= 0) {
		set = new int[size];
		for(int i=0; i < size; i++) {
			set[i] = i;
		}
	}
	else {
		set = NULL;
	}
}
IntegerSet::IntegerSet(const IntegerSet & param) { // Deep copy constructor
	size = param.size;
	if(size >=0) {
		set = new int[size];
		for(int i=0; i<size; i++) {
			set[i] = param.set[i];
		}
	}
	else {
		set = NULL;
	}
}
IntegerSet::~IntegerSet() { // Destructor
	delete [] set;
	set = NULL;
}

// Getters
int IntegerSet::getSize() const {
	return size;
}
int IntegerSet::getSetNum (int num) const {
	return set[num];
}

// Setters
void IntegerSet::setSize(int newSize) {
	size = newSize;
}
void IntegerSet::setSet(int * newSet) {
	if(set != NULL) {
		delete [] set;
	}
	set = newSet;
}
void IntegerSet::setSetNum(int index, int num) {
	set[index] = num;
}

// Operator Overloading 

IntegerSet IntegerSet::operator+(const IntegerSet & rhs) const { // + Operator
	int newSize = rhs.getSize();
	int rhsSize = rhs.getSize();
	int lhsSize = size;
	int * newSet = new int [newSize];
	for(int j=0; j<newSize;j++) {
				newSet[j] = rhs.getSetNum(j);
			}
	for(int i=0; i<lhsSize; i++) {
		int tempNum = set[i];
		bool check= true;
		for(int j=0; j<rhsSize; j++) {
			if(rhs.getSetNum(j) == tempNum) {
				check = false;
				j= rhsSize; // to break loop
			}
		}
		if(check) {
			newSize++;
			int * tempSet = new int [newSize];
			for(int j=0; j<newSize-1;j++) {
				tempSet[j] = newSet[j];
			}
			tempSet[newSize-1] = tempNum;
			if(newSet != NULL) {
				delete [] newSet;
			}
			newSet = tempSet;
		}
	}
	IntegerSet tempIntSet;
	tempIntSet.setSet(newSet);
	tempIntSet.setSize(newSize);
	return tempIntSet;
}

IntegerSet IntegerSet::operator*(const IntegerSet & rhs) const { // * Operator
	int lhsSize = size;
	int rhsSize = rhs.getSize();
	int newSize = 0;
	int * newSet = NULL;
	for(int i=0; i<lhsSize; i++) {
		int tempNum = set[i];
		for(int j=0; j<rhsSize; j++) {
			int tempNum2 = rhs.getSetNum(j);
			if(tempNum == tempNum2) {
				newSize++;
				int * tempSet = new int [newSize];
				for(int k=0; k< newSize-1; k++) {
					tempSet[k] = newSet[k];
				}
				tempSet[newSize-1] = tempNum;
				if(newSet != NULL) {
					delete [] newSet;
				}
				newSet = tempSet;
				j = rhsSize;
			}
		}
	}
	IntegerSet intersection;
	intersection.setSize(newSize);
	intersection.setSet(newSet);
	return intersection;
}

IntegerSet IntegerSet::operator=(const IntegerSet & rhs) { // = Operator
	if(this != &rhs) {
		if(set != NULL) {
			delete [] set;
		}
		size = rhs.getSize();
		set = new int [size];
		for(int i=0; i<size; i++) {
			set[i] = rhs.getSetNum(i);
		}
	}
	return *this;
}

IntegerSet IntegerSet::operator+=(const IntegerSet & rhs) { // += Overloading
	int newSize = rhs.getSize();
	int rhsSize = rhs.getSize();
	int lhsSize = size;
	int * newSet = new int [newSize];
	for(int j=0; j<newSize;j++) {
				newSet[j] = rhs.getSetNum(j);
	}
	for(int i=0; i<lhsSize; i++) {
		int tempNum = set[i];
		bool check= true;
		for(int j=0; j<rhsSize; j++) {
			if(rhs.getSetNum(j) == tempNum) {
				check = false;
				j= rhsSize; // to break loop
			}
		}
		if(check) {
			newSize++;
			int * tempSet = new int [newSize];
			for(int j=0; j<newSize-1;j++) {
				tempSet[j] = newSet[j];
			}
			tempSet[newSize-1] = tempNum;
			if(newSet != NULL) {
				delete [] newSet;
			}
			newSet = tempSet;
		}
	}
	size = newSize;
	if(set != NULL) {
		delete [] set;
	}
	set = newSet;
	return *this;
}