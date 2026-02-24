#include "Connection.h"

#include <iostream>
#include <ws2tcpip.h>
#include <stdexcept>

Connection::Connection(const SOCKET sock, const sockaddr_in addr, ConnectionListener* listen):
socket(sock), address(addr), listener(listen), isActive(true) {}

Connection::~Connection() {
        stop();

        if (socket != INVALID_SOCKET) {
                shutdown(socket, SD_BOTH);
                closesocket(socket);
        }

        if (listenerThread.joinable() && listenerThread.get_id() != std::this_thread::get_id())
                listenerThread.join();
        else if (listenerThread.get_id() == std::this_thread::get_id())
                listenerThread.detach();
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
                const int errorCode = WSAGetLastError();

                std::cerr << "Erro enquanto enviava a mensagem.\n";
                closesocket(socket);

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
}