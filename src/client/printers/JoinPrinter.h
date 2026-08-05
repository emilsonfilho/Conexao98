//
// Created by Emilson Filho on 06/03/2026.
//

#ifndef CONEXAO98_JOINPRINTER_H
#define CONEXAO98_JOINPRINTER_H
#include "IMessagePrinter.h"


class JoinPrinter : public IMessagePrinter {
public:
    std::string format(Message *msg) const override;
};


#endif //CONEXAO98_JOINPRINTER_H