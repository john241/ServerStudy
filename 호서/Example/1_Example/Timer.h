#pragma once
#include <chrono>

using Milli_t = std::chrono::steady_clock::time_point;

class CTimer
{
public:
	CTimer();
	~CTimer();

public:
	void Start();
	long long Duration();

private:
	Milli_t m_Start;
};

