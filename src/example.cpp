// This is the library for ThreadPools
// More info: https://github.com/vit-vit/CTPL
#include "ctpl_stl.h"
#include <iostream>
#include <vector>
#include <mutex>
#define NUM_THREADS 2
#define NUM_TASKS 10

// mutex for critical section
std::mutex mtx;

// The worker function
// The first parameter is the id of the thread in which is
// running
int
add(int id, int num1, int num2)
{
	// Print in order
	mtx.lock();
	std::cout << "Thread num: " << id
		<< " param1: " << num1
		<< " param2: " << num2
		<< std::endl;
	mtx.unlock();
	return num1 + num2;
}

int
main (int argc, char *argv[])
{
	// Thread pool
	ctpl::thread_pool p(NUM_THREADS);
	// Where to store results of the pool
	// std::future allows to safely wait for asynchronous
	// calls.
	std::vector<std::future<int>> results(NUM_TASKS);
	// Add tasks to the pool.
	for (int j = 0; j < NUM_TASKS; ++j)
	{
		// The tasks is sum two numbers
		results[j] = p.push( add, j, j);
	}
	// Wait for the execution of the tasks
	p.stop(true);
	// Now responses are ready
	std::cout << std::endl << "Results:" << std::endl;
	for (int j = 0; j < NUM_TASKS; ++j)
	{
		// Get responses and print them
		std::cout << "Task No "<< j << " => "
			<< results[j].get() << std::endl;
	}
}
