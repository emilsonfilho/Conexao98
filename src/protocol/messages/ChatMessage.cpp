#include "ChatMessage.h"

ChatMessage::ChatMessage(const std::string &content):
    senderNickname(""), content(content) {}

ChatMessage::ChatMessage(const std::string &senderNickname, const UserColor color, const std::string &content):
    senderNickname(senderNickname), color(color), content(content) {}

MessageType ChatMessage::getType() {
    return MessageType::CHAT;
}

ByteArray ChatMessage::serialize() {
    ByteArray packet;

    // Tipo
    const char type = static_cast<char>(getType());
    packet.write(&type, 1);

    // Cor
    const auto colorByte = static_cast<uint8_t>(color);
    packet.write(&colorByte, 1);

    // Dados
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

UserColor ChatMessage::getColor() const {
    return color;
}