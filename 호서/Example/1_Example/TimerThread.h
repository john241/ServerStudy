#pragma once
#include "Thread.h"
#include <vector>

class CTimerThread : public CThread
{
public:
	CTimerThread();
	virtual ~CTimerThread();

public:
	virtual void Run() override final;
};

static std::vector<CTimerThread*> g_TimerThreadList;
