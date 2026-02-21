#ifndef CONEXAO98_MESSAGEHANDLER_H
#define CONEXAO98_MESSAGEHANDLER_H

class ChatManager;
class UserSession;
class Message;

class MessageHandler {
public:
    virtual ~MessageHandler() = default;

    virtual void handle(ChatManager* manager, UserSession* session, Message* msg) = 0;
};

#endif //CONEXAO98_MESSAGEHANDLER_H