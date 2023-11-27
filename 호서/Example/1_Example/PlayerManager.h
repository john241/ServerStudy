#pragma once
#include <unordered_map>
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
	void PopPlayerList(std::list<CPlayer*>& outList);
	void PushPlayer(CPlayer* player);

	void Foreach(std::function<bool(CPlayer*)> func);
	bool AddFinishCount(const int num);
private:
	CLock m_Lock;
	std::unordered_map<int, CPlayer*> m_PlayerList;
	std::atomic<int> m_FinishCount;
};

