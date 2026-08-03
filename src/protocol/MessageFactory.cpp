#include <iostream>

#include "MessageFactory.h"

#include <cstring>

#include "../common/logger/Logger.h"
#include "messages/JoinMessage.h"
#include "messages/ChatMessage.h"
#include "messages/SyncMessage.h"

std::unique_ptr<Message> MessageFactory::create(const ByteArray &data) {



    char typeByte = data.data()[0];
    const auto type = static_cast<MessageType>(typeByte);

    if (type == MessageType::JOIN) {
        if (data.size() < 2) {
            Logger::getLogger().error("Malformed JoinMessage");
            return nullptr;
        }

        uint16_t nickSize;
        std::memcpy(&nickSize, data.data() + 1, sizeof(uint16_t));

        const std::string nick(data.data() + 3, nickSize);

        return std::make_unique<JoinMessage>(nick);
    }

    if (type == MessageType::CHAT) {
        if (data.size() < 3) {
            Logger::getLogger().error("Malformed ChatMessage");
            return nullptr;
        }

        uint16_t nickSize;
        std::memcpy(&nickSize, data.data() + 1, sizeof(uint16_t));

        const std::string nick(data.data() + 3, nickSize);

        const size_t textStart = 3 + nickSize;
        const std::string text(data.data() + textStart, data.size() - textStart);

        return std::make_unique<ChatMessage>(nick, text);
    }

    if (type == MessageType::SYNC) {
        size_t offset = 1;

        uint16_t userCount;
        std::memcpy(&userCount, data.data() + offset, sizeof(uint16_t));
        offset += sizeof(uint16_t);

        std::vector<std::string> users;

        for (uint16_t i = 0; i < userCount; i++) {
            uint16_t nickSize;
            std::memcpy(&nickSize, data.data() + offset, sizeof(uint16_t));
            offset += sizeof(uint16_t);

            std::string user(data.data() + offset, nickSize);
            users.push_back(user);

            offset += nickSize;
        }

        return std::make_unique<SyncMessage>(users);
    }

    Logger::getLogger().error("No MessageType corresponding");
    return nullptr;
}
