#ifndef CONEXAO98_MESSAGE_H
#define CONEXAO98_MESSAGE_H

#include "MessageType.h"
#include "../common/ByteArray.h"

class Message {
public:
    virtual ~Message() = default;

    virtual MessageType getType() = 0;
    virtual ByteArray serialize() = 0;
};


#endif //CONEXAO98_MESSAGE_H