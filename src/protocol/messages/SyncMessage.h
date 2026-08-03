//
// Created by Emilson Filho on 03/08/2026.
//

#ifndef CONEXAO98_SYNCMESSAGE_H
#define CONEXAO98_SYNCMESSAGE_H

#include "../Message.h"
#include "../UserColor.h"

class SyncMessage : public Message {
private:
    std::vector<std::pair<std::string, UserColor>> onlineUsers;
public:
    explicit SyncMessage(const std::vector<std::pair<std::string, UserColor>>& onlineUsers);

    MessageType getType() override;
    ByteArray serialize() override;

    [[nodiscard]] const std::vector<std::pair<std::string, UserColor>>& getOnlineUsers() const;
};


#endif //CONEXAO98_SYNCMESSAGE_H