#include <iostream>

#include "MessageFactory.h"

#include <cstring>

#include "../common/logger/Logger.h"
#include "messages/JoinMessage.h"
#include "messages/ChatMessage.h"
#include "messages/SyncMessage.h"
#include "UserMetadata.h"
#include "messages/ChangeColorMessage.h"
#include "messages/LeaveMessage.h"

std::unique_ptr<Message> MessageFactory::create(const ByteArray &data) {
    char typeByte = data.data()[0];
    const auto type = static_cast<MessageType>(typeByte);

    if (type == MessageType::JOIN) {
        if (data.size() < 4) {
            Logger::getLogger().error("Malformed JoinMessage");
            return nullptr;
        }

        size_t bytesRead = 0;
        UserMetadata meta = UserMetadata::deserialize(data.data() + 1, data.size() - 1, bytesRead);

        return std::make_unique<JoinMessage>(meta);
    }

    if (type == MessageType::CHAT) {
        if (data.size() < 4) {
            Logger::getLogger().error("Malformed ChatMessage");
            return nullptr;
        }

        size_t bytesRead = 0;
        UserMetadata meta = UserMetadata::deserialize(data.data() + 1, data.size() - 1, bytesRead);

        const size_t textStart = bytesRead + 1;
        const std::string text(data.data() + textStart, data.size() - textStart);

        return std::make_unique<ChatMessage>(meta, text);
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

        std::vector<UserMetadata> usersMetadata;

        for (uint16_t i = 0; i < userCount; i++) {
            size_t bytesRead = 0;
            usersMetadata.push_back(
                UserMetadata::deserialize(data.data() + offset, data.size() - offset, bytesRead)
            );
            offset += bytesRead;
        }

        return std::make_unique<SyncMessage>(usersMetadata);
    }

    if (type == MessageType::CHANGE_COLOR) {
        if (data.size() < 2) {
            Logger::getLogger().error("Malformed ChangeColorMessage");
            return nullptr;
        }

        const uint8_t colorByte = data.data()[1];
        const auto color = static_cast<UserColor>(colorByte);

        return std::make_unique<ChangeColorMessage>(color);
    }

    if (type == MessageType::LEAVE) {
        if (data.size() < 4) {
            Logger::getLogger().error("Malformed LeaveMessage");
            return nullptr;
        }

        size_t bytesRead = 0;
        UserMetadata meta = UserMetadata::deserialize(data.data() + 1, data.size() - 1, bytesRead);
        return std::make_unique<LeaveMessage>(meta);
    }

    Logger::getLogger().error("No MessageType corresponding");
    return nullptr;
}
