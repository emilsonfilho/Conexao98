#include "ChatHandler.h"

#include <iostream>

#include "../ChatManager.h"
#include "../../protocol/messages/ChatMessage.h"
#include "../../protocol/UserColor.h"

void ChatHandler::handle(ChatManager *manager, UserSession& session, const std::unique_ptr<Message> msg) {
    const auto chatMsg = static_cast<ChatMessage*>(msg.get());

    if (chatMsg == nullptr) return;

    const std::string nick = session.getNickname();
    const UserColor color = session.getColor();
    const std::string content = chatMsg->getContent();

    ChatMessage finalMsg(UserMetadata(nick, color), content); // com certeza, finalMsg tem o nickname

    manager->broadcast(&finalMsg, session);
}
