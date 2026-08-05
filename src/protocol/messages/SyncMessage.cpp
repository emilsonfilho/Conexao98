//
// Created by Emilson Filho on 03/08/2026.
//

#include "SyncMessage.h"

SyncMessage::SyncMessage(const std::vector<UserMetadata>& onlineUsers)
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

    for (const auto& metadata : onlineUsers) {
        ByteArray metaBytes = metadata.serialize();

        if (metaBytes.size() > 0)
            packet.write(metaBytes.data(), metaBytes.size());
    }

    return packet;
}

const std::vector<UserMetadata>& SyncMessage::getOnlineUsers() const {
    return onlineUsers;
}
