#include "ChatPrinter.h"

#include <iostream>

#include "../../protocol/messages/ChatMessage.h"

void ChatPrinter::handle(Message *msg) {
    const auto* chatMsg = dynamic_cast<ChatMessage*>(msg);
    std::cout << "[" << chatMsg->getNickname() << "]: " << chatMsg->getContent() << "\n";
}
