
#ifndef CONEXAO98_USERSESSION_H
#define CONEXAO98_USERSESSION_H

#include <memory>

#include "../network/Connection.h"
#include "../protocol/Message.h"
#include "../protocol/UserMetadata.h"

class UserSession {
private:
    std::unique_ptr<Connection> conn;
    UserMetadata profile;
public:
    explicit UserSession(std::unique_ptr<Connection> conn);

    void setProfile(const UserMetadata& meta);
    const UserMetadata& getProfile() const;

    [[nodiscard]] Connection& getConnection() const;
    void send(Message* msg) const;
};


#endif //CONEXAO98_USERSESSION_H