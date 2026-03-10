#ifndef CONEXAO98_SERVERLISTENER_H
#define CONEXAO98_SERVERLISTENER_H

#include "../common/Types.h"

class ServerListener {
public:
    virtual ~ServerListener() = default;

    virtual void onIncomingConnection(Socket clientSock, sockaddr_in socketData) = 0;
};

#endif //CONEXAO98_SERVERLISTENER_H