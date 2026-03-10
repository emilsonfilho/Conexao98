#include <memory>
#include <iostream>

#include "NetworkServer.h"

#include "../common/exceptions/NetworkException.h"


NetworkServer::NetworkServer(ServerListener* listen): appListener(listen), isActive(false) {
        this->sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void NetworkServer::start(uint16_t port) {
        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = SocketHelper::hostToNetworkShort(port);
        addr.sin_addr.s_addr = htonl(INADDR_ANY);

        if (bind(sock, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) == SOCKET_ERR) {
                SocketHelper::closeSocket(sock);
                throw NetworkException("Falha ao startar o servidor. Codigo de erro: " + std::to_string(SocketHelper::getLastError()) + ".\n");
        }

        listen(sock, 5);
        isActive = true;

        while (isActive) {
                sockaddr_in client{};
                socklen_t clientLen = sizeof(client);

                const Socket clientSock = accept(sock, reinterpret_cast<sockaddr *>(&client), &clientLen);
                if (clientSock == SOCKET_ERR) {
                        if (!isActive) {
                                std::cout << "Servidor desligado com sucesso.\n";
                                break;
                        }

                        std::cerr << "Falha ao aceitar cliente. Ignorando... Erro: " << SocketHelper::getLastError() << "\n";
                        continue;
                }

                std::cout << "Client connected:"
                         << SocketHelper::inetToAddress(client)
                         << "\n";

                appListener->onIncomingConnection(clientSock, client);
        }
}

void NetworkServer::shutdown() {
        isActive = false;

        if (sock != INVALID_SOCKET_FD) {
                SocketHelper::closeSocket(sock);
                sock = INVALID_SOCKET_FD;
        }
}
