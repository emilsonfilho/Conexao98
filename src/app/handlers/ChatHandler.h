#ifndef CONEXAO98_CHATHANDLER_H
#define CONEXAO98_CHATHANDLER_H

#include <memory>

#include "MessageHandler.h"

class ChatHandler : public MessageHandler {
    void handle(ChatManager *manager, UserSession *session, std::unique_ptr<Message> msg) override;
};


#endif //CONEXAO98_CHATHANDLER_H