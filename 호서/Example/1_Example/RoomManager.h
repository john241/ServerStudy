#pragma once
#include "Lock.h"
#include <vector>

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

private:
	std::vector<CRoom*> m_RoomList;

private:
	CLock m_RoomLock;
};

