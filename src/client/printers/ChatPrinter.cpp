#include "ChatPrinter.h"

#include <iostream>

#include "../../common/exceptions/ProtocolException.h"
#include "../../protocol/messages/ChatMessage.h"

void ChatPrinter::handle(Message *msg) {
    const auto* chatMsg = dynamic_cast<ChatMessage*>(msg);

    if (chatMsg == nullptr)
        throw ProtocolException("ChatPrinter::handle received a non-ChatMessage instance");

    std::cout << "[" << chatMsg->getNickname() << "]: " << chatMsg->getContent() << "\n";
}
