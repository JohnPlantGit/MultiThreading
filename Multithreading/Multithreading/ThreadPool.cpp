#include "ThreadPool.h"

ThreadPool::ThreadPool(int threadCount) : m_shutdown(false)
{
	m_threads.reserve(threadCount);

	for (int i = 0; i < threadCount; i++)
	{
		m_threads.push_back(std::thread(&ThreadPool::ThreadLoop, this));
	}
}

ThreadPool::~ThreadPool()
{
	{
		std::unique_lock<std::mutex> lock(m_mutex);

		m_shutdown = true;
		m_cv.notify_all();
	}

	for (int i = 0; i < m_threads.size(); i++)
	{
		m_threads[i].join();
	}
}

void ThreadPool::AddTask(std::function <void(void)> task, ...)
{
	std::unique_lock<std::mutex> lock(m_mutex);

	m_tasks.push(std::bind(task, ...);
	m_cv.notify_one();
}

void ThreadPool::ThreadLoop()
{
	std::function<void(void)> task;

	while (true)
	{
		{
			std::unique_lock<std::mutex> lock(m_mutex);

			while (!m_shutdown && m_tasks.empty())
				m_cv.wait(lock);

			if (m_tasks.empty())
			{
				return;
			}

			task = m_tasks.front();
			m_tasks.pop();
		}

		printf("Thread %i Start\n", std::this_thread::get_id());

		task();

		printf("Thread %i End\n", std::this_thread::get_id());
	}
}
