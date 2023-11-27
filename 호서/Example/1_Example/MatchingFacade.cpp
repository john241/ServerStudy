#include "MatchingFacade.h"
#include "PlayerManager.h"
#include "RoomManager.h"
#include "Room.h"
#include "Player.h"
#include "Config.h"
#include <vector>
#include <iostream>
#include "AppManager.h"
#include <list>

namespace MatchingFacade
{
	void MatchingOnce(int threadId)
	{
		std::list<CPlayer*> newList;

		CPlayerManager::GetInstance()->PopPlayerList(newList);

		if (true == newList.empty())
		{
			// 아직 할 수 없다.
			return;
		}

		CRoomManager::GetInstance()->Foreach(threadId, [&](CRoom* room)
		{
			CScopeLock roomLock(room->GetLock());

			if (true == room->IsJoinable())
			{
				room->AddPlayer(newList);

				if (true == room->IsRunable())
				{
					room->Foreach([](CPlayer* player)
					{
						player->Start();
					});

					room->Start();
				}

				return true;
			}

			return false;
		});

		// 남은거 다시 넣기
		for (auto itor = newList.begin(); itor != newList.end(); )
		{
			CPlayer* player = *itor;

			CPlayerManager::GetInstance()->PushPlayer(player);
		}
	}

	void RoomOnTimer(int threadId)
	{
		// 종료 관리
		{
			int finishCount = 0;
			std::vector<CPlayer*> reEnterList;
			CRoomManager::GetInstance()->Foreach(threadId, [&](CRoom* room)
			{
				if (true == room->IsFinish())
				{
					CScopeLock roomLock(room->GetLock());

					room->Foreach([&](CPlayer* player)
					{
						player->End();

						if (false == player->IsExitable())
						{
							reEnterList.push_back(player);
						}
						else
						{
							++finishCount;
						}
					});

					room->End();
				}

				return false;
			});

			if (true == CPlayerManager::GetInstance()->AddFinishCount(finishCount))
			{
				// 측정 종료
				CAppManager::GetInstance()->SetTerminated();
			}

			for (auto player : reEnterList)
			{
				CPlayerManager::GetInstance()->PushPlayer(player);
			}
		}
	}
}