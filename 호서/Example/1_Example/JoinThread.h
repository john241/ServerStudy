#pragma once
#include "Thread.h"
class CJoinThread : public CThread
{
public:
	CJoinThread();
	virtual ~CJoinThread();

public:
	virtual void Run() override final;
};

