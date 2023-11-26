#include "Player.h"
#include "Config.h"
#include <iostream>
#include <Windows.h>

CPlayer::CPlayer()
    : m_Id(0)
    , m_Timer()
    , m_PlayCount(0)
    , m_State(EPlayerState::EPlayerState_WAIT)
{
    static int indexer = 0;
    m_Id = ++indexer;
}

CPlayer::~CPlayer()
{
}

const int CPlayer::GetId()
{
    return m_Id;
}

const bool CPlayer::IsJoinable()
{
    return EPlayerState::EPlayerState_WAIT == m_State && PLAYER_WAIT_TICK < m_Timer.Duration();
}

void CPlayer::Start()
{
    DWORD threadId = GetCurrentThreadId();

    m_State = EPlayerState::EPlayerState_RUN;
    std::cout << "threadId : " << threadId << ", player( " << GetId() << " ) Start "  << std::endl;
}

void CPlayer::End()
{
    DWORD threadId = GetCurrentThreadId();

    m_State = EPlayerState::EPlayerState_WAIT;
    m_Timer.Start();
    ++m_PlayCount;


    std::cout << "threadId : " << threadId << ", player( " << GetId() << " ) count( " << m_PlayCount << " ) End" << std::endl;
}

const bool CPlayer::IsExitable()
{
    return MAX_PLAY_COUNT <= m_PlayCount;
}
