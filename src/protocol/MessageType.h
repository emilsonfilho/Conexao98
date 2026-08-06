#ifndef CONEXAO98_MESSAGETYPE_H
#define CONEXAO98_MESSAGETYPE_H

#include <cstdint>

enum class MessageType : uint8_t {
    JOIN,
    CHAT,
    SYNC,
    CHANGE_COLOR,
    LEAVE
};

#endif //CONEXAO98_MESSAGETYPE_H