#ifndef CONEXAO98_CONNECTION_H
#define CONEXAO98_CONNECTION_H

#include <winsock2.h>
#include <string>
#include <atomic>

#include "ConnectionListener.h"
#include "../common/ByteArray.h"

class Connection {
private:
    SOCKET socket;
    sockaddr_in address;
    ConnectionListener* listener;
    std::atomic<bool> isRunning;
public:
    Connection(SOCKET sock, sockaddr_in addr, ConnectionListener* listen);

    void sendData(const ByteArray& data) const;
    void listen();
    void stop();

    [[nodiscard]] std::string getSenderId() const;
};

#endif //CONEXAO98_CONNECTION_H