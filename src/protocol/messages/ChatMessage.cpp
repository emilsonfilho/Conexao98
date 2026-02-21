#include "ChatMessage.h"

ChatMessage::ChatMessage(const std::string &content):
    senderNickname(""), content(content) {}

ChatMessage::ChatMessage(const std::string &senderNickname, const std::string &content):
    senderNickname(senderNickname), content(content) {}

MessageType ChatMessage::getType() {
    return MessageType::CHAT;
}

ByteArray ChatMessage::serialize() {
    ByteArray packet;

    const char type = static_cast<char>(getType());
    packet.write(&type, 1);

    const uint16_t nickSize = senderNickname.size();
    packet.write(&nickSize, sizeof(uint16_t));

    if (nickSize > 0)
        packet.write(senderNickname.data(), nickSize);

    packet.write(content.data(), content.size());

    return packet;
}

std::string ChatMessage::getNickname() const {
    return senderNickname;
}

std::string ChatMessage::getContent() const {
    return content;
}