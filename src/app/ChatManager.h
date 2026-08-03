#ifndef CONEXAO98_CHATMANAGER_H
#define CONEXAO98_CHATMANAGER_H

#include <memory>
#include <mutex>
#include <unordered_map>

#include "ConnectionReaper.h"
#include "UserSession.h"

#include "../common/Types.h"
#include "../network/ConnectionListener.h"
#include "../network/ServerListener.h"
#include "../protocol/MessageFactory.h"
#include "handlers/MessageHandler.h"

class ChatManager : public ConnectionListener, public ServerListener {
private:
    std::atomic<ConnectionId> nextConnectionId = 1;
    std::mutex sessionMutex;
    std::unordered_map<ConnectionId, std::unique_ptr<UserSession>> sessions;

    std::unordered_map<MessageType, std::unique_ptr<MessageHandler>> messageHandlers;

    ConnectionReaper reaper = ConnectionReaper();

    template <typename Func>
    auto withSessionsLock(Func f) {
        std::unique_lock<std::mutex> lock(sessionMutex);
        return f(sessions);
    }
public:
    ChatManager() = default;
    void initializeHandlers();

    void broadcast(Message* msg, const UserSession& ignoreSession);

    void onMessageReceived(Connection &conn, const ByteArray &data) override;
    void onIncomingConnection(Socket clientSock, sockaddr_in clientData) override;
    void onDisconnected(Connection &conn) override;

    std::vector<std::pair<std::string, UserColor>> getActiveUsers();
};


#endif //CONEXAO98_CHATMANAGER_H