#include "PlayerManager.h"
#include "Player.h"
#include "Config.h"


CPlayerManager::CPlayerManager()
	: m_PlayerList()
	, m_Lock()
{
	//m_PlayerList.resize(1000);

	for (int i = 0; i < PLAYER_COUNT; ++i)
	{
		m_PlayerList.emplace_back(new CPlayer());
	}
}


CPlayerManager::~CPlayerManager()
{
	for (auto player : m_PlayerList)
	{
		delete player;
	}

	m_PlayerList.clear();
}

CPlayer* CPlayerManager::PopPlayer()
{
	CScopeLock lock(&m_Lock);

	if (true == m_PlayerList.empty())
	{
		return nullptr;
	}

	CPlayer* player = m_PlayerList.front();
	m_PlayerList.pop_front();

	return player;
}

void CPlayerManager::PushPlayer(CPlayer* player)
{
	CScopeLock lock(&m_Lock);

	m_PlayerList.push_back(player);
}

void CPlayerManager::Foreach(std::function<bool(CPlayer*)> func)
{
	CScopeLock lock(&m_Lock);

	bool result = false;

	for (auto player : m_PlayerList)
	{
		result = func(player);
		if (true == result)
		{
			break;
		}
	}
}
