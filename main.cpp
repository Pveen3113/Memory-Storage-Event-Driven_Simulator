#include <graphics.h>
#include <iostream>
#include "joblist.h"
#include "list.h"
#include "Queue.h"
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
int main()
{
	int start = 1;
	string filename;
	int Job_num, arrv_time, Pros_time, Job_size;
	fstream inputFile;
	joblist obj[100]; // 
	list memory_partition1; // memory partition lists are created
	list memory_partition2;
	ifstream infile;
	int array_size, option;
	int total_jobs;
	cout << " WELCOME TO THE EVENT DRIVEN SIMULATOR " << endl;
	cout << "Enter the filename (joblist) : ";	cin >> filename;
	filename += ".txt";
	inputFile.open(filename.c_str(), ios::in);
	if (inputFile)
	{
		inputFile >> total_jobs;
		for (int i = 1; i <= total_jobs; i++)
		{
			inputFile >> Job_num;
			inputFile >> arrv_time;
			inputFile >> Pros_time;
			inputFile >> Job_size;
			obj[i].set_job_num(Job_num);
			obj[i].set_arrival(arrv_time);
			obj[i].set_pros_time(Pros_time);
			obj[i].set_jobs(Job_size);
		}
	}
	else
	{
		cout << "## file not found ## " << endl;
		cout << "Enter filename againc(joblist) : ";
		cin >> filename;
		infile.open(filename.c_str(), ios::in);
	}

	while (start == 1)
	{
		system("CLS");
		cout << "Enter the following menu to test your current programme" << endl;
		cout << "1) Display Joblist file" << endl;
		cout << "2) Fixed Partition first fit" << endl;
		cout << "3) Fixed Partition best-fit" << endl;
		cout << "4) Dynamic Partition " << endl;
		cout << "5) EXIT SIMULATION" << endl;
		cout << "---> Enter your option : ";
		cin >> option;
		while (option != 1 && option != 2 && option != 3 && option != 4 && option != 5)
		{
			cout << "## invalid input , Try again ## " << endl;
			cout << "---> Enter your option : ";
			cin >> option;
		}

		if (option == 2 || option == 3)
		{
			cout << "\nEnter filename for memory list (memorylist): ";
			cin >> filename;	filename = filename + ".txt";
			infile.open(filename.c_str(), ios::in);
			while (!infile) // to check the availabilty of the entered file
			{
				cout << "## file not found ## " << endl;
				cout << "Enter filename again (memorylist) : ";
				cin >> filename;
				infile.open(filename.c_str(), ios::in);
			}
			if (infile) // read the first line from the textfile
				infile >> array_size;
			int memory_size_array[50]; // to know how many memory partitions there will be inside
			if (infile)
			{
				system("CLS");
				for (int i = 0; i < array_size && !infile.eof(); i++)
				{
					infile >> memory_size_array[i]; // will read the memory size from the textfile
					infile.ignore();  // to ignore the "enter" thing we pressed at textfile
				}
				infile.close();
			}

			for (int i = 0; i < array_size; i++)
			{
				memory_partition1.appendlist(memory_size_array[i], i); // the value from the memory list is assigned into each partition
			}

			for (int i = 0; i < array_size; i++)
			{
				memory_partition2.sortedlist(memory_size_array[i], i); // the value from the memory list is assigned into each partition and it is sorted in asce
			}
		}


		switch (option)
		{
		case 1:
		{
			for (int i = 1; i <= total_jobs; i++)
			{
				cout << obj[i].get_job() << '\t';
				cout << obj[i].get_arrival() << '\t';
				cout << obj[i].get_pros() << '\t';
				cout << obj[i].get_jobsize() << '\t';
				cout << endl;
			}
			break;
		}
		case 2:
		{
			int status3 = 0, new_arrival3 = 0, mem_no3 = 0, counter3 = 1; // works as a flag to indicate the status of memory
			Queue test_waiting_q3, second_waiting_q3;	// waiting queue is created
			bool flag3, bo3 = true; // to check whether the job has entered the memory or not
			int exit_time3 = 0;
			int wait_time3 = 0;
			int internal_frag3 = 0;
			int new_queue_length3 = 0;
			int mem_blocks3;
			int max_queue_length3 = 0;
			int min_queue_length3 = 0;
			float total_frag3 = 0;
			int num_job_x_masuk_cpu3 = 0;
			int simulation_end_time3 = 0;
			float total_wait_time3 = 0;
			float total_process_time3 = 0;
			float total_queue_content3 = 0;
			int max_wait_time3 = 0;
			int min_wait_time3 = 0;
			int incoming_job_wait_time3 = 0;

			cout << "Enter the number of memory blocks you want to test. Only this memory blocks are available to test" << endl;	//Enter valid memory blocks only
			cout << "3\t5\t7\t10" << endl;
			cout << "\nEnter your choice : ";
			cin >> mem_blocks3;
			while (mem_blocks3 != 3 && mem_blocks3 != 5 && mem_blocks3 != 7 && mem_blocks3 != 10)
			{
				cout << "incorrect choosing of memory blocks. Please choose again." << endl;
				cout << "Enter the number of memory blocks you want to test. Only this memory blocks are available to test" << endl;
				cout << "3\t5\t7\t10" << endl;
				cout << "------>Enter your choice : ";
				cin >> mem_blocks3;
			}

			initwindow(600,800);
			int top = 50;
			int bottom = 100;
			int left = 50;
			int right = 100;
			for(int i=1;i<=mem_blocks3;i++)
			{
				setcolor(WHITE);
				rectangle(300,top,400,bottom);
				top = top + 50;
				bottom = bottom + 50;
			}
			getch();
			//closegraph();
			for (int j = 1; j <= 40; j++) // j is the job pointer..
			{
				if (new_queue_length3 >= max_queue_length3)
					max_queue_length3 = new_queue_length3;
				if (new_queue_length3 <= min_queue_length3)
					min_queue_length3 = new_queue_length3;
				flag3 = true;	// to check if the job got a partition or not
				for (int k = 1; k <= mem_blocks3; k++) // k is the fixed memory pointer
				{
					if (obj[j].get_jobsize() <= memory_partition1.show_mem_size(k))	// to know job less than memory or not
					{
						while (bo3) // bo returns true if process time < arrival time , it will run while this condition stands , end of the list = returns false
						{
							memory_partition1.departure(obj[j].get_arrival(), new_arrival3, mem_no3, counter3, bo3);	// check wther b4 current job arrival is thr any job finish processed or not
							if (bo3 != false)
							{
								total_queue_content3 = total_queue_content3 + test_waiting_q3.get_quantity();
							}

							if (counter3 == 1)	//if there is memory departured will check the queue
							{
								int top5 = 50;
								int bottom5 = 100;
								for(int i=1;i<=mem_blocks3;i++)
								{
									setcolor(WHITE);
									if(i == mem_no3)
									{
										setcolor(BLUE);
									}
									rectangle(300,top5,400,bottom5);
									top5 = top5 + 50;
									bottom5 = bottom5 + 50;
								}
								getch();
								while (!test_waiting_q3.isEmpty()) // run the queue until it all sdh check
								{
									int value;
									test_waiting_q3.dequeue(value);
									if (obj[value].get_jobsize() <= memory_partition1.show_mem_size(mem_no3)) // check the queued job size less than memory which is freed from previous job only
									{
										exit_time3 = new_arrival3 + obj[value].get_pros();	//total process time. the new arrival time get from the departure of old job
										obj[value].set_job_completion_time(exit_time3);
										wait_time3 = new_arrival3 - obj[value].get_arrival(); // determine the waiting time for that job
										obj[value].set_job_waiting_time(wait_time3);
										memory_partition1.set_status(mem_no3, exit_time3, obj[value].get_job());	//set the memory into bz

										total_queue_content3 = total_queue_content3 + test_waiting_q3.get_quantity();

										internal_frag3 = memory_partition1.show_mem_size(mem_no3) - obj[value].get_jobsize();
										total_frag3 = total_frag3 + internal_frag3;
										cout << "\nt = " << new_arrival3 << " from queue, job number " << value << " sized " << obj[value].get_jobsize() << " has entered memory " << mem_no3;
										cout << " sized " << memory_partition1.show_mem_size(mem_no3) << endl;
										int top2 = 50;
										int bottom2 = 100;
										for(int i=1;i<=mem_blocks3;i++)
										{
											setcolor(WHITE);
											if(i == mem_no3)
											{
												setcolor(RED);
											}
											rectangle(300,top2,400,bottom2);
											top2 = top2 + 50;
											bottom2 = bottom2 + 50;
										}
										//getch();
										//closegraph();
										//system("PAUSE");
										break;
									}
									else
									{
										second_waiting_q3.enqueue(value);	//if not fit into memory masuk balik into the second queue. To avoid repetition here.
									}
								}
								
								while (!second_waiting_q3.isEmpty())	//eventually, the second queue data will sent to the test queue.
								{
									int value3;
									second_waiting_q3.dequeue(value3);
									test_waiting_q3.enqueue(value3);
								}
								cout << "QUANTITY: " << test_waiting_q3.get_quantity() << endl;
								
								for(int i=0;i<test_waiting_q3.get_quantity();i++)
								{
									rectangle(left,600,right,650);
									left = left + 50;
									right = right + 50;
								}
								getch();
								counter3 = 0;	//reset the counter
							}
						}
						bo3 = true;
						status3 = memory_partition1.listcheck(k, obj[j].get_arrival());	//check whether the memmory is bz or free
						if (status3 == 1)	// if bz then skip the loop to find next available memory
						{
							continue;
						}
						else if (status3 == 0)	// the memory is free and good to proceed
						{
							cout << "\n\nAt t = " << obj[j].get_arrival() << " job number " << obj[j].get_job() << " size : " << obj[j].get_jobsize();
							cout << " has entered the memory number " << memory_partition1.show_mem_num(k);
							cout << " size : " << memory_partition1.show_mem_size(k) << endl;
							total_queue_content3 = total_queue_content3 + test_waiting_q3.get_quantity();
							exit_time3 = obj[j].get_arrival() + obj[j].get_pros(); // get the exit time
							memory_partition1.set_status(k, exit_time3, obj[j].get_job());
							obj[j].set_job_completion_time(exit_time3);
							obj[j].set_job_waiting_time(0);
							internal_frag3 = memory_partition1.show_mem_size(k) - obj[j].get_jobsize();
							cout << "this job will exit at t = " << obj[j].get_job_completion_time() << endl;
							total_frag3 = total_frag3 + internal_frag3;
							flag3 = false; // false = sdh dpt tempat
							int top3 = 50;
							int bottom3 = 100;
							for(int i=1;i<=mem_blocks3;i++)
							{
								setcolor(WHITE);
								if(i == k)
								{
									setcolor(RED);
								}
								rectangle(300,top3,400,bottom3);
								top3 = top3 + 50;
								bottom3 = bottom3 + 50;
							}
							getch();
							//closegraph();
							//system("PAUSE");
							break; // exit the k for loop	
						}
					}
				}
				if (flag3) // the job tht didnt get any memory partition will enter the quueu via this function
				{
					cout << "\n\nAt t = " << obj[j].get_arrival() << " job number " << obj[j].get_job() << " with the size of  ";
					cout << obj[j].get_jobsize() << " has entered the queue " << endl;
					test_waiting_q3.enqueue(obj[j].get_job());
					new_queue_length3 = test_waiting_q3.get_quantity();
					total_queue_content3 = total_queue_content3 + test_waiting_q3.get_quantity();
					
					for(int i=0;i<test_waiting_q3.get_quantity();i++)
					{
						rectangle(left,600,right,650);
						left = left + 50;
						right = right + 50;
					}
					getch();
					//system("PAUSE");
				}
				if (j == 40)	//after job 40 thr is no arrival so after job 40 it will display all remaining processes
				{
					while (bo3) // bo returns true if process time < arrival time , it will run while this condition stands , end of the list = returns false
					{
						memory_partition1.departure(1000, new_arrival3, mem_no3, counter3, bo3);	// check whether b4 current job arrival is thr any job finish processed or not
						if (bo3 != false)
						{
							total_queue_content3 = total_queue_content3 + test_waiting_q3.get_quantity();
						}

						if (counter3 == 1)	//if there is memory departured will check the queue
						{
							int top6 = 50;
							int bottom6 = 100;
							for(int i=1;i<=mem_blocks3;i++)
							{
								setcolor(WHITE);
								if(i == mem_no3)
								{
									setcolor(BLUE);
								}
								rectangle(300,top6,400,bottom6);
								top6 = top6 + 50;
								bottom6 = bottom6 + 50;
							}
							getch();
							while (!test_waiting_q3.isEmpty()) // run the queue until it all sdh check
							{
								int value;
								test_waiting_q3.dequeue(value);
								if (obj[value].get_jobsize() <= memory_partition1.show_mem_size(mem_no3)) // check the queued job size less than memory which is freed from previous job only
								{
									exit_time3 = new_arrival3 + obj[value].get_pros();	//total process time. the new arrival time get from the departure of old job
									obj[value].set_job_completion_time(exit_time3);
									wait_time3 = new_arrival3 - obj[value].get_arrival(); // determine the waiting time for that job
									obj[value].set_job_waiting_time(wait_time3);
									memory_partition1.set_status(mem_no3, exit_time3, obj[value].get_job());	//set the memory into bz
									simulation_end_time3 = exit_time3;
									internal_frag3 = memory_partition1.show_mem_size(mem_no3) - obj[value].get_jobsize();
									total_frag3 = total_frag3 + internal_frag3;
									cout << "\nt = " << new_arrival3 << " from queue, job number " << value << " sized " << obj[value].get_jobsize() << " has entered memory " << mem_no3;
									cout << " sized " << memory_partition1.show_mem_size(mem_no3) << endl;
									system("PAUSE");
									total_queue_content3 = total_queue_content3 + test_waiting_q3.get_quantity();
									int top4 = 50;
									int bottom4 = 100;
									for(int i=1;i<=mem_blocks3;i++)
									{
										setcolor(WHITE);
										if(i == mem_no3)
										{
											setcolor(RED);
										}
										rectangle(300,top4,400,bottom4);
										top4 = top4 + 50;
										bottom4 = bottom4 + 50;
									}
									//getch();
									//closegraph();
									break;
								}
								else
								{
									second_waiting_q3.enqueue(value);	//if not fit into memory masuk balik into the second queue. To avoid repetition here.
								}
							}
						
							while (!second_waiting_q3.isEmpty())	//eventually, the second queue data will sent to the test queue.
							{
								int value;
								second_waiting_q3.dequeue(value);
								test_waiting_q3.enqueue(value);
							}
							
							for(int i=0;i<test_waiting_q3.get_quantity();i++)
							{
								rectangle(left,600,right,650);
								left = left + 50;
								right = right + 50;
							}
							getch();
							counter3 = 0;	//reset the counter
							if (simulation_end_time3 < new_arrival3)
								simulation_end_time3 = new_arrival3;
						}
					}
				}
				bo3 = true;
			}


			cout << "\n\n>>> Jobs that are waiting in the queue <<< " << endl;
			while (!test_waiting_q3.isEmpty())	//display the job number in queue;
			{
				int value3;
				test_waiting_q3.dequeue(value3);
				num_job_x_masuk_cpu3++;
				cout << "job number : " << value3;
				cout << " job size : " << obj[value3].get_jobsize() << endl;
			}

			for (int f = 1; f <= 40; f++)
			{
				if (obj[f].get_job_waiting_time() >= 0)
				{
					total_wait_time3 = total_wait_time3 + obj[f].get_job_waiting_time();
					total_process_time3 = total_process_time3 + obj[f].get_pros();

					incoming_job_wait_time3 = obj[f].get_job_waiting_time();

					if (incoming_job_wait_time3 >= max_wait_time3)
					{
						max_wait_time3 = incoming_job_wait_time3;
					}
					if (incoming_job_wait_time3 <= min_wait_time3)
					{
						min_wait_time3 = incoming_job_wait_time3;
					}

				}
			}

			cout << "\n--> total waiting time : " << total_wait_time3;
			cout << "\n---> average waiting time in the queue : " << (total_wait_time3 / (40 - num_job_x_masuk_cpu3));
			cout << "\n-----> Max wait time : " << max_wait_time3;
			cout << "\n-----> Min wait time : " << min_wait_time3;
			cout << "\n----> the simulation time : " << simulation_end_time3;
			cout << "\n-----> total processing time : " << total_process_time3;
			cout << "\n------> throughput value : " << (total_process_time3 / simulation_end_time3);
			cout << "\n-------> average queue length (max) : " << max_queue_length3;
			cout << "\n-------> average queue length (min) : " << min_queue_length3;
			cout << "\n--------> total internal fragmentation : " << total_frag3;
			cout << "\n---------> average internal fragmentation : " << (total_frag3 / mem_blocks3);
			cout << "\n----------> the total queue length : " << total_queue_content3;
			cout << "\n-----------> average queue length : " << (total_queue_content3 / simulation_end_time3);
			cout << "\n";
			break;
		}
		cleardevice();//closegraph();
		system("pause");
		case 3:
		{
			int status4 = 0, new_arrival4 = 0, mem_no4 = 0, counter4 = 1; // works as a flag to indicate the status of memory
			Queue test_waiting_q4, second_waiting_q4;	// waiting queue is created
			bool flag4, bo4 = true; // to check whether the job has entered the memory or not
			int exit_time4 = 0;
			int wait_time4 = 0;
			int simulation_end_time4 = 0;
			int internal_frag4 = 0;
			float total_frag4 = 0;
			int new_queue_length4 = 0;
			int mem_blocks4;
			int max_que_length4 = 0;
			int min_que_length4 = 0;
			int num_job_no_masuk_cpu4 = 0;
			float total_wait_time4 = 0;
			float total_process_time4 = 0;
			float total_queue_content4 = 0;
			int incoming_job_wait_time4 = 0;
			int max_wait_time4 = 0;
			int min_wait_time4 = 0;


			cout << "Enter the number of memory blocks you want to test. Only this memory blocks are available to test" << endl;	//Enter valid memory blocks only
			cout << "3\t5\t7\t10" << endl;
			cout << "\nEnter your choice : ";
			cin >> mem_blocks4;
			while (mem_blocks4 != 3 && mem_blocks4 != 5 && mem_blocks4 != 7 && mem_blocks4 != 10)
			{
				cout << "incorrect choosing of memory blocks. Please choose again." << endl;
				cout << "Enter the number of memory blocks you want to test. Only this memory blocks are available to test" << endl;
				cout << "3\t5\t7\t10" << endl; cout << "\nEnter your choice : ";
				cin >> mem_blocks4;
			}

			for (int j = 1; j <= 40; j++) // j is the job pointer..
			{
				if (new_queue_length4 >= max_que_length4)
					max_que_length4 = new_queue_length4;
				if (new_queue_length4 <= min_que_length4)
					min_que_length4 = new_queue_length4;
				flag4 = true;	// to check if the job got a partition or not
				for (int k = 1; k <= mem_blocks4; k++) // k is the fixed memory pointer
				{
					if (obj[j].get_jobsize() <= memory_partition2.show_mem_size(k))	// to know job less than memory or not
					{
						while (bo4) // bo returns true if process time < arrival time , it will run while this condition stands , end of the list = returns false
						{
							memory_partition2.departure(obj[j].get_arrival(), new_arrival4, mem_no4, counter4, bo4);	// check wther b4 current job arrival is thr any job finish processed or not
							if (bo4 != false)
							{
								total_queue_content4 = total_queue_content4 + test_waiting_q4.get_quantity();
							}

							if (counter4 == 1)	//if there is memory departured will check the queue
							{
								while (!test_waiting_q4.isEmpty()) // run the queue until it all sdh check
								{
									int value;
									test_waiting_q4.dequeue(value);
									if (obj[value].get_jobsize() <= memory_partition2.show_mem_size(mem_no4)) // check the queued job size less than memory which is freed from previous job only
									{
										exit_time4 = new_arrival4 + obj[value].get_pros();	//total process time. the new arrival time get from the departure of old job
										obj[value].set_job_completion_time(exit_time4);
										wait_time4 = new_arrival4 - obj[value].get_arrival(); // determine the waiting time for that job
										obj[value].set_job_waiting_time(wait_time4);
										memory_partition2.set_status(mem_no4, exit_time4, obj[value].get_job());	//set the memory into bz
										total_queue_content4 = total_queue_content4 + test_waiting_q4.get_quantity();
										internal_frag4 = memory_partition2.show_mem_size(mem_no4) - obj[value].get_jobsize();
										total_frag4 = total_frag4 + internal_frag4;
										cout << "\nt = " << new_arrival4 << " from queue, job number " << value << " sized " << obj[value].get_jobsize() << " has entered memory " << mem_no4;
										cout << " sized " << memory_partition2.show_mem_size(mem_no4) << endl;
										system("PAUSE");
										break;
									}
									else
									{
										second_waiting_q4.enqueue(value);	//if not fit into memory masuk balik into the second queue. To avoid repetition here.
									}
								}
								while (!second_waiting_q4.isEmpty())	//eventually, the second queue data will sent to the test queue.
								{
									int value;
									second_waiting_q4.dequeue(value);
									test_waiting_q4.enqueue(value);
								}
								counter4 = 0;	//reset the counter
							}
						}
						bo4 = true;
						status4 = memory_partition2.listcheck(k, obj[j].get_arrival());	//check whether the memmory is bz or free
						if (status4 == 1)	// if bz then skip the loop to find next available memory
						{
							continue;
						}
						else if (status4 == 0)	// the memory is free and good to proceed
						{
							cout << "\n\nAt t = " << obj[j].get_arrival() << " job number " << obj[j].get_job() << " size : " << obj[j].get_jobsize();
							cout << " has entered the memory number " << memory_partition2.show_mem_num(k);
							cout << " size : " << memory_partition2.show_mem_size(k) << endl;
							total_queue_content4 = total_queue_content4 + test_waiting_q4.get_quantity();
							exit_time4 = obj[j].get_arrival() + obj[j].get_pros(); // get the exit time
							memory_partition2.set_status(k, exit_time4, obj[j].get_job());
							obj[j].set_job_completion_time(exit_time4);
							obj[j].set_job_waiting_time(0);
							internal_frag4 = memory_partition2.show_mem_size(k) - obj[j].get_jobsize();
							total_frag4 = total_frag4 + internal_frag4;
							cout << "this job will exit at t = " << obj[j].get_job_completion_time() << endl;
							flag4 = false; // false = sdh dpt tempat
							system("PAUSE");
							break; // exit the k for loop	
						}
					}
				}
				if (flag4) // the job tht didnt get any memory partition will enter the quueu via this function
				{
					cout << "\n\nAt t = " << obj[j].get_arrival() << " job number " << obj[j].get_job() << " with the size of  ";
					cout << obj[j].get_jobsize() << " has entered the queue " << endl;
					test_waiting_q4.enqueue(obj[j].get_job());
					new_queue_length4 = test_waiting_q4.get_quantity();
					total_queue_content4 = total_queue_content4 + test_waiting_q4.get_quantity();
					system("PAUSE");
				}
				if (j == 40) //after job 40 thr is no arrival so after job 40 it will display all remaining processes
				{
					while (bo4) // bo returns true if process time < arrival time , it will run while this condition stands , end of the list = returns false
					{
						memory_partition2.departure(1000, new_arrival4, mem_no4, counter4, bo4);	// check whether b4 current job arrival is thr any job finish processed or not
						if (bo4 != false)
						{
							total_queue_content4 = total_queue_content4 + test_waiting_q4.get_quantity();
						}
						if (counter4 == 1)	//if there is memory departured will check the queue
						{
							while (!test_waiting_q4.isEmpty()) // run the queue until it all sdh check
							{
								int value;
								test_waiting_q4.dequeue(value);
								if (obj[value].get_jobsize() <= memory_partition2.show_mem_size(mem_no4)) // check the queued job size less than memory which is freed from previous job only
								{
									exit_time4 = new_arrival4 + obj[value].get_pros();	//total process time. the new arrival time get from the departure of old job
									obj[value].set_job_completion_time(exit_time4);
									wait_time4 = new_arrival4 - obj[value].get_arrival(); // determine the waiting time for that job
									obj[value].set_job_waiting_time(wait_time4);
									memory_partition2.set_status(mem_no4, exit_time4, obj[value].get_job());	//set the memory into bz
									simulation_end_time4 = exit_time4;
									internal_frag4 = memory_partition2.show_mem_size(mem_no4) - obj[value].get_jobsize();
									total_frag4 = total_frag4 + internal_frag4;
									cout << "\nt = " << new_arrival4 << " from queue, job number " << value << " sized " << obj[value].get_jobsize() << " has entered memory " << mem_no4;
									cout << " sized " << memory_partition2.show_mem_size(mem_no4) << endl;
									system("PAUSE");
									total_queue_content4 = total_queue_content4 + test_waiting_q4.get_quantity();
									break;
								}
								else
								{
									second_waiting_q4.enqueue(value);	//if not fit into memory masuk balik into the second queue. To avoid repetition here.
								}
							}
							while (!second_waiting_q4.isEmpty())	//eventually, the second queue data will sent to the test queue.
							{
								int value;
								second_waiting_q4.dequeue(value);
								test_waiting_q4.enqueue(value);
							}
							counter4 = 0;	//reset the counter
							if (simulation_end_time4 < new_arrival4)
								simulation_end_time4 = new_arrival4;
						}
					}
				}
				bo4 = true;
			}


			cout << "\n\n>>> Jobs that are waiting in the queue <<< " << endl;
			while (!test_waiting_q4.isEmpty())	//display the job number in queue;
			{
				int value4;
				test_waiting_q4.dequeue(value4);
				num_job_no_masuk_cpu4++;
				cout << "job number : " << value4;
				cout << " job size : " << obj[value4].get_jobsize() << endl;
			}

			for (int f = 1; f <= 40; f++)
			{
				if (obj[f].get_job_waiting_time() >= 0)
				{
					total_wait_time4 = total_wait_time4 + obj[f].get_job_waiting_time();
					total_process_time4 = total_process_time4 + obj[f].get_pros();

					incoming_job_wait_time4 = obj[f].get_job_waiting_time();

					if (incoming_job_wait_time4 >= max_wait_time4)
					{
						max_wait_time4 = incoming_job_wait_time4;
					}
					if (incoming_job_wait_time4 <= min_wait_time4)
					{
						min_wait_time4 = incoming_job_wait_time4;
					}


				}
			}
			cout << "\n--> total waiting time : " << total_wait_time4;
			cout << "\n---> average waiting time in the queue : " << (total_wait_time4 / (40 - num_job_no_masuk_cpu4));
			cout << "\n-----> Max wait time : " << max_wait_time4;
			cout << "\n-----> Min wait time : " << min_wait_time4;
			cout << "\n----> the simulation time : " << simulation_end_time4;
			cout << "\n-----> total processing time : " << total_process_time4;
			cout << "\n------> throughput value : " << (total_process_time4 / simulation_end_time4);
			cout << "\n-------> average queue length (max) : " << max_que_length4;
			cout << "\n-------> average queue length (min) : " << min_que_length4;
			cout << "\n--------> total internal fragmentation : " << total_frag4;
			cout << "\n---------> average internal fragmentation : " << (total_frag4 / mem_blocks4);
			cout << "\n----------> the total queue length : " << total_queue_content4;
			cout << "\n-----------> average queue length : " << (total_queue_content4 / simulation_end_time4);
			cout << "\n";
			system("pause");
			break;
		}
		case 4:
		{
			int mem_size, category, bestfit = 0, worstfit = 0, fragment = 0, total_exfrag = 0, total_exfrag1 = 0, total_exfrag2 = 0, total_exfrag3 = 0, simulation_time = 0;
			list memory_parti;
			int value5 = 0, status = 0, status1 = 0, check = 0, check1 = 0, status2 = 0, newarr5 = 0;
			Queue waiting, waiting2;
			bool bo5 = true;
			int exit_time5 = 0; // this is to calculate the job exit time
			int wait_time5 = 0;
			int num_job_no_masuk_cpu4 = 0;
			int max_que_length5 = 0;
			int min_que_length5 = 0;
			int new_queue_length5 = 0;
			int max_wait_time5 = 0;
			int min_wait_time5 = 0;
			int incoming_job_wait_time5 = 0;
			float total_wait_time5 = 0;
			float total_process_time5 = 0;
			float total_queue_content5 = 0;

			cout << "----> DYNAMIC PARTITION <----" << endl;
			cout << " 1) for best-fit" << endl;
			cout << " 2) worst-fit " << endl;
			cout << " 3) first-fit" << endl;
			cout << "----> Enter your choice : ";
			cin >> category;
			while (category != 1 && category != 2 && category != 3)
			{
				cout << "Incorrect choosing. Please choose again." << endl;
				cout << "Enter 1 for best-fit or 2 for worst-fit  or 3 for first-fit" << endl;
				cout << "----> Enter your choice : ";
				cin >> category;
			}
			if (category == 1)
				bestfit = 1;
			else if (category == 2)
				worstfit = 1;

			cout << "Enter the memory partition you want to test.\n20000\n30000\n40000\n50000" << endl;
			cout << "--> Enter the memory partition : ";
			cin >> mem_size;
			while (mem_size != 20000 && mem_size != 30000 && mem_size != 40000 && mem_size != 50000)	//choose memory size
			{
				cout << "Invalid memory partition. Please enter again." << endl;
				cout << "Enter the memory partition you want to test.\n20000\n30000\n40000\n50000" << endl;
				cout << "Enter the memory partition : ";
				cin >> mem_size;
			}

			memory_parti.appendlist1(mem_size);	//append memory size in link list

			for (int i = 1; i <= 40; i++)
			{
				if (new_queue_length5 >= max_que_length5)
					max_que_length5 = new_queue_length5;
				if (new_queue_length5 <= min_que_length5)
					min_que_length5 = new_queue_length5;
				while (bo5)	//check whole list
				{
					memory_parti.dyndeparture(obj[i].get_arrival(), newarr5, check, bo5, bestfit, worstfit); //check job departure

					if (check == 1) //if departure, then memory free
					{
						while (!waiting.isEmpty()) // check the queue first if got any job that can enter tht memory
						{
							int num;
							waiting.dequeue(num);
							memory_parti.dynjob1(obj[num].get_jobsize(), newarr5, obj[num].get_pros(), obj[num].get_job(), status1, value5, bestfit, worstfit, fragment);	//queue jobs insertion into memory
							total_exfrag1 = total_exfrag1 + fragment;
							fragment = 0;
							if (status1 == 0)
							{
								exit_time5 = newarr5 + obj[num].get_pros();
								obj[num].set_job_completion_time(exit_time5);
								wait_time5 = newarr5 - obj[num].get_arrival();
								obj[num].set_job_waiting_time(wait_time5);
								total_queue_content5 = total_queue_content5 + waiting.get_quantity();
							}

							if (status1 == 1)	//if queue job not fit into memory
							{
								waiting2.enqueue(num);
							}
							status1 = 0;
						}
						while (!waiting2.isEmpty())	//queue back job to original queue
						{
							int number;
							waiting2.dequeue(number);
							waiting.enqueue(number);
						}
					}
					check = 0;
				}
				bo5 = true;
				memory_parti.dynjob(obj[i].get_jobsize(), obj[i].get_arrival(), obj[i].get_pros(), obj[i].get_job(), status, value5, bestfit, worstfit, fragment);	//insert job into memory
				if (status == 0)
				{
					exit_time5 = obj[i].get_arrival() + obj[i].get_pros();
					obj[i].set_job_completion_time(exit_time5);
					obj[i].set_job_waiting_time(0);
					total_queue_content5 = total_queue_content5 + waiting.get_quantity();
				}

				total_exfrag2 = total_exfrag2 + fragment;
				fragment = 0;
				if (status == 1)	//job cannot fit into memory
				{
					waiting.enqueue(value5);	//job number
					new_queue_length5 = waiting.get_quantity();
					total_queue_content5 = total_queue_content5 + waiting.get_quantity();
				}
				status = 0;
				if (i == 40) //if no more job arrive,it continue departures all the remaining jobs
				{
					while (bo5)	//check the whole memory list
					{
						memory_parti.dyndeparture(1000, newarr5, check1, bo5, bestfit, worstfit);
						if (check1 != 0)
						{
							while (!waiting.isEmpty())
							{
								int num;
								waiting.dequeue(num);
								memory_parti.dynjob1(obj[num].get_jobsize(), newarr5, obj[num].get_pros(), obj[num].get_job(), status2, value5, bestfit, worstfit, fragment);
								if (status2 == 0)
								{
									exit_time5 = newarr5 + obj[num].get_pros();
									obj[num].set_job_completion_time(exit_time5);
									wait_time5 = newarr5 - obj[num].get_arrival();
									obj[num].set_job_waiting_time(wait_time5);
									total_queue_content5 = total_queue_content5 + waiting.get_quantity();

								}
								total_exfrag3 = total_exfrag3 + fragment;
								fragment = 0;
								if (status2 == 1)
								{
									waiting2.enqueue(num);
								}
								status2 = 0;
							}
							while (!waiting2.isEmpty())
							{
								int number;
								waiting2.dequeue(number);
								waiting.enqueue(number);
							}
							if (simulation_time < newarr5)	//calculate total simulation time
								simulation_time = newarr5;
						}
						check1 = 0;
					}
					bo5 = true;
				}
			}


			cout << ">>>> Job waiting queue:" << endl;
			while (!waiting.isEmpty()) // job that did not get memory
			{
				int value5;
				waiting.dequeue(value5);
				num_job_no_masuk_cpu4++;
				cout << "Job number " << obj[value5].get_job() << " sized " << obj[value5].get_jobsize() << endl;
			}
			bestfit = 0; worstfit = 0;
			total_exfrag = total_exfrag1 + total_exfrag2 + total_exfrag3;

			for (int i = 1; i <= 40; i++)
			{
				if (obj[i].get_job_waiting_time() >= 0)
				{
					total_wait_time5 = total_wait_time5 + obj[i].get_job_waiting_time();
					total_process_time5 = total_process_time5 + obj[i].get_pros();

					incoming_job_wait_time5 = obj[i].get_job_waiting_time();

					if (incoming_job_wait_time5 >= max_wait_time5)
					{
						max_wait_time5 = incoming_job_wait_time5;
					}
					if (incoming_job_wait_time5 <= min_wait_time5)
					{
						min_wait_time5 = incoming_job_wait_time5;
					}
				}

			}
			cout << "\nTotal waiting time : " << total_wait_time5 << endl; // done
			cout << "----------->Total processing time : " << total_process_time5 << endl; // done
			cout << "------>Total external fragmentation: " << total_exfrag << endl; // done
			cout << "--------> Simulation time: " << simulation_time << endl;  // done
			cout << "----> Throughput value : " << (total_process_time5 / simulation_time) << endl; // done
			cout << "----> Average waiting time : " << (total_wait_time5 / (40 - num_job_no_masuk_cpu4));  // done
			cout << "\n-----> Max wait time : " << max_wait_time5 << endl;
			cout << "-----> Min wait time : " << min_wait_time5;
			cout << "\n-------> average queue length (max) : " << max_que_length5;  // done
			cout << "\n-------> average queue length (min) : " << min_que_length5;  // done
			cout << "\n----------> the total queue length : " << total_queue_content5;
			cout << "\n-----------> average queue length : " << (total_queue_content5 / simulation_time) << endl;
			break;
		}

		}
		cout << "\n####  SELECT AN OPTION BELOW ####" << endl;
		cout << "1) Head to main menu " << endl;
		cout << "2) Exit " << endl;
		cout << "Your option : ";
		cin >> start;
		while (start != 1 && start != 2)
		{
			cout << "\nInvalid selection , please choose again : " << endl;
			cout << "1) Head to main menu " << endl;
			cout << "2) Exit simulator " << endl;
			cout << "Enter your option again : ";
			cin >> start;
		}
	}

	system("pause"); cout << "\n";
	system("CLS");
	cout << "THANK YOU " << endl;
	system("pause");
}
