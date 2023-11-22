#pragma once
class CPlayer
{
public:
	CPlayer()
	{
		static int keyIndexer = 0;
		m_Key = keyIndexer++;
	}

	~CPlayer()
	{

	}

public:
	const int& GetKey() { return m_Key; }

private:
	int m_Key;
};

