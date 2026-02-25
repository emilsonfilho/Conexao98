#ifndef CONEXAO98_CONNECTION_H
#define CONEXAO98_CONNECTION_H

#include <winsock2.h>
#include <string>
#include <thread>
#include <atomic>

#include "ConnectionListener.h"
#include "../common/ByteArray.h"
#include "../common/Types.h"

class Connection {
private:
    ConnectionId id;
    SOCKET socket;
    sockaddr_in address;
    ConnectionListener* listener;
    std::thread listenerThread;
    std::atomic<bool> isActive;
public:
    Connection(ConnectionId id, SOCKET sock, sockaddr_in addr, ConnectionListener* listen);
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;
    Connection(Connection&&) = delete;
    Connection& operator=(Connection&&) = delete;
    ~Connection();

    void start();
    void sendData(const ByteArray& data) const;
    void listen();
    void stop();

    [[nodiscard]] std::string getSenderId() const;
    [[nodiscard]] ConnectionId getId() const;
};

#endif //CONEXAO98_CONNECTION_H