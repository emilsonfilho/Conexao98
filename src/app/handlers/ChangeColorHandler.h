//
// Created by Emilson Filho on 05/08/2026.
//

#ifndef CONEXAO98_CHANGECOLORHANDLER_H
#define CONEXAO98_CHANGECOLORHANDLER_H
#include "MessageHandler.h"


class ChangeColorHandler : public MessageHandler {
public:
    void handle(ChatManager *manager, UserSession& session, std::unique_ptr<Message> msg) override;
};


#endif //CONEXAO98_CHANGECOLORHANDLER_H