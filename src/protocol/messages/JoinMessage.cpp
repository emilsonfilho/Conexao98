#include "JoinMessage.h"

JoinMessage::JoinMessage(const std::string &nick, UserColor color): nickname(nick), color(color) {}

MessageType JoinMessage::getType() {
    return MessageType::JOIN;
}

ByteArray JoinMessage::serialize() {
    ByteArray packet;

    // Tipo da mensagem (JOIN)
    const char type = static_cast<char>(getType());
    packet.write(&type, 1);

    // Cor
    const uint8_t colorByte = static_cast<uint8_t>(getColor());
    packet.write(&colorByte, 1);

    // Tamanho do nick e texto
    const uint16_t nickSize = getNickname().size();
    packet.write(&nickSize, sizeof(uint16_t));

    if (nickSize > 0)
        packet.write(nickname.data(), nickSize);

    return packet;
}

std::string JoinMessage::getNickname() const {
    return nickname;
}

UserColor JoinMessage::getColor() const {
    return color;
}
