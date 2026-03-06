#ifndef CONEXAO98_IMESSAGEPRINTER_H
#define CONEXAO98_IMESSAGEPRINTER_H

#include "../../protocol/Message.h"

class IMessagePrinter {
public:
    virtual ~IMessagePrinter() = default;

    virtual void handle(Message* msg) = 0;
};

#endif //CONEXAO98_IMESSAGEPRINTER_H