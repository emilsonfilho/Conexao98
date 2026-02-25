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
    std::vector<UserSession*> sessionsSnapshot;

    withSessionsLock([&sessionsSnapshot, &ignoreSession](auto& sessions) -> void {
        for (auto& [id, session] : sessions) {
            if (session.get() != &ignoreSession)
                sessionsSnapshot.push_back(session.get());
        }
    });

    for (const UserSession* session : sessionsSnapshot) {
        // Avaliar a viabilidade de uma mensagem de log aqui
        if (session != &ignoreSession)
            session->send(msg);
    }
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

void ChatManager::onConnectionCreated(std::unique_ptr<Connection> conn) {
    ConnectionId id = nextConnectionId++;
    conn->setId(id);

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
    sessions.erase(connId);
}