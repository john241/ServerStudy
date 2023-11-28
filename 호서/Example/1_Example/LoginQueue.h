#pragma once
#include <list>
#include "Player.h"

class CLoginQueue
{
public:
	CLoginQueue() {}
	~CLoginQueue() {}

public:
	std::list<CPlayer*> m_Queue;
};

