#include "TimerThread.h"
#include "AppManager.h"
#include "MatchingFacade.h"

CTimerThread::CTimerThread()
{
	static int indexer = 0;
	m_Id = indexer++;
}

CTimerThread::~CTimerThread()
{
}

void CTimerThread::Run()
{
	while (true)
	{
		if (!CAppManager::GetInstance()->IsTerminated())
		{
			MatchingFacade::RoomOnTimer(m_Id);
		}
		else // ¾Û Á¾·á
		{
			// ·Î±ë
			break;
		}
	}
}
