#include "Logger.h"

Logger::Logger()
{
	m_hasData = false;
	m_shouldClose = false;

	m_thread = std::thread(&Logger::WriteToFile, this);
}

Logger::~Logger()
{
	m_shouldClose = true;
	m_hasData = true;
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
		//m_thread = std::thread(&Logger::WriteToFile, this);
	}
}

void Logger::WriteToFile()
{
	while (!m_hasData && !m_shouldClose)
	{
		//std::this_thread::yield();
		while (m_hasData)
		{
			std::ofstream file;
			file.open("Log.txt", std::ios::app);

			if (file.is_open())
			{
				file << m_data.front();

				file.close();
			}

			m_data.pop_front();

			if (m_data.empty())
			{
				m_hasData = false;
			}
		}		
	}
}