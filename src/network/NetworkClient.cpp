#include <ws2tcpip.h>
#include <thread>
#include <iostream>

#include "NetworkClient.h"
#include "../common/ByteArray.h"

NetworkClient::NetworkClient(ConnectionListener *listener): clientConnection(nullptr), appListener(listener), wsaData(WSAData()) {}

void NetworkClient::connectToServer(const char *ip, uint16_t port) {
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "WSAStartup() failed \n";
        return;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cout << "Error creating socket.\n";
        return;
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    inet_pton(AF_INET, ip, &address.sin_addr);

    if (connect(sock, reinterpret_cast<sockaddr *>(&address), sizeof(address)) == SOCKET_ERROR) {
        std::cerr << "Error connecting to server.\n";
        closesocket(sock);
        return;
    }

    clientConnection = std::make_unique<Connection>(0, sock, address, this);
    clientConnection->start();
}

void NetworkClient::sendMessage(Message* msg) const {
    if (!clientConnection) {
        std::cerr << "Cannot send message: no active client connection.\n";
        return;
    }

    clientConnection->sendData(msg->serialize());
}

void NetworkClient::onMessageReceived(Connection &conn, const ByteArray &data) {
    if (appListener) appListener->onMessageReceived(conn, data);
}

void NetworkClient::onDisconnected(Connection &conn) {
    if (appListener) appListener->onDisconnected(conn);
}
