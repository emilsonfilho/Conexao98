//
// Created by Emilson Filho on 06/03/2026.
//

#ifndef CONEXAO98_JOINPRINTER_H
#define CONEXAO98_JOINPRINTER_H
#include "IMessagePrinter.h"


class JoinPrinter : public ImessagePrinter {
public:
    void handle(Message *msg) override;
};


#endif //CONEXAO98_JOINPRINTER_H