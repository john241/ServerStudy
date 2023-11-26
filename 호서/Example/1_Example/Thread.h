#pragma once
#include <thread>
#include <string>

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
	void SetName(std::string name);
protected:
	std::thread m_Thread;
};

