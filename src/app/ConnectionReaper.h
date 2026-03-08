//
// Created by Emilson Filho on 08/03/2026.
//

#ifndef CONEXAO98_CONNECTIONREAPER_H
#define CONEXAO98_CONNECTIONREAPER_H

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>

#include "UserSession.h"


class ConnectionReaper {
private:
    std::queue<std::unique_ptr<UserSession>> cleanupQueue;
    std::thread cleanupThread;
    std::mutex queueMutex;
    std::condition_variable queueCondition;
    std::atomic<bool> isServerActive;

    void cleanupLoop();
public:
    ConnectionReaper();
    ~ConnectionReaper();

    void moveToGraveyard(std::unique_ptr<UserSession> deadSession);
};


#endif //CONEXAO98_CONNECTIONREAPER_H