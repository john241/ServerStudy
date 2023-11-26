#include "MatchingFacade.h"
#include "PlayerManager.h"
#include "RoomManager.h"
#include "Room.h"
#include "Player.h"
#include "Config.h"
#include <vector>
#include <iostream>
#include "AppManager.h"

static int g_EndPlayer = 0;

namespace MatchingFacade
{
	void MatchingOnce()
	{
		DWORD threadId = GetCurrentThreadId();
		CPlayer* newPlayer = CPlayerManager::GetInstance()->PopPlayer();

		if (nullptr == newPlayer)
		{
			return;
		}

		CRoom* readyRoom = nullptr;

		CRoomManager::GetInstance()->Foreach([&](CRoom* room) 
		{
			if (true == room->IsJoinable())
			{
				std::cout << "threadId : " << threadId << ", player( " << newPlayer->GetId() << " ) Room( " << room->GetId() << " ) Add Player And Check Room" << std::endl;
				room->AddPlayer(newPlayer);

				if (true == room->IsRunable())
				{
					readyRoom = room;
				}

				return true;
			}

			return false;
		});

		if (nullptr != readyRoom)
		{
			readyRoom->Foreach([](CPlayer* player)
			{
				player->Start();
			});

			readyRoom->Start();
		}
	}

	void RoomOnTimer()
	{
		std::vector<CPlayer*> reEnterList;
		CRoomManager::GetInstance()->Foreach([&](CRoom* room)
		{
			if (true == room->IsFinish())
			{
				room->Foreach([&](CPlayer* player)
				{
					player->End();

					if (false == player->IsExitable())
					{
						reEnterList.push_back(player);
					}
					else
					{
						++g_EndPlayer;
					}
				});

				room->End();
			}

			return false;
		});


		for (auto player : reEnterList)
		{
			CPlayerManager::GetInstance()->PushPlayer(player);
		}

		// 측정 종료
		if (PLAYER_COUNT - MAX_ENTRY_COUNT <= g_EndPlayer)
		{
			CAppManager::GetInstance()->SetTerminated();
		}
	}
}