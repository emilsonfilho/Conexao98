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
