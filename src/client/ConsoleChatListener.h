#ifndef CONEXAO98_CONSOLECHATLISTENER_H
#define CONEXAO98_CONSOLECHATLISTENER_H

#include <algorithm>
#include <iostream>
#include <unordered_map>

#include "../network/ConnectionListener.h"
#include "../protocol/MessageFactory.h"
#include "../protocol/MessageType.h"
#include "printers/IMessagePrinter.h"


class ConsoleChatListener : public ConnectionListener {
private:
    std::unordered_map<MessageType, std::unique_ptr<ImessagePrinter>> printers;
public:
    ConsoleChatListener();

    void onMessageReceived(Connection& conn, const ByteArray& data) override {
        const std::unique_ptr<Message> msg = MessageFactory::create(data);

        if (const auto it = printers.find(msg->getType()); it != printers.end()) {
            it->second->handle(msg.get());
        } else {
            std::cerr << "[CLIENT]: Message of unknown type received\n";
        }
    }

    void onDisconnected(Connection& conn) override {
        std::cout << "[CLIENT] Disconnected from the server.\n";
    }
};


#endif //CONEXAO98_CONSOLECHATLISTENER_H