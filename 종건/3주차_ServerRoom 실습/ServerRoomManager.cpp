#pragma once
#include "ServerRoomManager.h"

ServerRoomManager* ServerRoomManager::_instance = nullptr;

ServerRoom::ServerRoom()
{
	clear();
}

ServerRoom::~ServerRoom()
{
	clear();
}

void ServerRoom::setRoomInfo(const byte roomNo, const string& roomName)
{
	_roomNo = roomNo;
	_roomName = roomName;
}

void ServerRoom::clear()
{
	lock_guard<recursive_mutex> lock(_roomLock);
	_playerList.clear();
	_checkOverlapPlayerList.clear();
	_startTime = 0;
	_clearTime = 0;

	cout << "Thread(" << std::this_thread::get_id() << ") / Room(" << static_cast<int>(_roomNo) << ") 초기화" << endl;
}

bool ServerRoom::isPlayingRoom__(ULONGLONG currentTickCount)
{
	lock_guard<recursive_mutex> lock(_roomLock);
	if (_startTime <= currentTickCount && currentTickCount < _clearTime)
		return true;

	return false;
}

bool ServerRoom::addPlayer(Player* player)
{
	if (player == nullptr)
		return false;

	ULONGLONG	currentTickCount = GetTickCount64();
	bool		start = false;
	{
		lock_guard<recursive_mutex> lock(_roomLock);

		int playerCount = static_cast<int>(_playerList.size());
		if (playerCount >= 5)
			return false;

		if (isPlayingRoom__(currentTickCount) == true)
			return false;

		// 중복되서 들어가는 player가 있다.
		
		auto findItor = _checkOverlapPlayerList.find(player);
		if (findItor == _checkOverlapPlayerList.end())
		{
			_checkOverlapPlayerList.insert(player);
		}
		else
		{
			cout << "중복" << endl; 
		}

		_playerList.emplace_back(player);

		if (playerCount >= 4)
		{
			_startTime = currentTickCount;
			_clearTime = _startTime + 100;

			start = true;
		}
	}

	{
		//https://stackoverflow.com/questions/58710090/why-does-a-lock-guard-on-a-mutex-reference-produce-c26110
		//lock_guard<recursive_mutex> lock(player->getLock());
		lock_guard<recursive_mutex> playerLock(player->_playerLock);
		player->setEnteredRoomNo__(_roomNo);
		player->_isMatching = false;

		cout << "Thread(" << std::this_thread::get_id() << ") / Player(" << player->getPlayerNo() << ") Room(" << static_cast<int>(_roomNo) << ") 입장" << endl;
	}

	if(start == true)
		cout << "Thread(" << std::this_thread::get_id() << ") / Room(" << static_cast<int>(_roomNo) << ") 게임 시작, 100ms 이후 초기화 됩니다." << endl;

	return true;
}

void ServerRoom::update()
{
	ULONGLONG currentTickCount = GetTickCount64();

	list<Player*> playerList;
	{
		lock_guard<recursive_mutex> lock(_roomLock);
		if (_playerList.size() != 5)
			return;

		if (isPlayingRoom__(currentTickCount) == true)
			return;

		if (_clearTime > currentTickCount)
			return;

		playerList = _playerList;
		_playerList.clear();
		_checkOverlapPlayerList.clear();
		//for (auto player : _playerList)
		//{
		//	lock_guard<recursive_mutex> lock(player->_playerLock);
		//
		//	player->varyClearCount__(1);
		//	player->setEnteredRoomNo__(0);
		//}
	}

	{
		for (auto player : playerList)
		{
			lock_guard<recursive_mutex> lock(player->_playerLock);
		
			player->varyClearCount__(1);
			player->setEnteredRoomNo__(0);
			player->setReStartTime__(currentTickCount + 100);
		}
	}

	// 방 초기화
	clear();
}

void Player::setPlayerNo(const int playerNo)
{
	_playerNo = playerNo;
}

int Player::getPlayerNo()
{
	return _playerNo;
}

bool Player::isFinished__()
{
	if (_clearCount >= 5)
		return true;

	return false;
}

void Player::setEnteredRoomNo__(const byte roomNo)
{
	_enteredRoomNo = roomNo;
}

void Player::varyClearCount__(const byte vary)
{	
	_clearCount += vary;
}

const byte Player::getEnteredRoomNo__()
{
	return _enteredRoomNo;
}

void Player::setReStartTime__(const ULONGLONG restartTime)
{
	_reStartTime = restartTime;
}

const ULONGLONG Player::getReStartTime__()
{
	return _reStartTime;
}

bool ServerRoomManager::open(const int openRoomCount)
{
	_roomList.reserve(openRoomCount);

	for (int count = 0; count < openRoomCount; ++count)
	{
		ServerRoom* newServerRoom = new ServerRoom();
		if (newServerRoom == nullptr)
			return false;

		string roomName;
		roomName.resize(32);
		sprintf_s((char*)roomName.c_str(), 32, "room:%d", count + 1);

		newServerRoom->setRoomInfo(count + 1, roomName);

		_roomList.emplace_back(newServerRoom);
	}

	return true;
}

void ServerRoomManager::findAndEnterRoom(Player* player)
{
	//recursive_mutex		_roomLock;

	const ULONGLONG currentTime = GetTickCount64();

	for (auto room : _roomList)
	{
		{
			lock_guard<recursive_mutex> lock(room->_roomLock);
			if (room->isPlayingRoom__(currentTime) == true)
				continue;
		}

		if (room->addPlayer(player) == false)
			continue;

		break;
	}
}

void ServerRoomManager::updateServerRooms()
{
	for (auto room : _roomList)
	{
		room->update();
	}
}
