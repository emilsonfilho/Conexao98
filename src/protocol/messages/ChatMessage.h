#ifndef CONEXAO98_CHATMESSAGE_H
#define CONEXAO98_CHATMESSAGE_H

#include "../Message.h"

class ChatMessage : public Message {
private:
    std::string senderNickname;
    std::string content;
public:
    explicit ChatMessage(const std::string& content);
    ChatMessage(const std::string &senderNickname, const std::string &content);

    MessageType getType() override;
    ByteArray serialize() override;

    std::string getNickname() const;
    std::string getContent() const;
};


#endif //CONEXAO98_CHATMESSAGE_H