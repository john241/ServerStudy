#include "RoomManager.h"
#include "Room.h"
#include "Config.h"

CRoomManager::CRoomManager()
	: m_RoomLock()
	, m_RoomList()
{
	//m_RoomList.resize(1000);
	
	for (int i = 0; i < ROOM_COUNT; ++i)
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

void CRoomManager::Foreach(std::function<bool(CRoom*)> func)
{
	CScopeLock lock(&m_RoomLock);

	bool result = false;

	for (auto room : m_RoomList)
	{
		result = func(room);

		if (true == result)
		{
			break;
		}
	}
}

void CRoomManager::StartRoom()
{
}
