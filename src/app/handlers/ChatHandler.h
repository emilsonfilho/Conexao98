#ifndef CONEXAO98_CHATHANDLER_H
#define CONEXAO98_CHATHANDLER_H

#include "MessageHandler.h"

class ChatHandler : public MessageHandler {
    void handle(ChatManager *manager, UserSession *session, Message *msg) override;
};


#endif //CONEXAO98_CHATHANDLER_H