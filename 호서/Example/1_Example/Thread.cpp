#include "Thread.h"
#include <windows.h>

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

void CThread::SetName(std::string name)
{
	 DWORD dwThreadID = ::GetThreadId( static_cast<HANDLE>( m_Thread.native_handle() ) );

	//THREADNAME_INFO info;
	//info.dwType = 0x1000;
	//info.szName = name.c_str();
	//info.dwThreadID = dwThreadID;
	//info.dwFlags = 0;

	//__try
	//{
	//	RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*)&info);
	//}
	//__except (EXCEPTION_EXECUTE_HANDLER)
	//{
	//}
}
