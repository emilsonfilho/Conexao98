#ifndef CONEXAO98_CHATPRINTER_H
#define CONEXAO98_CHATPRINTER_H

#include "IMessagePrinter.h"


class ChatPrinter : public ImessagePrinter {
    void handle(Message *msg) override;
};


#endif //CONEXAO98_CHATPRINTER_H