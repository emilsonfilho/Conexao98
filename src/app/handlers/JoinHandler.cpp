#include "JoinHandler.h"

#include "../ChatManager.h"
#include "../../protocol/messages/JoinMessage.h"

void JoinHandler::handle(ChatManager *manager, UserSession& session, const std::unique_ptr<Message> msg) {
    const auto joinMsg = static_cast<JoinMessage*>(msg.get());
    if (joinMsg == nullptr) return;

    session.setNickname(joinMsg->getNickname());

    manager->broadcast(joinMsg, session);
}
