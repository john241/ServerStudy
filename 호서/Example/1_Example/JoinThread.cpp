#include "JoinThread.h"
#include "AppManager.h"
#include "MatchingFacade.h"

CJoinThread::CJoinThread()
{
}

CJoinThread::~CJoinThread()
{
}

void CJoinThread::Run()
{
	while (true)
	{
		if (!CAppManager::GetInstance()->IsTerminated())
		{
			MatchingFacade::MatchingOnce();
		}
		else // ¾Û Á¾·á
		{
			// ·Î±ë

			break;
		}
	}
}
