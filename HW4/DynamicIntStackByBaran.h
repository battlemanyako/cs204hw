struct StackNode
{
	int value;
	StackNode *next;

	StackNode() {}

	StackNode(int x, StackNode *node=NULL) {
		value = x;
		next = node;
	}
};

class DynIntStack
{
private:
	StackNode *top;

	StackNode * DynIntStack::createClone() const { // will return the top
		if(top == NULL) {
			return NULL;
		}
		StackNode * topClone = new StackNode(top->value, NULL);
		StackNode * ptr = top->next;
		StackNode * ptrClone = topClone;

		while(ptr != NULL) {
			ptrClone->next = new StackNode(ptr->value, NULL);
			ptr = ptr->next;
			ptrClone = ptrClone->next;
		}
		return topClone;
	};
public:
	DynIntStack(void);
	DynIntStack(const DynIntStack &); //copy constructor
	~DynIntStack(void); // deconstructor
	const DynIntStack & DynIntStack::operator = (const DynIntStack & stack);
	void push(int);
	void pop(int &);
	bool isEmpty(void);
};