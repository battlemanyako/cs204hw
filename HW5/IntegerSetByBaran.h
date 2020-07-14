#ifndef INTEGERSET_BY_BARAN_H
#define INTEGERSET_BY_BARAN_H

using namespace std;

class IntegerSet {
private:
	int size;
	int * set;
public:
	IntegerSet(); // Default constructor
	IntegerSet(int size); // Constructor with number of elements parameter
	IntegerSet(const IntegerSet & param); // Deep copy constructor
	~IntegerSet(); // Destructor

	// Getters
	int getSize() const;
	int getSetNum (int num) const;

	// Setters
	void setSize(int newSize);
	void setSet(int * newSet);
	void setSetNum(int index, int num);

	// Operator Overloading
	IntegerSet operator+(const IntegerSet & rhs) const;
	IntegerSet operator*(const IntegerSet & rhs) const;
	IntegerSet operator=(const IntegerSet & rhs);
	IntegerSet operator+=(const IntegerSet & rhs);
};

ostream & operator <<( ostream & out, const IntegerSet & rhs);
IntegerSet operator+(const IntegerSet & lhs, int num);
bool operator!=(const IntegerSet & lhs, const IntegerSet & rhs);
bool operator<=(const IntegerSet & lhs, const IntegerSet & rhs);
bool operator<=(const int & lhs, const IntegerSet & rhs);
#endif