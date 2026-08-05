//
// Created by Emilson Filho on 05/08/2026.
//

#include "ChangeColorHandler.h"

#include "../ChatManager.h"
#include "../UserSession.h"
#include "../../protocol/messages/ChangeColorMessage.h"
#include "../../protocol/messages/SyncMessage.h"

void ChangeColorHandler::handle(ChatManager *manager, UserSession &session, const std::unique_ptr<Message> msg) {
    const auto changeColorMsg = static_cast<ChangeColorMessage*>(msg.get());

    if (!changeColorMsg) return;

    const UserColor newColor = changeColorMsg->getColor();

    UserMetadata meta = session.getProfile();
    meta.setColor(UserAttr::COLOR, newColor);
    session.setProfile(meta);

    SyncMessage syncMsg(manager->getActiveUsers());
    session.send(&syncMsg);

    manager->broadcast(&syncMsg, session);
}
