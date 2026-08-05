#ifndef CONEXAO98_JOINMESSAGE_H
#define CONEXAO98_JOINMESSAGE_H

#include "../Message.h"
#include "../UserColor.h"
#include "../UserMetadata.h"

class JoinMessage : public Message {
private:
    UserMetadata metadata;
public:
    explicit JoinMessage(const UserMetadata& meta);

    MessageType getType() override;
    ByteArray serialize() override;

    const UserMetadata& getMetadata() const;
};


#endif //CONEXAO98_JOINMESSAGE_H