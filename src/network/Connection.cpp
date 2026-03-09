#include "Connection.h"

#include <iostream>
#include <ws2tcpip.h>
#include <stdexcept>

#include "../common/platform/SocketHelper.h"

Connection::Connection(ConnectionId id, const SOCKET sock, const sockaddr_in addr, ConnectionListener* listen):
id(id), socket(sock), address(addr), listener(listen), isActive(true) {}

Connection::~Connection() {
        stop();
        if (listenerThread.joinable()) listenerThread.join();
}

void Connection::start() {
        listenerThread = std::thread([this]() {
                this->listen();
        });
}

std::string Connection::getSenderId() const {
        char* ip = inet_ntoa(address.sin_addr);
        const u_long port = ntohs(address.sin_port);

        return std::string(ip) + ":" + std::to_string(port);
}

void Connection::sendData(const ByteArray& data) const {
        if (const int iResult = send(socket, data.data(), static_cast<int>(data.size()), 0); iResult == SOCKET_ERROR) {
                const int errorCode = SocketHelper::getLastError();

                std::cerr << "Erro enquanto enviava a mensagem.\n";
                SocketHelper::closeSocket(socket);

                throw std::runtime_error("Erro no sendData. Codigo Winsock: " + std::to_string(errorCode));
        }
}

void Connection::listen() {
        char buff[1025];

        while (isActive) {
                if (const int iResult = recv(socket, buff, 1024, 0); iResult > 0) {
                        ByteArray data;
                        data.write(buff, iResult);
                        if (listener) listener->onMessageReceived(*this, data);
                } else {
                        if (listener) listener->onDisconnected(*this);
                        return;
                }
        }
}

void Connection::stop() {
        isActive = false;

        if (socket != INVALID_SOCKET) {
                shutdown(socket, SD_BOTH);
                SocketHelper::closeSocket(socket);
                socket = INVALID_SOCKET;
        }
}

ConnectionId Connection::getId() const {
        return id;
}