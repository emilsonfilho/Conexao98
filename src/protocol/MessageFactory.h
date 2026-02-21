#ifndef CONEXAO98_MESSAGEFACTORY_H
#define CONEXAO98_MESSAGEFACTORY_H

#include "Message.h"

class MessageFactory {
public:
    static Message* create(const ByteArray& data);
};


#endif //CONEXAO98_MESSAGEFACTORY_H