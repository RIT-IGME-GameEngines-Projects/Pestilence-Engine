#include "threadPool.h"

ThreadPool::ThreadPool() {
	m_AvailableThreadCount = 10;
	m_RunningThreadCount = 0;

	m_AvailableThreads = new thread[10];
	for (int i = 0; i < 10; i++) {
		m_AvailableThreads[i] = thread();
	}
	m_RunningThreads = new thread[10];
}

ThreadPool::ThreadPool(int numThreads) {
	m_AvailableThreadCount = numThreads;
	m_RunningThreadCount = 0;

	m_AvailableThreads = new thread[numThreads];
	for (int i = 0; i < numThreads; i++) {
		m_AvailableThreads[i] = thread();
	}
	m_RunningThreads = new thread[numThreads];
}

ThreadPool::~ThreadPool() {
	delete m_AvailableThreads;
	delete m_RunningThreads;

	m_AvailableThreads = nullptr;
	m_RunningThreads = nullptr;
}

void ThreadPool::scheduleTask(void(*f)()) {

}

void ThreadPool::waitForTask(float milliseconds) {

}