#include "UserSession.h"

UserSession::UserSession(Connection *conn) {
    connection = conn;
}

void UserSession::setNickname(const std::string& nick) {
    nickname = nick;
}

std::string UserSession::getNickname() const {
    return nickname;
}

Connection* UserSession::getConnection() const {
    return connection;
}

void UserSession::send(Message *msg) const {
    connection->sendData(msg->serialize());
}
