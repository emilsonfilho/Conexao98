#ifndef CONEXAO98_CHATPRINTER_H
#define CONEXAO98_CHATPRINTER_H

#include "IMessagePrinter.h"

class ChatPrinter : public IMessagePrinter {
public:
    std::string format(Message *msg) const override;
};


#endif //CONEXAO98_CHATPRINTER_H