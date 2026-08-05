#include "ChatPrinter.h"

#include <iostream>

#include "../../common/exceptions/ProtocolException.h"
#include "../../protocol/messages/ChatMessage.h"

std::string ChatPrinter::format(Message *msg) const {
    const auto* chatMsg = dynamic_cast<ChatMessage*>(msg);

    if (chatMsg == nullptr)
        throw ProtocolException("ChatPrinter::handle received a non-ChatMessage instance");

    return "[" + chatMsg->getMetadata().getString(UserAttr::NICKNAME) + "]: " + chatMsg->getContent() + "\n";
}
