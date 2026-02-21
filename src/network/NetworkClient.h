#ifndef CONEXAO98_NETWORKCLIENT_H
#define CONEXAO98_NETWORKCLIENT_H

#include <winsock2.h>

#include "ConnectionListener.h"
#include "Connection.h"
#include "../protocol/Message.h"

class NetworkClient {
private:
    Connection* conn;
    ConnectionListener* listener;
    WSADATA wsaData;
public:
    explicit NetworkClient(ConnectionListener* listener);
    ~NetworkClient();

    void connectToServer(const char* ip, uint16_t port);

    void sendMessage(Message* msg) const;
};


#endif //CONEXAO98_NETWORKCLIENT_H