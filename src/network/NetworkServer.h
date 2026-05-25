#ifndef CONEXAO98_NETWORKSERVER_H
#define CONEXAO98_NETWORKSERVER_H

#include <atomic>

#include "ServerListener.h"
#include "../common/platform/SocketHelper.h"

class NetworkServer {
private:
    Socket sock;
    ServerListener* appListener;
    std::atomic<bool> isActive;
public:
    explicit NetworkServer(ServerListener* listen);

    void start(uint16_t port);
    void shutdown();
};


#endif //CONEXAO98_NETWORKSERVER_H