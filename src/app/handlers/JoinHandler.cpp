#include "JoinHandler.h"

#include "../ChatManager.h"
#include "../../protocol/messages/JoinMessage.h"
#include "../../protocol/messages/SyncMessage.h"

void JoinHandler::handle(ChatManager *manager, UserSession& session, const std::unique_ptr<Message> msg) {
    const auto joinMsg = static_cast<JoinMessage*>(msg.get());
    if (joinMsg == nullptr) return;

    session.setNickname(joinMsg->getNickname());
    session.setColor(joinMsg->getColor());

    manager->broadcast(joinMsg, session);

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    const std::vector<UserMetadata> userList = manager->getActiveUsers();

    SyncMessage syncMsg(userList);
    session.send(&syncMsg);

    manager->broadcast(&syncMsg, session);
}
