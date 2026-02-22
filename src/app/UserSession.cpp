#include "UserSession.h"

UserSession::UserSession(std::unique_ptr<Connection> conn) : conn(std::move(conn)) {}

void UserSession::setNickname(const std::string& nick) {
    nickname = nick;
}

std::string UserSession::getNickname() const {
    return nickname;
}

Connection& UserSession::getConnection() const {
    return *conn;
}

void UserSession::send(Message *msg) const {
    conn->sendData(msg->serialize());
}
