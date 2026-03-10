#ifndef CONEXAO98_NETWORKCLIENT_H
#define CONEXAO98_NETWORKCLIENT_H



#include "ConnectionListener.h"
#include "Connection.h"
#include "../protocol/Message.h"
#include "../common/platform/SocketHelper.h"

class NetworkClient : public ConnectionListener {
private:
    std::unique_ptr<Connection> clientConnection;
    ConnectionListener* appListener;
    WSADATA wsaData;
public:
    explicit NetworkClient(ConnectionListener* listener);

    void connectToServer(const char* ip, uint16_t port);

    void sendMessage(Message* msg) const;

    void onMessageReceived(Connection &conn, const ByteArray &data) override;
    void onDisconnected(Connection &conn) override;
};


#endif //CONEXAO98_NETWORKCLIENT_H