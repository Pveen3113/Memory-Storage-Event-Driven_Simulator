#include<iostream>
using namespace std;
class joblist
{
private:
	int job_num;
	int arrival;
	int pros_time;
	int jobs; // job number
	int job_completion_time; // what time each job finishes
	int job_waiting_time; // for the job that has waited in the queue,
public:
	joblist()
	{
		job_num = 0; arrival = 0; pros_time = 0; jobs = 0;
	}
	~joblist()
	{
		job_num = 0; arrival = 0; pros_time = 0; jobs = 0;
	}
	void set_job_num(int);
	void set_arrival(int);
	void set_pros_time(int);
	void set_jobs(int);
	void set_job_completion_time(int);
	void set_job_waiting_time(int);
	int get_job() { return job_num; }
	int get_arrival() { return arrival; }
	int get_pros() { return pros_time; }
	int get_jobsize() { return jobs; }
	int get_job_completion_time() { return job_completion_time; }
	int get_job_waiting_time() { return job_waiting_time; }
};
