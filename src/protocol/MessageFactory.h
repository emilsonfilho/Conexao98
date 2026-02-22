#ifndef CONEXAO98_MESSAGEFACTORY_H
#define CONEXAO98_MESSAGEFACTORY_H

#include <memory>

#include "Message.h"

class MessageFactory {
public:
    static std::unique_ptr<Message> create(const ByteArray& data);
};


#endif //CONEXAO98_MESSAGEFACTORY_H