#pragma once
class CAppManager
{
private:
	CAppManager();

public:
	~CAppManager();

public:
	static CAppManager* GetInstance()
	{
		static CAppManager* instance = nullptr;

		if (nullptr == instance)
		{
			instance = new CAppManager();
		}

		return instance;
	}
public:
	const bool IsTerminated() { return m_IsTerminated; }
	void SetTerminated() { m_IsTerminated = true; }

private:
	bool m_IsTerminated;
};