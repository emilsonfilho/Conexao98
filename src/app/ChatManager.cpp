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

void ChatManager::broadcast(Message *msg, const UserSession* ignoreSession) {
    for (auto& [user, session] : sessions) {
        std::cout << "Avaliando " << session->getNickname() << '\n';
        if (session != ignoreSession)
            session->send(msg);
    }
}

void ChatManager::onMessageReceived(Connection &conn, const ByteArray &data) {
    std::cout << "Teste de chegada no ChatManager onMessageReceived\n";
    Message* msg = MessageFactory::create(data);

    if (msg == nullptr) {
        std::cout << "Error while creating message in onMessageReceived\n";
        return;
    }

    UserSession* user = sessions.at(&conn);

    if (auto itHandler = messageHandlers.find(msg->getType()); itHandler != messageHandlers.end())
        itHandler->second->handle(this, user, msg);
    else
        std::cerr << "Handler nao encontrado para o tipo " << static_cast<int>(msg->getType()) << '\n';

    delete msg;
}

void ChatManager::onConnectionCreated(Connection *conn) {
    sessions.emplace(
        conn,
        new UserSession(conn)
    );
}

void ChatManager::onDisconnected(Connection &conn) {
    const UserSession* user = sessions.at(&conn);

    sessions.erase(&conn);

    delete user;
}
