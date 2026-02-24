#ifndef CONEXAO98_CHATMANAGER_H
#define CONEXAO98_CHATMANAGER_H

#include <memory>
#include <unordered_map>

#include "UserSession.h"

#include "../network/ConnectionListener.h"
#include "../protocol/MessageFactory.h"
#include "handlers/MessageHandler.h"

class ChatManager : public ConnectionListener {
private:
    ConnectionId nextConnectionId = 1;

    std::unordered_map<ConnectionId, std::unique_ptr<UserSession>> sessions;
    std::unordered_map<MessageType, std::unique_ptr<MessageHandler>> messageHandlers;
public:
    ChatManager() = default;
    void initializeHandlers();

    void broadcast(Message* msg, const UserSession& ignoreSession);

    void onMessageReceived(Connection &conn, const ByteArray &data) override;
    void onConnectionCreated(std::unique_ptr<Connection> conn) override;
    void onDisconnected(Connection &conn) override;
};


#endif //CONEXAO98_CHATMANAGER_H