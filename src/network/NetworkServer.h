#ifndef CONEXAO98_NETWORKSERVER_H
#define CONEXAO98_NETWORKSERVER_H

#include <winsock2.h>
#include <atomic>
#include <vector>

#include "ConnectionListener.h"
#include "Connection.h"

class NetworkServer {
private:
    SOCKET sock;
    ConnectionListener* appListener;
    std::atomic<bool> isActive;
public:
    NetworkServer(ConnectionListener* listen);

    void start(uint16_t port);
};


#endif //CONEXAO98_NETWORKSERVER_H