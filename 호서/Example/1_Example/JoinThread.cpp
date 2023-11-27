#include "JoinThread.h"
#include "AppManager.h"
#include "MatchingFacade.h"

CJoinThread::CJoinThread()
{
	static int indexer = 0;
	m_Id = indexer++;
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
			MatchingFacade::MatchingOnce(m_Id);
		}
		else // ¾Û Á¾·á
		{
			// ·Î±ë

			break;
		}
	}
}
