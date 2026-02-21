#ifndef CONEXAO98_JOINMESSAGE_H
#define CONEXAO98_JOINMESSAGE_H

#include "../Message.h"

class JoinMessage : public Message {
private:
    std::string nickname;
public:
    explicit JoinMessage(const std::string& nick);

    MessageType getType() override;
    ByteArray serialize() override;

    std::string getNickname() const;
};


#endif //CONEXAO98_JOINMESSAGE_H