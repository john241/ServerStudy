#include "Thread.h"

CThread::CThread()
{
	Start();
}

CThread::~CThread()
{
	
}

void CThread::Stop()
{
	m_Thread.detach();
}

void CThread::Join()
{
	if (true == m_Thread.joinable())
	{
		m_Thread.join();
	}
}

void CThread::Start()
{
	m_Thread = std::thread(&CThread::Run, this);
}
