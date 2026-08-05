#ifndef CONEXAO98_CHATMESSAGE_H
#define CONEXAO98_CHATMESSAGE_H

#include "../Message.h"
#include "../UserColor.h"
#include "../UserMetadata.h"

class ChatMessage : public Message {
private:
    UserMetadata metadata;
    std::string content;
public:
    explicit ChatMessage(const std::string& content);
    ChatMessage(const UserMetadata& meta, const std::string &content);

    MessageType getType() override;
    ByteArray serialize() override;

    const UserMetadata& getMetadata() const;
    std::string getContent() const;
};


#endif //CONEXAO98_CHATMESSAGE_H