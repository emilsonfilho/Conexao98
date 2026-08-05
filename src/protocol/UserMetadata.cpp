//
// Created by Emilson Filho on 05/08/2026.
//

#include "UserMetadata.h"

UserMetadata::UserMetadata(const std::string &nick, UserColor color) {
    setString(UserAttr::NICKNAME, nick);
    setColor(UserAttr::COLOR, color);
}

void UserMetadata::setString(const UserAttr attr, const std::string &value) {
    ByteArray data;
    data.write(value.c_str(), value.size());
    properties[attr] = data;
}

std::string UserMetadata::getString(const UserAttr attr) const {
    if (const auto it = properties.find(attr); it != properties.end()) {
        return {it->second.data(), it->second.size()};
    }
    return "";
}

void UserMetadata::setColor(const UserAttr attr, UserColor color) {
    const auto colorByte = static_cast<uint8_t>(color);
    ByteArray data;
    data.write(&colorByte, 1);
    properties[attr] = data;
}

UserColor UserMetadata::getColor(const UserAttr attr) const {
    if (const auto it = properties.find(attr); it != properties.end()) {
        return static_cast<UserColor>(it->second.data()[0]);
    }
    return UserColor::DEFAULT;
}

// Type-Length-Value (TLV) Protocol
ByteArray UserMetadata::serialize() const {
    ByteArray packet;

    const auto attrCount = static_cast<uint8_t>(properties.size());
    packet.write(&attrCount, 1);

    for (const auto& [attr, data] : properties) {
        const auto type = static_cast<uint8_t>(attr);
        packet.write(&type, 1);

        const auto length = static_cast<uint16_t>(data.size());
        packet.write(&length, 2);

        if (length > 0) packet.write(data.data(), length);
    }

    return packet;
}

UserMetadata UserMetadata::deserialize(const char *data, const size_t size, size_t &outBytesRead) {
    UserMetadata meta;
    size_t offset = 0;

    if (size < 1) return meta;

    const uint8_t attrCount = data[offset++];

    for (uint8_t i = 0; i < attrCount; i++) {
        if (offset + 3 > size) break; // Pacote corrompido

        // Type
        auto attr = static_cast<UserAttr>(data[offset++]);

        // Legth
        uint16_t length;
        std::memcpy(&length, data + offset, 2);
        offset += 2;

        if (offset + length > size) break; // Estouro de memória

        // Value
        ByteArray valueData;
        valueData.write(data + offset, length);
        meta.properties[attr] = valueData;

        offset += length;
    }

    outBytesRead = offset;
    return meta;
}
