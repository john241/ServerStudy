#pragma once
#include "Lock.h"
#include <vector>
#include <functional>

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
	void Foreach(std::function<bool(CRoom*)> func);
	void StartRoom();

private:
	std::vector<CRoom*> m_RoomList;
	CLock m_RoomLock;
};