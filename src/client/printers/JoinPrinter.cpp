//
// Created by Emilson Filho on 06/03/2026.
//

#include "JoinPrinter.h"

#include <iostream>

#include "../../protocol/messages/JoinMessage.h"

void JoinPrinter::handle(Message *msg) {
    auto* joinMsg = dynamic_cast<JoinMessage*>(msg);
    std::cout << ">>> " << joinMsg->getNickname() << " entrou no servidor! <<<\n";
}
