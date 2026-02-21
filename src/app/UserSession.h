
#ifndef CONEXAO98_USERSESSION_H
#define CONEXAO98_USERSESSION_H

#include "../network/Connection.h"
#include "../protocol/Message.h"

class UserSession {
private:
    Connection* connection;
    std::string nickname;
public:
    explicit UserSession(Connection* conn);

    void setNickname(const std::string& nick);
    std::string getNickname() const;

    Connection* getConnection() const;

    void send(Message* msg) const;
};


#endif //CONEXAO98_USERSESSION_H