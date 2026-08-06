//
// Created by Emilson Filho on 06/08/2026.
//

#include "LeaveMessage.h"

LeaveMessage::LeaveMessage(const UserMetadata &meta): metadata(meta) {}

MessageType LeaveMessage::getType() {
    return MessageType::LEAVE;
}

ByteArray LeaveMessage::serialize() {
    ByteArray packet;

    const char type = static_cast<char>(getType());
    packet.write(&type, 1);

    ByteArray metaBytes = metadata.serialize();
    if (metaBytes.size() > 0)
        packet.write(metaBytes.data(), metaBytes.size());

    return packet;
}

UserMetadata LeaveMessage::getMetadata() const {
    return metadata;
}
