#ifndef CONEXAO98_SERVERLISTENER_H
#define CONEXAO98_SERVERLISTENER_H

#include <winsock2.h>

class ServerListener {
public:
    virtual ~ServerListener() = default;

    virtual void onIncomingConnection(SOCKET clientSock, sockaddr_in socketData) = 0;
};

#endif //CONEXAO98_SERVERLISTENER_H