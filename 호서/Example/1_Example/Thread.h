#pragma once
#include <thread>

class CThread
{
public:
	CThread();
	virtual ~CThread();

public:
	virtual void Run() = 0;

public:
	void Stop();
	void Join();
	void Start();

protected:
	std::thread m_Thread;
};

