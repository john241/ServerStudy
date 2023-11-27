#pragma once
#include "Lock.h"
#include <vector>
#include <functional>
#include "Config.h"
#include <array>

class CRoom;
class CRoomManager
{
private:
	CRoomManager();

public:
	~CRoomManager();

public:
	static CRoomManager* GetInstance()
	{
		static CRoomManager* instance = nullptr;

		if (nullptr == instance)
		{
			instance = new CRoomManager();
		}

		return instance;
	}

public:
	void Foreach( const int threadId, std::function<bool(CRoom*)> func);
	void StartRoom();

private:
	using LoomList = std::vector<CRoom*>;
	std::array<LoomList, TIMER_THREAD_COUNT> m_RoomList;
	CLock m_RoomLock;
};