#include "Logger.h"
#include <iostream>
#include <condition_variable>

Logger::Logger()
{
	m_hasData = false;
	m_shouldClose = false;

	m_thread = std::thread(&Logger::WriteToFile, this);
}

Logger::~Logger()
{
	m_shouldClose = true;
	cv.notify_one();
	m_thread.join();
	bool joinable = m_thread.joinable();
}

void Logger::WriteToLog(std::string output)
{
	/*std::thread newThread(&Logger::WriteToFile, this, output);
	newThread.detach();*/
	m_data.push_back(output);
	if (!m_hasData)
	{
		m_hasData = true;
		cv.notify_one();
		//m_thread = std::thread(&Logger::WriteToFile, this);
	}
}

void Logger::WriteToFile()
{
	std::unique_lock<std::mutex> lk(m_mutex);	

	while (!m_shouldClose || m_hasData)
	{
		//std::this_thread::yield();
		if (m_hasData)
		{
			std::ofstream file;
			file.open("Log.txt", std::ios::app);

			if (file.is_open())
			{
				while (m_hasData)
				{
					file << m_data.front();
					std::cout << m_data.front();

					m_data.pop_front();

					if (m_data.empty())
					{
						m_hasData = false;
					}
				}
				file.close();
			}			
		}	
		cv.wait(lk, [this] { return m_hasData || m_shouldClose; });		
	}
}