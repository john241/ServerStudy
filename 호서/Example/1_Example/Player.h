#pragma once
#include "Timer.h"

enum class EPlayerState
{
	EPlayerState_WAIT = 0,
	EPlayerState_MATCHING,
	EPlayerState_RUN,
};
class CPlayer
{
public:
	CPlayer();
	~CPlayer();

public:
	const int GetId();
	const bool IsJoinable();

	void Start();
	void End();
	const bool IsExitable();

private:
	int m_Id;
	int m_PlayCount;
	CTimer m_Timer;
	EPlayerState m_State;
};

