//
// Created by Emilson Filho on 06/03/2026.
//

#include "JoinPrinter.h"

#include <iostream>

#include "../../common/exceptions/ProtocolException.h"
#include "../../protocol/messages/JoinMessage.h"

std::string JoinPrinter::format(Message *msg) const {
    auto* joinMsg = dynamic_cast<JoinMessage*>(msg);

    if (!joinMsg)
        throw ProtocolException("JoinPrinter::handle received a non-JoinMessage instance");

    return + ">>> " + joinMsg->getNickname() + " entrou no servidor! <<<\n";
}
