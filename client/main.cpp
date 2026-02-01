#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <cstring>

#pragma comment(lib, "Ws2_32.lib")

int main() {
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize WinSock." << "\n";
        return 1;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Error creating socket: " << WSAGetLastError() << "\n";
        WSACleanup();
        return 1;
    }

    std::cout << "Socket created successfully.\n";

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    if (connect(sock, reinterpret_cast<sockaddr*>(&server), sizeof(server)) == SOCKET_ERROR) {
        std::cerr << "Error connecting to server: " << WSAGetLastError() << "\n";
        WSACleanup();
        closesocket(sock);
        return 1;
    }

    const auto msg = "Oi!";
    const int iResult = send(sock, msg, static_cast<int>(strlen(msg)), 0);

    if (iResult == SOCKET_ERROR) {
        std::cerr << "Error sending message: " << WSAGetLastError() << "\n";
        WSACleanup();
        closesocket(sock);
        return 1;
    }

    std::cout << "Message sent successfully.\n";

    char response[1024];
    const int iResponse = recv(sock, response, 1024, 0);
    if (iResponse > 0) {
        response[iResponse] = '\0';
        std::cout << "Response by server: " << response << "\n";
        closesocket(sock);
    } else if (iResponse == 0) {
        std::cerr << "Connection closed.\n";
        closesocket(sock);
    } else {
        std::cerr << "Error receiving message: " << WSAGetLastError() << "\n";
        WSACleanup();
        closesocket(sock);
        return 1;
    }

    closesocket(sock);
    WSACleanup();

    return 0;
}