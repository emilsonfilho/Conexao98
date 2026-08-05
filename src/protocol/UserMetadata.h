//
// Created by Emilson Filho on 05/08/2026.
//

#ifndef CONEXAO98_USERMETADATA_H
#define CONEXAO98_USERMETADATA_H

#include <cstdint>
#include <cstring>
#include <unordered_map>

#include "UserColor.h"
#include "../common/ByteArray.h"

enum class UserAttr : uint8_t {
    NICKNAME = 1,
    COLOR = 2
};

class UserMetadata {
private:
    std::unordered_map<UserAttr, ByteArray> properties;
public:
    UserMetadata() = default;
    UserMetadata(const std::string& nick, UserColor color);

    void setString(UserAttr attr, const std::string& value);
    std::string getString(UserAttr attr) const;

    void setColor(UserAttr attr, UserColor color);
    UserColor getColor(UserAttr attr) const;

    ByteArray serialize() const;

    static UserMetadata deserialize(const char* data, size_t size, size_t& outBytesRead);
};

#endif //CONEXAO98_USERMETADATA_H