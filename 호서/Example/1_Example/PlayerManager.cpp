#include "PlayerManager.h"
#include "Player.h"
#include "Config.h"
#include "AppManager.h"
#include <iostream>

CPlayerManager::CPlayerManager()
	: m_PlayerList()
	, m_Lock()
	, m_FinishCount(0)
{
	//m_PlayerList.resize(1000);

	for (int i = 0; i < PLAYER_COUNT; ++i)
	{
		CPlayer* player = new CPlayer();

		m_PlayerList.insert(std::make_pair(player->GetId(), player));
	}
}


CPlayerManager::~CPlayerManager()
{
	m_PlayerList.clear();
}

void CPlayerManager::PopPlayerList(std::list<CPlayer*>& outList)
{
	CScopeLock lock(&m_Lock);

	if (m_PlayerList.size() < MAX_ENTRY_COUNT)
	{
		return;
	}

	for (int i = 0; i < MAX_ENTRY_COUNT; ++i)
	{
		auto itor = m_PlayerList.begin();

		CPlayer* player = itor->second;

		outList.emplace_back(player);

		m_PlayerList.erase(player->GetId());
	}
}

void CPlayerManager::PushPlayer(CPlayer* player)
{
	CScopeLock lock(&m_Lock);

	if (m_PlayerList.end() != m_PlayerList.find(player->GetId()))
	{
		std::cout << "PushPlayerError : " << player->GetId() << std::endl;
		CAppManager::GetInstance()->SetTerminated();
		return;
	}


	m_PlayerList.insert( std::make_pair(player->GetId(), player));
}

void CPlayerManager::Foreach(std::function<bool(CPlayer*)> func)
{
	CScopeLock lock(&m_Lock);

	bool result = false;

	for (auto player : m_PlayerList)
	{
		result = func(player.second);
		if (true == result)
		{
			break;
		}
	}
}

bool CPlayerManager::AddFinishCount(const int num)
{
	m_FinishCount.fetch_add(num);

	return PLAYER_COUNT - MAX_ENTRY_COUNT <= m_FinishCount.load();
}