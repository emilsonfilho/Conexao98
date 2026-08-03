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
        if (data.size() < 4) {
            Logger::getLogger().error("Malformed JoinMessage");
            return nullptr;
        }

        const uint8_t colorByte = data.data()[1];
        const auto color = static_cast<UserColor>(colorByte);

        uint16_t nickSize;
        std::memcpy(&nickSize, data.data() + 2, sizeof(uint16_t));

        const std::string nick(data.data() + 4, nickSize);

        return std::make_unique<JoinMessage>(nick, color);
    }

    if (type == MessageType::CHAT) {
        if (data.size() < 4) {
            Logger::getLogger().error("Malformed ChatMessage");
            return nullptr;
        }

        const uint8_t colorByte = data.data()[1];
        const auto color = static_cast<UserColor>(colorByte);

        uint16_t nickSize;
        std::memcpy(&nickSize, data.data() + 2, sizeof(uint16_t));

        const std::string nick(data.data() + 4, nickSize);

        const size_t textStart = 4 + nickSize;
        const std::string text(data.data() + textStart, data.size() - textStart);

        return std::make_unique<ChatMessage>(nick, color, text);
    }

    if (type == MessageType::SYNC) {
        if (data.size() < 3) {
            Logger::getLogger().error("Malformed SyncMessage");
            return nullptr;
        }

        size_t offset = 1;

        uint16_t userCount;
        std::memcpy(&userCount, data.data() + offset, sizeof(uint16_t));
        offset += sizeof(uint16_t);

        std::vector<std::pair<std::string, UserColor>> users;

        for (uint16_t i = 0; i < userCount; i++) {
            // Cor
            const uint8_t colorByte = data.data()[offset];
            const auto color = static_cast<UserColor>(colorByte);
            offset++;

            // Nickname
            uint16_t nickSize;
            std::memcpy(&nickSize, data.data() + offset, sizeof(uint16_t));
            offset += sizeof(uint16_t);

            std::string user(data.data() + offset, nickSize);
            users.emplace_back(user, color);

            offset += nickSize;
        }

        return std::make_unique<SyncMessage>(users);
    }

    Logger::getLogger().error("No MessageType corresponding");
    return nullptr;
}
