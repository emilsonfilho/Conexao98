#include "ChatPrinter.h"

#include <iostream>

#include "../../protocol/messages/ChatMessage.h"

void ChatPrinter::handle(Message *msg) {
    const auto* chatMsg = dynamic_cast<ChatMessage*>(msg);

    if (chatMsg == nullptr)
        throw std::invalid_argument("ChatPrinter::handle received a non-ChatMessage instance");

    std::cout << "[" << chatMsg->getNickname() << "]: " << chatMsg->getContent() << "\n";
}
