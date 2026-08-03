//
// Created by Emilson Filho on 03/08/2026.
//

#ifndef CONEXAO98_SYNCMESSAGE_H
#define CONEXAO98_SYNCMESSAGE_H

#include "../Message.h"

class SyncMessage : public Message {
private:
    std::vector<std::string> onlineUsers;
public:
    explicit SyncMessage(const std::vector<std::string>& onlineUsers);

    MessageType getType() override;
    ByteArray serialize() override;

    [[nodiscard]] const std::vector<std::string>& getOnlineUsers() const;
};


#endif //CONEXAO98_SYNCMESSAGE_H