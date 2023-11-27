#include "RoomManager.h"
#include "Room.h"

CRoomManager::CRoomManager()
	: m_RoomLock()
	, m_RoomList()
{
	//m_RoomList.resize(1000);
	
	for (int i = 0; i < ROOM_COUNT; ++i)
	{
		CRoom* newRoom = new CRoom();
		int shardIndex = newRoom->GetId() % TIMER_THREAD_COUNT;

		m_RoomList[shardIndex].emplace_back(newRoom);
	}
}

CRoomManager::~CRoomManager()
{
	for (int i = 0; i < ROOM_COUNT; ++i)
	{
		m_RoomList[i].clear();
	}
}

void CRoomManager::Foreach(const int threadId, std::function<bool(CRoom*)> func)
{
	if (m_RoomList.size() <= threadId)
	{
		return;
	}

	//CScopeLock lock(&m_RoomLock);

	bool result = false;
	auto list = m_RoomList[threadId];

	for (auto room : list)
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
