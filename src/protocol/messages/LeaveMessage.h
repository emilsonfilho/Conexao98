//
// Created by Emilson Filho on 06/08/2026.
//

#ifndef CONEXAO98_LEAVEMESSAGE_H
#define CONEXAO98_LEAVEMESSAGE_H
#include "../Message.h"
#include "../UserMetadata.h"


class LeaveMessage : public Message {
private:
    UserMetadata metadata;
public:
    explicit LeaveMessage(const UserMetadata& meta);

    MessageType getType() override;
    ByteArray serialize() override;

    UserMetadata getMetadata() const;
};


#endif //CONEXAO98_LEAVEMESSAGE_H