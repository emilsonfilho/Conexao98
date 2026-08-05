#include "JoinMessage.h"

JoinMessage::JoinMessage(const UserMetadata& meta): metadata(meta) {}

MessageType JoinMessage::getType() {
    return MessageType::JOIN;
}

ByteArray JoinMessage::serialize() {
    ByteArray packet;

    // Tipo da mensagem (JOIN)
    const char type = static_cast<char>(getType());
    packet.write(&type, 1);

    ByteArray metaBytes = metadata.serialize();

    if (metaBytes.size() > 0)
        packet.write(metaBytes.data(), metaBytes.size());

    return packet;
}

const UserMetadata& JoinMessage::getMetadata() const {
    return metadata;
}
