#pragma once
#include "Thread.h"
#include <vector>

class CJoinThread : public CThread
{
public:
	CJoinThread();
	virtual ~CJoinThread();

public:
	virtual void Run() override final;
};

static std::vector<CJoinThread*> g_JoinThreadList;