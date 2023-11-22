#include "Thread.h"

CThread::CThread()
{
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
	m_Thread.join();
}

void CThread::Start()
{
	m_Thread = std::thread(&CThread::Run, this);
}
