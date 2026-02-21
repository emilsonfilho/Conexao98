#ifndef CONEXAO98_JOINHANDLER_H
#define CONEXAO98_JOINHANDLER_H

#include "MessageHandler.h"

class JoinHandler : public MessageHandler {
public:
    void handle(ChatManager *manager, UserSession *session, Message *msg) override;
};

#endif //CONEXAO98_JOINHANDLER_H