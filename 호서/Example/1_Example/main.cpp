#include "RoomManager.h"
#include "PlayerManager.h"
#include "AppManager.h"
#include "JoinThread.h"
#include "TimerThread.h"
#include "LoginThread.h"
#include "Timer.h"
#include "Config.h"
#include <iostream>

int main()
{
	CRoomManager::GetInstance();
	CPlayerManager::GetInstance();
	CAppManager::GetInstance();

	const int coreNum = std::thread::hardware_concurrency();

	CTimer timer;
	timer.Start();
	// JoinThread 세팅
	{
		// 이거 resize 후 index 접근, emplace_back, push_back 성능 확인해보자
		//g_JoinThreadList.resize(coreNum * 2);
		for (int i = 0; i < JOIN_THREAD_COUNT; ++i)
		{
			g_JoinThreadList.emplace_back(new CJoinThread());
		}
	}

	// TimerThread 세팅
	{
		//g_TimerThreadList.resize(2);
		for (int i = 0; i < TIMER_THREAD_COUNT; ++i)
		{
			g_TimerThreadList.emplace_back(new CTimerThread());
		}
	}

	// LoginThread 세팅
	{
		for (int i = 0; i < 1; ++i)
		{
			g_LoginThreadList.emplace_back(new CLoginThread());
		}
	}

	// JoinThread 대기
	{
		for (int i = 0; i < JOIN_THREAD_COUNT; ++i)
		{
			g_JoinThreadList[i]->Join();
		}
	}

	// TimerThread 대기
	{
		for (int i = 0; i < TIMER_THREAD_COUNT; ++i)
		{
			g_TimerThreadList[i]->Join();
		}
	}

	// LoginThread 대기
	{
		for (int i = 0; i < 1; ++i)
		{
			g_LoginThreadList[i]->Join();
		}
	}

	std::cout << "program Duration : " << timer.Duration() << " ms " << std::endl;

	return 0;
}