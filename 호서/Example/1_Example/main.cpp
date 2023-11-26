#include "RoomManager.h"
#include "PlayerManager.h"
#include "AppManager.h"
#include "JoinThread.h"
#include "TimerThread.h"

int main()
{
	CRoomManager::GetInstance();
	CPlayerManager::GetInstance();
	CAppManager::GetInstance();

	const int coreNum = std::thread::hardware_concurrency();

	// JoinThread 세팅
	{
		// 이거 resize 후 index 접근, emplace_back, push_back 성능 확인해보자
		//g_JoinThreadList.resize(coreNum * 2);
		for (int i = 0; i < coreNum * 2; ++i)
		{
			g_JoinThreadList.emplace_back(new CJoinThread());
		}
	}

	// TimerThread 세팅
	{
		//g_TimerThreadList.resize(2);
		for (int i = 0; i < 1; ++i)
		{
			g_TimerThreadList.emplace_back(new CTimerThread());
		}
	}

	// JoinThread 대기
	{
		for (int i = 0; i < coreNum * 2; ++i)
		{
			g_JoinThreadList[i]->Join();
		}
	}

	// TimerThread 대기
	{
		for (int i = 0; i < 2; ++i)
		{
			g_TimerThreadList[i]->Join();
		}
	}

	return 0;
}