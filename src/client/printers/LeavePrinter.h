//
// Created by Emilson Filho on 06/08/2026.
//

#ifndef CONEXAO98_LEAVEPRINTER_H
#define CONEXAO98_LEAVEPRINTER_H
#include "IMessagePrinter.h"


class LeavePrinter : public IMessagePrinter {
public:
    std::string format(Message *msg) const override;
};


#endif //CONEXAO98_LEAVEPRINTER_H