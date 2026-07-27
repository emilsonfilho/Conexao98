#include "TUIListener.h"

#include "../../common/logger/Logger.h"
#include "../../protocol/Message.h"
#include "../../protocol/MessageFactory.h"
#include "../printers/ChatPrinter.h"
#include "../printers/JoinPrinter.h"

TUIListener::TUIListener(ChatPresenter &presenter): presenter(presenter) {
    printers.emplace(MessageType::CHAT, std::make_unique<ChatPrinter>());
    printers.emplace(MessageType::JOIN, std::make_unique<JoinPrinter>());
}

void TUIListener::onMessageReceived(Connection &conn, const ByteArray &data) {
    const std::unique_ptr<Message> msg = MessageFactory::create(data);

    if (!msg) {
        Logger::getLogger().error("[CLIENT]: Malformed or unknown message payload received.");
        return;
    }

    if (const auto it = printers.find(msg->getType()); it != printers.end()) {
        std::string formattedMsg = it->second->format(msg.get());

        presenter.addMessage(formattedMsg);
    } else {
        Logger::getLogger().error("[CLIENT]: Unknown message type received.");
    }
}

void TUIListener::onDisconnected(Connection &conn) {
    presenter.addMessage("[Sistema]: Disconectado do servidor.");
}
