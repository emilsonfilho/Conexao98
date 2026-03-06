#ifndef CONEXAO98_IMESSAGEPRINTER_H
#define CONEXAO98_IMESSAGEPRINTER_H

#include "../../protocol/Message.h"

class ImessagePrinter {
public:
    virtual ~ImessagePrinter() = default;

    virtual void handle(Message* msg) = 0;
};

#endif //CONEXAO98_IMESSAGEPRINTER_H