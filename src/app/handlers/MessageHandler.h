#ifndef CONEXAO98_MESSAGEHANDLER_H
#define CONEXAO98_MESSAGEHANDLER_H

#include <memory>

class ChatManager;
class UserSession;
class Message;

class MessageHandler {
public:
    virtual ~MessageHandler() = default;

    virtual void handle(ChatManager *manager, UserSession *session, std::unique_ptr<Message> msg) = 0;
};

#endif //CONEXAO98_MESSAGEHANDLER_H