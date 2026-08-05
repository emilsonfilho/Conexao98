//
// Created by Emilson Filho on 03/08/2026.
//

#ifndef CONEXAO98_SYNCMESSAGE_H
#define CONEXAO98_SYNCMESSAGE_H

#include "../Message.h"
#include "../UserMetadata.h"

class SyncMessage : public Message {
private:
    std::vector<UserMetadata> onlineUsers;
public:
    explicit SyncMessage(const std::vector<UserMetadata>& onlineUsers);

    MessageType getType() override;
    ByteArray serialize() override;

    [[nodiscard]] const std::vector<UserMetadata>& getOnlineUsers() const;
};


#endif //CONEXAO98_SYNCMESSAGE_H