#include "Queue.h"
using namespace std;
Queue::Queue()
{
	front = NULL;
	rear = NULL;
	quantity = 0;
}
Queue::~Queue()
{
	queueNode* nodeptr;
	while (!isEmpty())
	{
		nodeptr = front;
		front = front->next;
		delete nodeptr;
	}
}
bool Queue::isEmpty()
{
	bool status;
	if (quantity > 0)
		status = false;
	else
		status = true;
	return status;
}
void Queue::enqueue(int job_name)
{
	queueNode* newnode;
	newnode = new queueNode;
	newnode->value = job_name;
	if (isEmpty())
	{
		front = newnode;
		rear = newnode;
	}
	else
	{
		rear->next = newnode;
		rear = newnode;
	}
	quantity++;
}
void Queue::dequeue(int& job_name)
{
	queueNode* nodeptr;
	if (isEmpty())
	{
		cout << "The queue is empty." << endl;
	}
	else
	{
		job_name = front->value;
		nodeptr = front;
		front = front->next;
		delete nodeptr;
	}
	quantity--;
}
int Queue::get_quantity()
{
	return quantity;
}
