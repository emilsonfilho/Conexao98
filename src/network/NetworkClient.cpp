#include "NetworkClient.h"

#include <iostream>
#include <ws2tcpip.h>

NetworkClient::NetworkClient(ConnectionListener *listener): sock(INVALID_SOCKET), listener(listener), wsaData(WSAData()) {}

void NetworkClient::connectToServer(const char *ip, uint16_t port) {
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "WSAStartup() failed \n";
        return;
    }

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cout << "Error creating socket.\n";
        return;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    inet_pton(AF_INET, ip, &address.sin_addr);

    if (connect(sock, reinterpret_cast<sockaddr *>(&address), sizeof(address)) == SOCKET_ERROR) {
        std::cerr << "Error connecting to server.\n";
        closesocket(sock);
        return;
    }
}


void NetworkClient::sendMessage(const char *message) const {
    const int result = send(sock, message, static_cast<int>(strlen(message)), 0);

    if (result == SOCKET_ERROR) {
        std::cerr << "Error writing to socket.\n";
        closesocket(sock);
        return;
    }
}
