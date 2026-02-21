#include <iostream>

#include "MessageFactory.h"

#include <cstring>

#include "messages/JoinMessage.h"
#include "messages/ChatMessage.h"

Message *MessageFactory::create(const ByteArray &data) {



    char typeByte = data.data()[0];
    const auto type = static_cast<MessageType>(typeByte);

    if (type == MessageType::JOIN) {
        if (data.size() < 2) {
            std::cout << "Malformed JoinMessage\n";
            return nullptr;
        }

        uint16_t nickSize;
        std::memcpy(&nickSize, data.data() + 1, sizeof(uint16_t));

        const std::string nick(data.data() + 3, nickSize);

        return new JoinMessage(nick);
    }

    if (type == MessageType::CHAT) {
        if (data.size() < 3) {
            std::cout << "Malformed ChatMessage\n";
            return nullptr;
        }

        uint16_t nickSize;
        std::memcpy(&nickSize, data.data() + 1, sizeof(uint16_t));

        const std::string nick(data.data() + 3, nickSize);

        const size_t textStart = 3 + nickSize;
        const std::string text(data.data() + textStart, data.size() - textStart);

        return new ChatMessage(nick, text);
    }

    std::cout << "No MessageType corresponding\n";
    return nullptr;
}
