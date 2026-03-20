//
// Created by Emilson Filho on 05/03/2026.
//

#include "ConsoleChatListener.h"

#include "../common/logger/Logger.h"
#include "printers/ChatPrinter.h"
#include "printers/JoinPrinter.h"

ConsoleChatListener::ConsoleChatListener() {
    printers.emplace(MessageType::CHAT, std::make_unique<ChatPrinter>());
    printers.emplace(MessageType::JOIN, std::make_unique<JoinPrinter>());
}

void ConsoleChatListener::onMessageReceived(Connection &conn, const ByteArray &data) {
    const std::unique_ptr<Message> msg = MessageFactory::create(data);

    if (!msg) {
        Logger::getLogger().error("[CLIENT]: Malformed or unknown message payload received.");
        return;
    }

    if (const auto it = printers.find(msg->getType()); it != printers.end()) {
        it->second->handle(msg.get());
    } else {
        Logger::getLogger().error("[CLIENT]: Message of unknown type received");
    }
}

void ConsoleChatListener::onDisconnected(Connection& conn) {
    std::cout << "[CLIENT] Disconnected from the server.\n";
}