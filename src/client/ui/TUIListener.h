//
// Created by Emilson Filho on 22/07/2026.
//

#ifndef CONEXAO98_TUILISTENER_H
#define CONEXAO98_TUILISTENER_H
#include "ChatPresenter.h"
#include "../../network/ConnectionListener.h"
#include "../../protocol/MessageType.h"
#include "../printers/IMessagePrinter.h"


class TUIListener : public ConnectionListener {
private:
    ChatPresenter& presenter;
    std::unordered_map<MessageType, std::unique_ptr<IMessagePrinter>> printers;
public:
    TUIListener(ChatPresenter& presenter);

    void onMessageReceived(Connection &conn, const ByteArray &data) override;
    void onDisconnected(Connection &conn) override;
};


#endif //CONEXAO98_TUILISTENER_H