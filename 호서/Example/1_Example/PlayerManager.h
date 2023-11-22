#pragma once
#include <vector>

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

private:
	std::vector<CPlayer*> m_PlayerList;

};

