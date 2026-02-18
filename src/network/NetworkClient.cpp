#include "NetworkClient.h"

#include <iostream>
#include <ws2tcpip.h>

#include "../common/ByteArray.h"

NetworkClient::NetworkClient(ConnectionListener *listener): conn(nullptr), listener(listener), wsaData(WSAData()) {}

NetworkClient::~NetworkClient() {
    delete conn;
}

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

    conn = new Connection(sock, address, this->listener);
}

void NetworkClient::sendMessage(const std::string& message) const {
    const ByteArray data(message);
    conn->sendData(ByteArray(message));
}
