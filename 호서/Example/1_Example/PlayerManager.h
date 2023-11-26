#pragma once
#include <list>
#include "Lock.h"
#include <functional>

class CPlayer;
class CPlayerManager
{
private:
	CPlayerManager();

public:
	~CPlayerManager();

public:
	static CPlayerManager* GetInstance()
	{
		static CPlayerManager* instance = nullptr;

		if (nullptr == instance)
		{
			instance = new CPlayerManager();
		}

		return instance;
	}

public:
	CPlayer* PopPlayer();
	void PushPlayer(CPlayer* player);

	void Foreach(std::function<bool(CPlayer*)> func);

private:
	CLock m_Lock;
	std::list<CPlayer*> m_PlayerList;
};

