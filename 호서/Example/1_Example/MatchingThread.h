#pragma once
#include "Thread.h"
class CMatchingThread : public CThread
{
public:
	CMatchingThread();
	virtual ~CMatchingThread();

public:
	virtual void Run() override final;
};

