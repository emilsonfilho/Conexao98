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

    void onMessageReceived(Connection& conn, const ByteArray& data) override;

    void onDisconnected(Connection& conn) override;
};


#endif //CONEXAO98_CONSOLECHATLISTENER_H