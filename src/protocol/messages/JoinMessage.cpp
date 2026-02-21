#include "JoinMessage.h"

JoinMessage::JoinMessage(const std::string &nick): nickname(nick) {}

MessageType JoinMessage::getType() {
    return MessageType::JOIN;
}

ByteArray JoinMessage::serialize() {
    ByteArray packet;

    const char type = static_cast<char>(getType());
    packet.write(&type, 1);

    const uint16_t nickSize = getNickname().size();
    packet.write(&nickSize, sizeof(uint16_t));

    if (nickSize > 0)
        packet.write(nickname.data(), nickSize);

    return packet;
}

std::string JoinMessage::getNickname() const {
    return nickname;
}