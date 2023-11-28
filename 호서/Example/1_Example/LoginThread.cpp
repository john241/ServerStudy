#include "LoginThread.h"
#include "AppManager.h"
#include "MatchingFacade.h"

CLoginThread::CLoginThread()
{
	static int indexer = 0;
	m_Id = indexer++;
}

CLoginThread::~CLoginThread()
{
}

void CLoginThread::Run()
{
	while (true)
	{
		if (!CAppManager::GetInstance()->IsTerminated())
		{
			MatchingFacade::LoginPlayer(m_Id);
		}
		else // ¾Û Á¾·á
		{
			// ·Î±ë

			break;
		}
	}
}
