#include<iostream>
using namespace std;
class list {
private:
    struct node {
        int memory_num; // stores the memory slot number,makes it easy to identify it later
        int partition_memory_size;// this is the size of the memory for 1 node(memory partition)
        int status; // to determine if the memory partition is free or not , 0 = means empty while 1 = means occupied
        int job_processing_time; // holds the amount of time a job is taking inside the queue
        int job_dlm_mem_slot; // stores the job number tht has entered the memory
        node* next;
    };
    node* head;
public:
    list()
    {
        head = NULL;
    }
    ~list()
    {
        head = NULL;
    }
    // all the basic op involving linked list
    void appendlist(int, int);
    void appendlist1(int);
    void dynjob(int, int, int, int, int&, int&, int, int, int&);
    void dynjob1(int, int, int, int, int&, int&, int, int, int&);
    void dyndeparture(int, int&, int&, bool&, int, int);
    void dynsortbest();
    void dynsortworst();
    void dynmerge();
    void sortedlist(int, int);
    void deletelist(int);
    int show_mem_size(int);
    void displaylist() const;
    int listcheck(int, int);
    void set_status(int, int, int);
    //int bestfit(int);
    void departure(int, int&, int&, int&, bool&);
    int show_mem_num(int);
};
