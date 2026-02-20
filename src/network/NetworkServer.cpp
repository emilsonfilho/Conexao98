#include <ws2tcpip.h>
#include <stdexcept>
#include <iostream>

#include "NetworkServer.h"

NetworkServer::NetworkServer(ConnectionListener* listen): appListener(listen), isActive(false) {
        this->sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void NetworkServer::start(uint16_t port) {
        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = htonl(INADDR_ANY);

        if (bind(sock, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) == SOCKET_ERROR) {
                closesocket(sock);
                throw std::runtime_error("Falha ao startar o servidor. Codigo de erro: " + std::to_string(WSAGetLastError()) + ".\n");
        }

        listen(sock, 5);
        isActive = true;

        while (true) {
                sockaddr_in client{};
                socklen_t clientLen = sizeof(client);

                const SOCKET clientSock = accept(sock, reinterpret_cast<sockaddr *>(&client), &clientLen);
                if (clientSock == SOCKET_ERROR) {
                        closesocket(sock);
                        std::cerr << "Failed to accept connection from client. Erro: " << WSAGetLastError() << "\n";
                        continue;
                }

                std::cout << "Client connected:"
                         << inet_ntoa(client.sin_addr)
                         << "\n";

                Connection* newConn = new Connection(clientSock, client, appListener);

                activeConnections.push_back(newConn);
                newConn->listen();

                std::cout << "Client disconnected. Let's wait for another one.\n";

                delete newConn; // You'll delete this later
                activeConnections.clear();
        }
}
