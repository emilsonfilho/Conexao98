//
// Created by Emilson Filho on 05/08/2026.
//

#include "ChangeColorMessage.h"

ChangeColorMessage::ChangeColorMessage(UserColor newColor): newColor(newColor) {}

MessageType ChangeColorMessage::getType() {
    return MessageType::CHANGE_COLOR;
}

UserColor ChangeColorMessage::getColor() const {
    return newColor;
}

ByteArray ChangeColorMessage::serialize() {
    ByteArray packet;

    const char type = static_cast<char>(getType());
    packet.write(&type, 1);

    const auto color = static_cast<uint8_t>(getColor());
    packet.write(&color, 1);

    return packet;
}
