#include "ChatMessage.h"

ChatMessage::ChatMessage(const std::string &content):
    metadata(UserMetadata()), content(content) {}

ChatMessage::ChatMessage(const UserMetadata& meta, const std::string &content):
    metadata(meta), content(content) {}

MessageType ChatMessage::getType() {
    return MessageType::CHAT;
}

ByteArray ChatMessage::serialize() {
    ByteArray packet;

    const char type = static_cast<char>(getType());
    packet.write(&type, 1);

    ByteArray metaBytes = metadata.serialize();
    if (metaBytes.size() > 0)
        packet.write(metaBytes.data(), metaBytes.size());

    packet.write(content.data(), content.size());

    return packet;
}

const UserMetadata& ChatMessage::getMetadata() const {
    return metadata;
}

std::string ChatMessage::getContent() const {
    return content;
}
