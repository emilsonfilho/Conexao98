//
// Created by Emilson Filho on 05/03/2026.
//

#include "ConsoleChatListener.h"

#include "printers/ChatPrinter.h"
#include "printers/JoinPrinter.h"

ConsoleChatListener::ConsoleChatListener() {
    printers.emplace(MessageType::CHAT, std::make_unique<ChatPrinter>());
    printers.emplace(MessageType::JOIN, std::make_unique<JoinPrinter>());
}

void ConsoleChatListener::onMessageReceived(Connection &conn, const ByteArray &data) {
    const std::unique_ptr<Message> msg = MessageFactory::create(data);

    if (!msg) {
        std::cerr << "[CLIENT]: Malformed or unknown message payload received.\n";
        return;
    }

    if (const auto it = printers.find(msg->getType()); it != printers.end()) {
        it->second->handle(msg.get());
    } else {
        std::cerr << "[CLIENT]: Message of unknown type received\n";
    }
}

void ConsoleChatListener::onDisconnected(Connection& conn) {
    std::cout << "[CLIENT] Disconnected from the server.\n";
}