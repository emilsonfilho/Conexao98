#ifndef CONEXAO98_NETWORKSERVER_H
#define CONEXAO98_NETWORKSERVER_H

#include <winsock2.h>
#include <atomic>

#include "Connection.h"
#include "ServerListener.h"

class NetworkServer {
private:
    SOCKET sock;
    ServerListener* appListener;
    std::atomic<bool> isActive;
public:
    explicit NetworkServer(ServerListener* listen);

    void start(uint16_t port);
    void shutdown();
};


#endif //CONEXAO98_NETWORKSERVER_H