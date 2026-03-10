#include "ChatManager.h"

#include <iostream>
#include <ostream>

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
    std::cout << "Teste de chegada no ChatManager onMessageReceived\n";
    std::unique_ptr<Message> msg = MessageFactory::create(data);

    if (msg == nullptr) {
        std::cout << "Error while creating message in onMessageReceived\n";
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
            std::cerr << "Handler nao encontrado para o tipo " << static_cast<int>(msg->getType()) << '\n';
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

    std::lock_guard<std::mutex> lock(sessionMutex);

    if (const auto it = sessions.find(connId); it != sessions.end()) {
        reaper.moveToGraveyard(std::move(it->second));
        sessions.erase(it);
    }
}