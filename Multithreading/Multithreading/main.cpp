#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#include "Logger.h"
#include <string>
#include "ThreadPool.h"

void Print()
{
	printf("Hello thread %i\n", std::this_thread::get_id());
}

void Sleep(int seconds)
{
	printf("Thread %i is sleeping for %i seconds\n", std::this_thread::get_id(), seconds);
	std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

int main()
{
	const int threadCount = 10;
	/*
	std::vector<std::thread> threads;

	for (int i = 0; i < threadCount; i++)
	{
		threads.push_back(std::thread(Print, i));
	}
	for (auto& thread : threads)
	{
		thread.join();
	}*/

	/*Logger logger;
	for (int i = 0; i < threadCount; i++)
	{
		std::string output = "Test ";
		output += std::to_string(i);
		output += "\n";
		
		logger.WriteToLog(output);
	}*/



	ThreadPool pool(2);
	pool.AddTask(Print);
	pool.AddTask(Print);
	pool.AddTask(std::bind(Sleep, 1));
	pool.AddTask(Print);
	pool.AddTask(std::bind(Sleep, 3));

	std::this_thread::sleep_for(std::chrono::seconds(2));	
	//logger.WriteToLog("Finished Sleep\n");
	return 0;
}