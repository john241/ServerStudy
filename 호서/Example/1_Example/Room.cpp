#include "Room.h"
#include "Config.h"
#include "Player.h"
#include <iostream>
#include "AppManager.h"

CRoom::CRoom()
	: m_RoomLock()
	, m_PlayerList()
	, m_State(ERoomState::ERoomState_WAIT)
	, m_StartTick(0)
	, m_Timer()
	, m_Id(0)
{
	static int indexer = 0;
	m_Id = ++indexer;
}

CRoom::~CRoom()
{
	m_PlayerList.clear();
}

void CRoom::AddPlayer(std::list<CPlayer*>& list)
{
	//CScopeLock lock(&m_RoomLock);

	DWORD threadId = GetCurrentThreadId();

	for (auto itor = list.begin(); itor != list.end(); )
	{
		CPlayer* player = *itor;

		//if (m_PlayerList.end() != m_PlayerList.find(player->GetId()))
		//{
		//	std::cout << "threadId : " << threadId << " Room( " << GetId() << " )" << " Player( " << player->GetId() << " )  Overlap Error" << std::endl;
		//	CAppManager::GetInstance()->SetTerminated();
		//	return;
		//}


		m_PlayerList.emplace(std::make_pair(player->GetId(), player));
		itor = list.erase(itor);

		std::cout << "threadId : " << threadId << ", player( " << player->GetId() << " ) Room( " << GetId() << " ) Add Player And Check Room" << std::endl;

		if (MAX_ENTRY_COUNT <= m_PlayerList.size())
		{
			return;
		}
		//++itor;
	}
}

void CRoom::DeletePlayer()
{
	CScopeLock lock(&m_RoomLock);
	m_PlayerList.clear();
}

const int CRoom::GetId()
{
	return m_Id;
}

void CRoom::OnDestroy() 
{
}

const bool CRoom::IsJoinable()
{
	//CScopeLock lock(&m_RoomLock);
	return m_PlayerList.size() < MAX_ENTRY_COUNT;
}

const bool CRoom::IsRunable()
{
	//CScopeLock lock(&m_RoomLock);
	return m_PlayerList.size() == MAX_ENTRY_COUNT;
}

void CRoom::Start()
{
	DWORD threadId = GetCurrentThreadId();

	if (ERoomState::ERoomState_RUN == m_State)
	{
		std::cout << "threadId : " << threadId << " Room( " << GetId() << " )" << " Room Start Error" << std::endl;
		CAppManager::GetInstance()->SetTerminated();
		return;
	}

	m_State = ERoomState::ERoomState_RUN;
	m_Timer.Start();

	std::cout << "threadId : " << threadId << " Room( " << GetId() << " )" << " Room Start " << std::endl;
}

void CRoom::End()
{
	DWORD threadId = GetCurrentThreadId();

	if (ERoomState::ERoomState_WAIT == m_State)
	{
		std::cout << "threadId : " << threadId << " Room( " << GetId() << " )" << " Room End Error" << std::endl;
		CAppManager::GetInstance()->SetTerminated();
		return;
	}

	m_State = ERoomState::ERoomState_WAIT;
	m_PlayerList.clear();
	std::cout << "threadId : " << threadId << " Room( " << GetId() << " )" << " Room End " << std::endl;
}

const bool CRoom::IsFinish()
{
	return ERoomState::ERoomState_RUN == m_State && ROOM_WAIT_TICK <= m_Timer.Duration();
}

void CRoom::Foreach(std::function<void(CPlayer*)> func)
{
	//CScopeLock lock(&m_RoomLock);

	for (auto player : m_PlayerList)
	{
		func(player.second); 
	}
}

CLock* CRoom::GetLock()
{
	return &m_RoomLock;
}
