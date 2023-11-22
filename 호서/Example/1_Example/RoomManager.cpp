#include "RoomManager.h"
#include "Room.h"

CRoomManager::CRoomManager()
	: m_RoomLock()
	, m_RoomList()
{
	//m_RoomList.resize(1000);
	
	for (int i = 0; i < 1000; ++i)
	{
		m_RoomList.emplace_back(new CRoom());
	}
}

CRoomManager::~CRoomManager()
{
	for (auto room : m_RoomList)
	{
		room->OnDestroy();

		delete room;
	}

	m_RoomList.clear();
	m_RoomList.shrink_to_fit();
}
