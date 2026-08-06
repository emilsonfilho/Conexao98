//
// Created by Emilson Filho on 06/08/2026.
//

#include "LeavePrinter.h"

#include "../../common/exceptions/ProtocolException.h"
#include "../../protocol/messages/LeaveMessage.h"

std::string LeavePrinter::format(Message *msg) const {
    const auto* leaveMsg = dynamic_cast<LeaveMessage*>(msg);

    if (!leaveMsg)
        throw ProtocolException("LeavePrinter::handle received a non-LeaveMessage instance");

    return "<<< " + leaveMsg->getMetadata().getString(UserAttr::NICKNAME) + " saiu do servidor! >>>\n";
}
