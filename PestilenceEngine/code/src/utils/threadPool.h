#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include <thread>
#include <iostream>

#include "../MyVector.h"

using namespace std;

class ThreadPool {
public:
	ThreadPool();
	ThreadPool(int numThreads);
	~ThreadPool();

	void scheduleTask(void(*f)());
	void waitForTask(float);

private:
	int m_AvailableThreadCount;
	int m_RunningThreadCount;
	thread* m_AvailableThreads;
	thread* m_RunningThreads;
};

#endif