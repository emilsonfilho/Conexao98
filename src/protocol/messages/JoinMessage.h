#ifndef CONEXAO98_JOINMESSAGE_H
#define CONEXAO98_JOINMESSAGE_H

#include "../Message.h"
#include "../UserColor.h"

class JoinMessage : public Message {
private:
    std::string nickname;
    UserColor color;
public:
    explicit JoinMessage(const std::string& nick, UserColor color);

    MessageType getType() override;
    ByteArray serialize() override;

    std::string getNickname() const;
    UserColor getColor() const;
};


#endif //CONEXAO98_JOINMESSAGE_H