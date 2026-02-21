#ifndef CONEXAO98_CONNECTIONLISTENER_H
#define CONEXAO98_CONNECTIONLISTENER_H

#include "../common/ByteArray.h"

class Connection;

class ConnectionListener {
public:
    virtual ~ConnectionListener() = default;

    virtual void onConnectionCreated(Connection* conn) = 0;
    virtual void onMessageReceived(Connection& conn, const ByteArray& data) = 0;
    virtual void onDisconnected(Connection& conn) = 0;
};

#endif //CONEXAO98_CONNECTIONLISTENER_H