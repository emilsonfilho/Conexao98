#include "JoinHandler.h"

#include "../ChatManager.h"
#include "../../protocol/messages/JoinMessage.h"

void JoinHandler::handle(ChatManager *manager, UserSession *session, Message *msg) {
    const auto joinMsg = dynamic_cast<JoinMessage*>(msg);
    if (joinMsg == nullptr) return;

    session->setNickname(joinMsg->getNickname());

    manager->broadcast(joinMsg, session);
}
