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
    for (auto& [user, session] : sessions) {
        std::cout << "Avaliando " << session->getNickname() << '\n';
        if (session.get() != &ignoreSession)
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

    UserSession& user = *sessions.at(&conn);

    if (auto itHandler = messageHandlers.find(msg->getType()); itHandler != messageHandlers.end())
        itHandler->second->handle(this, user, std::move(msg));
    else
        std::cerr << "Handler nao encontrado para o tipo " << static_cast<int>(msg->getType()) << '\n';
}

void ChatManager::onConnectionCreated(std::unique_ptr<Connection> conn) {
    Connection* rawId = conn.get();

    rawId->start();

    sessions.emplace(
        rawId,
        std::make_unique<UserSession>(std::move(conn))
    );
}

void ChatManager::onDisconnected(Connection &conn) {
    const std::unique_ptr<UserSession> user = std::move(sessions.at(&conn));

    sessions.erase(&conn);
}
