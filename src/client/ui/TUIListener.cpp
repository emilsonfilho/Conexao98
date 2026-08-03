#include "TUIListener.h"

#include "../../common/logger/Logger.h"
#include "../../protocol/Message.h"
#include "../../protocol/MessageFactory.h"
#include "../../protocol/messages/ChatMessage.h"
#include "../../protocol/messages/SyncMessage.h"
#include "../printers/ChatPrinter.h"
#include "../printers/JoinPrinter.h"

TUIListener::TUIListener(ChatPresenter &presenter): presenter(presenter) {
    printers.emplace(MessageType::JOIN, std::make_unique<JoinPrinter>());
}

void TUIListener::onMessageReceived(Connection &conn, const ByteArray &data) {
    const std::unique_ptr<Message> msg = MessageFactory::create(data);

    if (!msg) {
        Logger::getLogger().error("[CLIENT]: Malformed or unknown message payload received.");
        return;
    }

    if (msg->getType() == MessageType::SYNC) {
        if (const auto* syncMsg = static_cast<SyncMessage*>(msg.get()))
            presenter.setOnlineUsers(syncMsg->getOnlineUsers());

        return;
    }

    if (msg->getType() == MessageType::CHAT) {
        if (const auto* chatMsg = static_cast<ChatMessage*>(msg.get()))
            presenter.addMessage(chatMsg->getNickname(), chatMsg->getContent(), chatMsg->getColor());

        return;
    }

    if (const auto it = printers.find(msg->getType()); it != printers.end()) {
        std::string formattedMsg = it->second->format(msg.get());

        presenter.addMessage("Sistema", formattedMsg, UserColor::DEFAULT);
    } else {
        Logger::getLogger().error("[CLIENT]: Unknown message type received.");
    }
}

void TUIListener::onDisconnected(Connection &conn) {
    presenter.addMessage("Sistema", "Disconectado do servidor.", UserColor::DEFAULT);
}
