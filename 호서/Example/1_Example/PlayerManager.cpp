#include "PlayerManager.h"
#include "Player.h"

CPlayerManager::CPlayerManager()
	:m_PlayerList()
{
	//m_PlayerList.resize(1000);

	for (int i = 0; i < 1000; ++i)
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
	m_PlayerList.shrink_to_fit();
}
