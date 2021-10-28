#include <iostream>
//#include "joblist.h"
using namespace std;
class Queue
{
private:
	struct queueNode
	{
		int value;
		queueNode* next;
	};
	queueNode* front;
	queueNode* rear;
	int quantity;
public:
	Queue();
	~Queue();
	bool isEmpty();
	void enqueue(int);
	void dequeue(int&);
	int get_quantity();
};
