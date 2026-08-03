#include "ChatManager.h"

#include "../common/logger/Logger.h"
#include "../protocol/messages/SyncMessage.h"
#include "handlers/ChatHandler.h"
#include "handlers/JoinHandler.h"

void ChatManager::initializeHandlers() {
    messageHandlers.emplace(
        MessageType::CHAT,
        std::make_unique<ChatHandler>()
    );

    messageHandlers.emplace(
        MessageType::JOIN,
        std::make_unique<JoinHandler>()
    );
}

void ChatManager::broadcast(Message *msg, const UserSession& ignoreSession) {
    withSessionsLock([&ignoreSession, &msg](auto& sessions) -> void {
        for (auto& [id, session] : sessions) {
            if (!session) continue;

            if (session.get() != &ignoreSession)
                session->send(msg); // Avaliar a viablidade de um log aqui depoise
        }
    });
}

void ChatManager::onMessageReceived(Connection &conn, const ByteArray &data) {
    Logger::getLogger().debug("Teste de chegada no ChatManager onMessageReceived");
    std::unique_ptr<Message> msg = MessageFactory::create(data);

    if (msg == nullptr) {
        Logger::getLogger().error("Error while creating message in onMessageReceived");
        return;
    }

    UserSession* user = nullptr;

    withSessionsLock([&user, &conn](auto& sessions) -> void {
        const auto it = sessions.find(conn.getId());
        if (it == sessions.end())
            return;

        user = it->second.get();
    });

    if (user) {
        if (const auto itHandler = messageHandlers.find(msg->getType()); itHandler != messageHandlers.end())
            itHandler->second->handle(this, *user, std::move(msg));
        else
            Logger::getLogger().error(std::string("Handler nao encontrado para o tipo ") + std::to_string(static_cast<int>(msg->getType())));
    }
}

void ChatManager::onIncomingConnection(Socket clientSock, sockaddr_in clientData) {
    ConnectionId id = nextConnectionId++;
    auto conn = std::make_unique<Connection>(id, clientSock, clientData, this);

    Connection* rawConn = conn.get();

    withSessionsLock([&id, &conn](auto& sessions) -> void {
        sessions.emplace(
            id,
            std::make_unique<UserSession>(std::move(conn))
        );
    });

    if (rawConn) rawConn->start();
}

void ChatManager::onDisconnected(Connection &conn) {
    const ConnectionId connId = conn.getId();

    {
        std::lock_guard<std::mutex> lock(sessionMutex);
        if (const auto it = sessions.find(connId); it != sessions.end()) {
            reaper.moveToGraveyard(std::move(it->second));
            sessions.erase(it);
        }
    }

    const std::vector<std::string> userList = getActiveUsers();
    SyncMessage syncMsg(userList);

    withSessionsLock([&syncMsg](auto& activeSessions) -> void {
        for (auto& [id, session] : activeSessions) {
            if (session) session->send(&syncMsg);
        }
    });
}

std::vector<std::string> ChatManager::getActiveUsers() {
    std::vector<std::string> activeUsers;

    withSessionsLock([&activeUsers](const auto& sessions) -> void {
        for (const auto& [id, session] : sessions) {
            if (session and !session->getNickname().empty()) {
                activeUsers.emplace_back(session->getNickname());
            }
        }
    });

    return activeUsers;
}
