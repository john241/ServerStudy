#include "MatchingFacade.h"
#include "PlayerManager.h"
#include "RoomManager.h"
#include "Room.h"
#include "Player.h"
#include "Config.h"
#include <vector>
#include <iostream>

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

		CRoomManager::GetInstance()->Foreach([&](CRoom* room) 
		{
			if (true == room->IsJoinable())
			{
				std::cout << "threadId : " << threadId << ", player( " << newPlayer->GetId() << " ) Room( " << room->GetId() << " ) Add Player And Check Room" << std::endl;
				room->AddPlayer(newPlayer);

				if (true == room->IsRunable())
				{
					room->Start();

					room->Foreach([](CPlayer* player)
					{
						player->Start();
					});
				}

				return true;
			}

			return false;
		});
	}

	void RoomOnTimer()
	{
		CRoomManager::GetInstance()->Foreach([](CRoom* room)
		{
			if (true == room->IsFinish())
			{
				room->End();

				room->Foreach([](CPlayer* player)
				{
					player->End();

					if (false == player->IsExitable())
					{
						CPlayerManager::GetInstance()->PushPlayer(player);
					}
				});
			}

			return false;
		});
	}
}