#include "Timer.h"



CTimer::CTimer()
    :m_Start(std::chrono::milliseconds(0))
{
}

CTimer::~CTimer()
{
}

void CTimer::Start()
{
    m_Start = std::chrono::high_resolution_clock::now();
}

long long CTimer::Duration()
{
    Milli_t current = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(current - m_Start);

    return duration.count();
}
