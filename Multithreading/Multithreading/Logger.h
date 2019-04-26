#pragma once
#include <thread>
#include <fstream>
#include <mutex>
#include <string>
#include <vector>
#include <list>

class Logger
{
public:
	Logger();
	~Logger();

	void WriteToLog(std::string output);


	void WriteToFile();
private:
	std::thread m_thread;
	std::mutex m_mutex;
	bool m_hasData;
	bool m_shouldClose;
	std::list<std::string> m_data;
};

