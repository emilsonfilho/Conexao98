#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <cstring>

#pragma comment(lib, "Ws2_32.lib")

int main() {
    WSADATA wsadata;
    if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
        std::cerr << "Failed to initialize WinSock." << "\n";
        return 1;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Failed to create socket." << "\n";
        return 1;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sock, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) == SOCKET_ERROR) {
        std::cerr << "Failed to binding: " << WSAGetLastError() << "\n";
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    listen(sock, 5);

    std::cout << "Waiting for connections...\n";

    while (true) {
        sockaddr_in client{};
        socklen_t socklen = sizeof(client);

        const SOCKET clientSock = accept(sock, reinterpret_cast<sockaddr *>(&client), &socklen);

        if (clientSock == SOCKET_ERROR) {
            std::cerr << "Failed to accept connection from client." << "\n";
            closesocket(clientSock);
            WSACleanup();
            return 1;
        }

        std::cout << "Client connected:"
                  << inet_ntoa(client.sin_addr)
                  << "\n";

        std::cout << "Waiting for data...\n";

        char buffer[1024];
        const int iResult = recv(clientSock, buffer, 1024, 0);
        if (iResult > 0) {
            buffer[iResult] = '\0';
            std::cout << "Received: " << buffer << "\n";

            const auto response = "Message received";
            send(clientSock, response, static_cast<int>(strlen(response)), 0);

            closesocket(clientSock);
        } else if (iResult == 0) {
            std::cerr << "Connection closed." << "\n";
            closesocket(sock);
        } else {
            std::cerr << "Failed to receive: " << WSAGetLastError() << "\n";
            WSACleanup();
            closesocket(clientSock);
            return 1;
        }

        break;
    }

    closesocket(sock);
    WSACleanup();

    return 0;
}