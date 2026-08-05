#include "UserSession.h"

UserSession::UserSession(std::unique_ptr<Connection> conn) : conn(std::move(conn)) {}

void UserSession::setProfile(const UserMetadata &meta) {
    profile = meta;
}

const UserMetadata &UserSession::getProfile() const {
    return profile;
}

Connection& UserSession::getConnection() const {
    return *conn;
}

void UserSession::send(Message *msg) const {
    conn->sendData(msg->serialize());
}
