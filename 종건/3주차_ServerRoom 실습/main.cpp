#include "preDefine.h"
#include "ServerRoomManager.h"

const int playerCount = 10000;
const int roomCount = 100;

const int playerThreadCount = 6;
const int roomThreadCount = 1;

//const int MaxCount = 150000;
//const int ThreadCount = 4;

void main(void)
{
    vector<Player*> playerList;
    playerList.reserve(playerCount);

    for (int count = 0; count < playerCount; ++count)
    {
        Player* newPlayer = new Player();
        newPlayer->setPlayerNo(count);

        playerList.emplace_back(newPlayer);
    }
 
    ServerRoomManager* serverRoomManager = ServerRoomManager::getInstance();
    serverRoomManager->open(roomCount);

    vector<shared_ptr<thread>> playerThreads;
    vector<shared_ptr<thread>> roomThreads;

    bool playerThreadisStop = false;

    auto playerThreadFunc = [&]()
    {
        while (true)
        {
            const ULONGLONG currentTime = GetTickCount64();
            /* thread_local 쓰지 않으면 deadlock */
            thread_local int isFinishedPlayerCount = 0;
            for (auto player : playerList)
            {
                {
                    lock_guard<recursive_mutex> lock(player->_playerLock);
                    if (player->_isMatching == true)
                        continue;

                    if (player->getReStartTime__() >= currentTime)
                        continue;

                    if (player->getEnteredRoomNo__() != 0 )
                        continue;

                    if (player->isFinished__() == true)
                    {
                        ++isFinishedPlayerCount;
                        continue;
                    }

                    player->setReStartTime__(0);
                    player->_isMatching = true;
                }

                serverRoomManager->findAndEnterRoom(player);
            }

            if (isFinishedPlayerCount >= 9995)
                break;
        }
    };

    auto roomUpdateThreadFunc = [&]()
    {
        while (true)
        {
            if (playerThreadisStop == true)
                break;

            serverRoomManager->updateServerRooms();
        }
    };

    auto t0 = chrono::system_clock::now();

    for (int i = 0; i < playerThreadCount; ++i)
    {
        shared_ptr<thread> thread(new thread(playerThreadFunc));
        playerThreads.emplace_back(thread);
    }

    for (int i = 0; i < roomThreadCount; ++i)
    {
        shared_ptr<thread> thread(new thread(roomUpdateThreadFunc));
        roomThreads.emplace_back(thread);
    }

    for (auto thread : playerThreads)
    {
        thread->join();
    }

    playerThreadisStop = true;

    for(auto thread : roomThreads)
    {
        thread->join();
    }

    auto t1 = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(t1 - t0).count();
    cout << "Took " << duration << " milliseconds." << endl;        

    //Player Thread 4, Room Thread 1
    // 43545ms, 43138ms, 42481ms

    //Player Thread 4, Room Thread 2
    // 42509ms, 43036ms, 43101ms

    //Player Thread 6, Room Thread 2
    // 45369ms,

    //Player Thread 2, Room Thread 2
    // 42682ms,

    //Player Thread 1, Room Thread 1 
    // 40552ms, 38763ms, ????




    // 2587ms
    // 4 threads : 735ms, 727ms, 785ms, 709ms, 675ms
    // 8 threads : 528ms, 624ms, 560ms, 692ms, 960ms
}
