#ifndef CONEXAO98_JOINHANDLER_H
#define CONEXAO98_JOINHANDLER_H

#include "MessageHandler.h"

class JoinHandler : public MessageHandler {
public:
    void handle(ChatManager *manager, UserSession& session, std::unique_ptr<Message> msg) override;
};

#endif //CONEXAO98_JOINHANDLER_H