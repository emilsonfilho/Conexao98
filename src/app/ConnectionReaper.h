//
// Created by Emilson Filho on 08/03/2026.
//

#ifndef CONEXAO98_CONNECTIONREAPER_H
#define CONEXAO98_CONNECTIONREAPER_H

#include <memory>
#include <mutex>
#include <queue>

#include "UserSession.h"


class ConnectionReaper {
private:
    std::queue<std::unique_ptr<UserSession>> cleanupQueue;
    std::thread cleanupThread;
    std::mutex queueMutex;
    std::atomic<bool> isServerActive;
public:
    ConnectionReaper();
    ~ConnectionReaper();

    void moveToGraveyard(std::unique_ptr<UserSession> deadSession);

    void cleanupLoop();
};


#endif //CONEXAO98_CONNECTIONREAPER_H