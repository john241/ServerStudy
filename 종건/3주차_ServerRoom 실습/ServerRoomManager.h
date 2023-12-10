#pragma once
#include "preDefine.h"
#include <winnt.h>

class Player
{
public:
	Player()
	{
		_enteredRoomNo = 0;
		_playerNo = 0;
		_clearCount = 0;
		_reStartTime = 0;
		_isMatching = false;
	}

public:
	//recursive_mutex& getLock() { return _playerLock; }
	void	setPlayerNo(const int playerNo);
	int		getPlayerNo();

	bool	isFinished__();
	void	varyClearCount__(const byte vary);

	const byte	getEnteredRoomNo__();
	void		setEnteredRoomNo__(const byte roomNo);

	void			setReStartTime__(const ULONGLONG restartTime);
	const ULONGLONG	getReStartTime__();

public:
	recursive_mutex _playerLock;
	bool			_isMatching;

private:
	ULONGLONG	_reStartTime;
	byte		_enteredRoomNo;
	byte		_clearCount;
	int			_playerNo;
};


class ServerRoom
{
public:
	ServerRoom();
	~ServerRoom();

public:
	void				setRoomInfo(const byte roomNo, const string& roomName);

	void				clear();
	bool				isPlayingRoom__(ULONGLONG currentTickCount);
	bool				addPlayer(Player* player);
	void				update();

public:
	recursive_mutex		_roomLock;

private:
	//CRITICAL_SECTION	_roomLock;

	byte				_roomNo;
	string				_roomName;
	list<Player*>		_playerList;
	set<Player*>		_checkOverlapPlayerList;
	ULONGLONG			_startTime;
	ULONGLONG			_clearTime;
};

class ServerRoomManager
{
private:
	static ServerRoomManager* _instance;
	ServerRoomManager() {}

public:
	static ServerRoomManager* getInstance()
	{
		if (_instance == nullptr)
			_instance = new ServerRoomManager();

		return _instance;
	}

public:
	bool	open(const int openRoomCount);

	void	findAndEnterRoom(Player* player);
	void	updateServerRooms();

private:
	//recursive_mutex		_roomLock;
	vector<ServerRoom*>	_roomList;
};