#pragma once
#include "Thread.h"

class CLoginThread : public CThread
{
public:
	CLoginThread();
	virtual ~CLoginThread();

public:
	virtual void Run() override final;
};

static std::vector<CLoginThread*> g_LoginThreadList;