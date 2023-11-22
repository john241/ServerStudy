#include "Room.h"

CRoom::CRoom()
	: m_RoomLock()
	, m_PlayerList()
{
}

CRoom::~CRoom()
{
	m_PlayerList.clear();
}

void CRoom::AddPlayer(CPlayer* player)
{
	CScopeLock lock(&m_RoomLock);

	m_PlayerList.emplace(std::make_pair(1, player));
}

void CRoom::DeletePlayer(CPlayer* player)
{
	CScopeLock lock(&m_RoomLock);

	for (auto itor = m_PlayerList.begin(); itor != m_PlayerList.end(); ++itor)
	{
	}

	m_PlayerList.erase(1);

	m_PlayerList.clear();
}

void CRoom::OnDestroy()
{
}
