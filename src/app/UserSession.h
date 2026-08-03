
#ifndef CONEXAO98_USERSESSION_H
#define CONEXAO98_USERSESSION_H

#include <memory>

#include "../network/Connection.h"
#include "../protocol/Message.h"
#include "../protocol/UserColor.h"

class UserSession {
private:
    std::unique_ptr<Connection> conn;
    std::string nickname;
    UserColor color;
public:
    explicit UserSession(std::unique_ptr<Connection> conn);

    void setNickname(const std::string& nick);
    [[nodiscard]] std::string getNickname() const;

    void setColor(UserColor c);
    UserColor getColor() const;

    [[nodiscard]] Connection& getConnection() const;

    void send(Message* msg) const;
};


#endif //CONEXAO98_USERSESSION_H