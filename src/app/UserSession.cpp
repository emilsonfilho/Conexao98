#include "UserSession.h"

UserSession::UserSession(std::unique_ptr<Connection> conn) : conn(std::move(conn)), isActive(true) {}

void UserSession::setNickname(const std::string& nick) {
    nickname = nick;
}

std::string UserSession::getNickname() const {
    return nickname;
}

Connection& UserSession::getConnection() const {
    return *conn;
}

bool UserSession::isAlive() const {
    return isActive;
}

void UserSession::send(Message *msg) const {
    conn->sendData(msg->serialize());
}
