#include "RoomManager.h"
#include "Room.h"

CRoomManager::CRoomManager()
	: m_RoomLock()
	, m_RoomList()
{
}

CRoomManager::~CRoomManager()
{
	for (auto room : m_RoomList)
	{
		room->OnDestroy();

		delete room;
	}

	m_RoomList.clear();
}
