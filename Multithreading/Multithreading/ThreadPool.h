#pragma once
#include <queue>
#include <thread>
#include <vector>
#include <condition_variable>
#include <mutex>

class ThreadPool
{
public:
	ThreadPool(int threadCount);
	~ThreadPool();

	void AddTask(std::function <void(void)> task, ...);
	void ThreadLoop();

private:
	std::vector<std::thread> m_threads;
	std::queue<std::function <void (void)>> m_tasks;

	std::mutex m_mutex;
	std::condition_variable m_cv;
	bool m_shutdown;
};

