#include "list.h"
#include "Queue.h"
#include "joblist.h"
using namespace std;

void list::displaylist() const // displays the content of the list
{
	node* nodeptr;
	nodeptr = head;
	while (nodeptr)
	{
		cout << nodeptr->partition_memory_size << endl;
		/*if (nodeptr->status == 1)
			cout << " OCcupied";
		if (nodeptr->status == 0)
			cout << " free";*/
		nodeptr = nodeptr->next;
	}
}
// memorySize == the one from the array tht we stored earlier from the text file
void list::appendlist(int memorySize, int memory_number)
{
	node* nodeptr; // to travel
	node* newnode; // to create a node
	newnode = new node; // allocating space/memory for tht node
	newnode->partition_memory_size = memorySize; // assigning value to tht node
	newnode->status = 0; // setting the intial memory as free
	newnode->job_processing_time = NULL;
	newnode->next = NULL; // to end the list
	newnode->memory_num = memory_number + 1;
	if (!head)
		head = newnode;
	else
	{
		nodeptr = head;
		while (nodeptr->next)
		{
			nodeptr = nodeptr->next;
		}
		nodeptr->next = newnode;
	}
}

void list::appendlist1(int memsize)	//append memory partition for dynamic
{
	node* nodeptr;
	node* newnode;
	newnode = new node;
	newnode->partition_memory_size = memsize;
	newnode->status = 0;
	newnode->job_processing_time = NULL;
	newnode->next = NULL;

	if (!head)
		head = newnode;
	else
	{
		nodeptr = head;
		while (nodeptr->next)
		{
			nodeptr = nodeptr->next;
		}
		nodeptr->next = newnode;
	}
}

void list::dynjob(int jobsize, int arrival, int process, int jobnum, int& status, int& value, int bestfit, int worstfit, int& exfrag)	//asign job in dynamic memory partition first fit
{
	node* nodeptr = head;
	node* pointer = head;
	node* newnode;
	newnode = new node;
	newnode->partition_memory_size = NULL;
	newnode->status = 0;
	newnode->job_processing_time = NULL;
	int balance = 0, frag = 0;
	while (nodeptr)
	{
		if (jobsize <= nodeptr->partition_memory_size && nodeptr->status == 0)
		{
			balance = nodeptr->partition_memory_size - jobsize;
			nodeptr->partition_memory_size = jobsize;
			nodeptr->job_dlm_mem_slot = jobnum;
			nodeptr->status = 1;
			nodeptr->job_processing_time = arrival + process;
			cout << "At t=" << arrival << ", job number " << jobnum << " entered with size of " << jobsize << endl;
			system("PAUSE"); cout << "\n";
			newnode->partition_memory_size = balance;
			if (nodeptr->next != NULL)
			{
				newnode->next = nodeptr->next;
				nodeptr->next = newnode;
			}
			else
				appendlist1(balance);

			if (bestfit == 1)
			{
				dynsortbest();
			}
			if (worstfit == 1)
			{
				dynsortworst();
			}
			break;
		}
		else
			nodeptr = nodeptr->next;
	}
	if (nodeptr == NULL)
	{
		cout << "At t=" << arrival << " job number " << jobnum << " sized of " << jobsize << " entered queue." << endl;
		system("PAUSE"); cout << "\n";
		value = jobnum;
		status = 1;
		while (pointer)
		{
			if (pointer->status == 0)
			{
				frag = frag + pointer->partition_memory_size;
			}
			pointer = pointer->next;
		}
		if (frag >= jobsize)
			exfrag = frag;
	}
}

void list::dynjob1(int jobsize, int arrival, int process, int jobnum, int& status, int& value, int bestfit, int worstfit, int& exfrag)	//asign queue job in dynamic memory partition first fit
{
	node* nodeptr = head;
	node* pointer = head;
	node* newnode;
	newnode = new node;
	newnode->partition_memory_size = NULL;
	newnode->status = 0;
	newnode->job_processing_time = NULL;
	int balance = 0, frag = 0;
	while (nodeptr)
	{
		if (jobsize <= nodeptr->partition_memory_size && nodeptr->status == 0)
		{

			balance = nodeptr->partition_memory_size - jobsize;
			nodeptr->partition_memory_size = jobsize;
			nodeptr->job_dlm_mem_slot = jobnum;
			nodeptr->status = 1;
			nodeptr->job_processing_time = arrival + process;
			cout << "At t=" << arrival << ", from queue, job number " << jobnum << " entered with size of " << jobsize << endl;
			system("PAUSE"); cout << "\n";
			//cout << "Job process time " << nodeptr->job_processing_time << endl;
			newnode->partition_memory_size = balance;
			if (nodeptr->next != NULL)
			{
				newnode->next = nodeptr->next;
				nodeptr->next = newnode;
			}
			else
				appendlist1(balance);
			//dynmerge();
			if (bestfit == 1)
				dynsortbest();
			if (worstfit == 1)
				dynsortworst();
			break;
		}
		else
			nodeptr = nodeptr->next;
	}
	if (nodeptr == NULL)
	{
		value = jobnum;
		status = 1;
		while (pointer)
		{
			if (pointer->status == 0)
			{
				frag = frag + pointer->partition_memory_size;
			}
			pointer = pointer->next;
		}
		if (frag >= jobsize)
			exfrag = frag;
	}
}

void list::dynsortbest()
{
	node* nodeptr;
	node* pointer;
	int temp, temp1, temp2, temp3;

	for (nodeptr = head; nodeptr->next != NULL; nodeptr = nodeptr->next)
	{
		for (pointer = nodeptr->next; pointer != NULL; pointer = pointer->next)
		{
			if (nodeptr->partition_memory_size > pointer->partition_memory_size)
			{
				temp = nodeptr->partition_memory_size;
				temp1 = nodeptr->job_processing_time;
				temp2 = nodeptr->status;
				temp3 = nodeptr->job_dlm_mem_slot;

				nodeptr->partition_memory_size = pointer->partition_memory_size;
				nodeptr->job_processing_time = pointer->job_processing_time;
				nodeptr->status = pointer->status;
				nodeptr->job_dlm_mem_slot = pointer->job_dlm_mem_slot;

				pointer->partition_memory_size = temp;
				pointer->job_processing_time = temp1;
				pointer->status = temp2;
				pointer->job_dlm_mem_slot = temp3;
			}
		}
	}
}

void list::dynsortworst()
{
	node* nodeptr;
	node* pointer;
	int temp, temp1, temp2, temp3;

	for (nodeptr = head; nodeptr->next != NULL; nodeptr = nodeptr->next)
	{
		for (pointer = nodeptr->next; pointer != NULL; pointer = pointer->next)
		{
			if (nodeptr->partition_memory_size < pointer->partition_memory_size)
			{
				temp = nodeptr->partition_memory_size;
				temp1 = nodeptr->job_processing_time;
				temp2 = nodeptr->status;
				temp3 = nodeptr->job_dlm_mem_slot;

				nodeptr->partition_memory_size = pointer->partition_memory_size;
				nodeptr->job_processing_time = pointer->job_processing_time;
				nodeptr->status = pointer->status;
				nodeptr->job_dlm_mem_slot = pointer->job_dlm_mem_slot;

				pointer->partition_memory_size = temp;
				pointer->job_processing_time = temp1;
				pointer->status = temp2;
				pointer->job_dlm_mem_slot = temp3;
			}
		}
	}
}

void list::dyndeparture(int arrival, int& newarr, int& value, bool& bo, int bestfit, int worstfit) // first fit departure of dynamic parition
{
	node* nodeptr = head;
	node* pointer = head;
	node* point = head;
	int x = 0, y = 0, a = 0;
	while (nodeptr)
	{
		if (nodeptr->job_processing_time > 0 && nodeptr->job_processing_time <= arrival)
		{
			newarr = nodeptr->job_processing_time;
			break;
		}
		else
			nodeptr = nodeptr->next;
	}
	if (nodeptr == NULL)
		bo = false;
	if (bo != false)
	{
		while (pointer)
		{
			if (pointer->job_processing_time > 0 && pointer->job_processing_time <= arrival)
			{
				if (pointer->job_processing_time <= newarr)
				{
					newarr = pointer->job_processing_time;
					x = y;
				}
			}
			pointer = pointer->next;
			y++;
		}
		while (point)
		{
			if (a == x)
			{
				value = 1;
				point->status = 0;
				cout << "At t=" << newarr << " job number " << point->job_dlm_mem_slot << " sized " << point->partition_memory_size << " leaves.\n" << endl;
				system("PAUSE"); cout << "\n";
				point->job_processing_time = 0;
				bo = true;
				dynmerge();
				if (bestfit == 1)
					dynsortbest();
				if (worstfit == 1)
					dynsortworst();
				break;
			}
			else
				point = point->next;
			a++;
		}
	}
}

void list::dynmerge()	// first fit dynamic merge spaces of side by side
{
	node* nodeptr = head;
	node* nextnode = nodeptr->next;
	node* temp;

	while (nodeptr)
	{
		if (nextnode == NULL)
			break;
		if (nodeptr->status == 0 && nextnode->status == 0)
		{
			nodeptr->partition_memory_size = nodeptr->partition_memory_size + nextnode->partition_memory_size;
			nodeptr->next = nextnode->next;
			temp = nextnode;
			delete nextnode;
			if (nodeptr->next == NULL)
				break;
			nextnode = nodeptr->next;
		}
		else
		{
			nodeptr = nextnode;
			if (nodeptr->next == NULL)
				break;
			nextnode = nextnode->next;
		}
	}
}


// this function be used as the sorter function (ascending mode) for best fit i think,..... 
void list::sortedlist(int memorySize, int memory_number)
{
	node* nodeptr;
	node* previousnode;
	node* newnode;
	newnode = new node;
	newnode->partition_memory_size = memorySize;
	newnode->status = 0;
	newnode->job_processing_time = NULL;
	newnode->next = NULL;
	newnode->memory_num = memory_number + 1;
	//newnode->status = 0;
	if (!head)
	{
		head = newnode;
		newnode->next = NULL;
	}
	else
	{
		nodeptr = head;
		previousnode = NULL;
		while ((nodeptr != NULL) && (nodeptr->partition_memory_size < memorySize))
		{
			previousnode = nodeptr;
			nodeptr = nodeptr->next;
		}
		if (previousnode == NULL)
		{
			head = newnode;
			newnode->next = nodeptr;
		}
		else
		{
			previousnode->next = newnode;
			newnode->next = nodeptr;
		}
	}
}
// we dont need delete function now, but will keep it for now...
void list::deletelist(int memorySize)
{
	node* nodeptr = NULL;
	node* previousnode = NULL;
	if (!head)
	{
		cout << "\nThere's nothing in this list!!" << endl;
		return;
	}
	if (head->partition_memory_size == memorySize)
	{
		nodeptr = head->next;
		delete head;
		head = nodeptr;
	}
	else
	{
		nodeptr = head;
		while (nodeptr != NULL && nodeptr->partition_memory_size != memorySize)
		{
			previousnode = nodeptr;
			nodeptr = nodeptr->next;
		}
		if (nodeptr)
		{
			previousnode->next = nodeptr->next;
			delete nodeptr;
		}
	}
}
// will display the memory size of the choosen block by the job 
int list::show_mem_size(int nth_block)
{
	node* nodeptr;
	node* keeper = head; // keeper will save the memory location tht the job has choosen to stay 
	nodeptr = head;
	int r = 1; // r is used to compare with nth_block
	while (nodeptr)
	{
		if (r == nth_block) // check if r is at the same block as with nth_block
		{
			keeper = nodeptr;
			break;
		}
		nodeptr = nodeptr->next;
		r++;
	}
	return keeper->partition_memory_size;
}
// returns the memory block number
int list::show_mem_num(int nth_block)
{
	node* nodeptr;
	node* keeper = head; // keeper will save the memory location tht the job has choosen to stay 
	nodeptr = head;
	int r = 1; // r is used to compare with nth_block
	while (nodeptr)
	{
		if (r == nth_block) // check if r is at the same block as with nth_block
		{
			keeper = nodeptr;
			break;
		}
		nodeptr = nodeptr->next;
		r++;
	}
	return keeper->memory_num;
}
// to set the status if the memory partition is free or occupied
void list::set_status(int memory_block, int job_exit_time, int job_tht_gonna_masuk)
{
	node* nodeptr = head;
	node* keeper = head; // keeper will save the memory location tht the job has choosen to stay 
	int r = 1;
	while (nodeptr)
	{
		if (r == memory_block) // check if r is at the same block as with nth_block
		{
			keeper = nodeptr;
			break;
		}
		nodeptr = nodeptr->next;
		r++;
	}
	keeper->status = 1; // 1 = occupied
	keeper->job_processing_time = job_exit_time;
	keeper->job_dlm_mem_slot = job_tht_gonna_masuk;
}
// checks the memory partition, whether is occupied or not at the moment
int list::listcheck(int memory_block, int job_arrival_time)
{
	node* nodeptr = head;
	node* traveller = head;
	int r = 1; // r is used to compare with nth_block
	while (nodeptr)
	{
		if (r == memory_block) // check if r is at the same block as with nth_block
		{
			traveller = nodeptr;
			break;
		}
		nodeptr = nodeptr->next;
		r++;
	}
	if (traveller->status == 0) // 0 means the memory_bock is empty
		return 0;
	if (traveller->job_processing_time != 0) // if doesnt equal to 0, it means..there is a job in it..
	{
		if (traveller->job_processing_time > job_arrival_time) // the job exit time is more than the new job's arrival time, so it cant enter
			return 1;
		if (traveller->job_processing_time <= job_arrival_time) // the job exit time is equal to the new job's arrival time, the  job can enter
			return 0;
	}
}

void list::departure(int arrival, int& newarr, int& w, int& count, bool& bo)	//will send balik to main new arrival, tht specific memory number, and counter as indicator to queue
{
	node* nodeptr = head;
	node* pointer = head;
	node* point = head;
	int x = 1, y = 1, z = 1, a = 1;
	//joblist obj[100];
	while (nodeptr)	//first time setting newarr
	{
		if (nodeptr->job_processing_time > 0 && nodeptr->job_processing_time <= arrival)
		{
			newarr = nodeptr->job_processing_time;
			break;
		}
		else
			nodeptr = nodeptr->next;
	}
	if (nodeptr == NULL)	//if no process time less than arrival time
		bo = false;

	if (bo != false)
	{
		while (pointer)		//sort the lowest newarr if two or more process time less than arrival time
		{
			if (pointer->job_processing_time > 0 && pointer->job_processing_time <= arrival)
			{
				if (pointer->job_processing_time <= newarr)
				{
					newarr = pointer->job_processing_time;//this jobs processing time become newarrival for future job in queue
					z = y;	//know memory number that will be departured
				}
			}
			pointer = pointer->next;
			y++;
		}
		while (point)
		{
			if (a == z)	//if a equals to memory number
			{
				point->status = 0;	//memory is free
				point->job_processing_time = 0;
				cout << "\nAt t = " << newarr << " memory number " << a << " sized ";
				cout << point->partition_memory_size << " is free now";
				cout << "\n>>> the job number tht left is : " << point->job_dlm_mem_slot << endl;
				w = a;	// to know which memory is free so that queue jobs can check that particular memory only
				count = 1;	//indicate the queue
				system("PAUSE"); cout << "\n";
				bo = true;
				break;
			}
			else
				point = point->next;
			a++;
		}
	}
}
