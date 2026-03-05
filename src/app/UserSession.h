
#ifndef CONEXAO98_USERSESSION_H
#define CONEXAO98_USERSESSION_H

#include <memory>

#include "../network/Connection.h"
#include "../protocol/Message.h"

class UserSession {
private:
    std::unique_ptr<Connection> conn;
    std::string nickname;
public:
    explicit UserSession(std::unique_ptr<Connection> conn);

    void setNickname(const std::string& nick);
    std::string getNickname() const;

    Connection& getConnection() const;

    void send(Message* msg) const;
};


#endif //CONEXAO98_USERSESSION_H