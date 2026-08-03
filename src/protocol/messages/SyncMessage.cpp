//
// Created by Emilson Filho on 03/08/2026.
//

#include "SyncMessage.h"

SyncMessage::SyncMessage(const std::vector<std::pair<std::string, UserColor>>& onlineUsers)
    : onlineUsers(onlineUsers) {}

MessageType SyncMessage::getType() {
    return MessageType::SYNC;
}

ByteArray SyncMessage::serialize() {
    ByteArray packet;

    const char type = static_cast<char>(getType());
    packet.write(&type, 1);

    const uint16_t userCount = onlineUsers.size();
    packet.write(&userCount, sizeof(uint16_t));

    for (const auto& [userNickname, userColor] : onlineUsers) {
        // Color
        const uint8_t colorByte = static_cast<uint8_t>(userColor);
        packet.write(&colorByte, 1);

        // Nickname
        const uint16_t nickSize = userNickname.size();
        packet.write(&nickSize, sizeof(uint16_t));

        if (nickSize > 0)
            packet.write(userNickname.data(), nickSize);
    }

    return packet;
}

const std::vector<std::pair<std::string, UserColor>>& SyncMessage::getOnlineUsers() const {
    return onlineUsers;
}
