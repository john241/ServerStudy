#pragma once
#include "Lock.h"
#include <unordered_map>

class CPlayer;
class CRoom
{
public:
	CRoom();
	~CRoom();

public:
	void AddPlayer(CPlayer* player);
	void DeletePlayer(CPlayer* player);

	void OnDestroy();


private:
	std::unordered_map< int, CPlayer*> m_PlayerList;

private:
	CLock m_RoomLock;

};

