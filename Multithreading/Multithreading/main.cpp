#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#include "Logger.h"
#include <string>

void Print(int index)
{
	static std::mutex printMutex;

	printMutex.lock();

	std::cout << "Hello Thread\n";
	std::cout << "a..." << index << "\n";
	std::cout << "b...\n";

	printMutex.unlock();
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

	Logger logger;
	for (int i = 0; i < threadCount; i++)
	{
		std::string output = "Test ";
		output += std::to_string(i);
		output += "\n";
		
		logger.WriteToLog(output);
	}
	//logger.WriteToLog("Test3");
	//logger.WriteToLog("Test4");
	//logger.WriteToLog("Test5");
	//logger.WriteToLog("Test2");

	return 0;
}