//
// Created by Emilson Filho on 09/03/2026.
//

#include "SocketHelper.h"

bool SocketHelper::initSystem() {
    #ifdef _WIN32
        WSADATA wsaData;

        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
            return false;

    #endif
    return true;
}

void SocketHelper::cleanupSystem() {
    #ifdef _WIN32
        WSACleanup();
    #endif
}

void SocketHelper::shutdownSystem(const Socket sock) {
    shutdown(sock, SOCKET_SHUTDOWN_BOTH);
}

void SocketHelper::closeSocket(Socket sock) {
    #ifdef _WIN32
        closesocket(sock);
    #elif __linux__
        close(sock);
    #endif
}

int SocketHelper::getLastError() {
    #ifdef _WIN32
        return WSAGetLastError();
    #else
        return errno;
    #endif
}

std::string SocketHelper::inetToAddress(const sockaddr_in address) {
    char buffer[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &address.sin_addr, buffer, INET_ADDRSTRLEN);

    return std::string(buffer);
}

u_long SocketHelper::networkToHost(const sockaddr_in address) {
    return ntohs(address.sin_port);
}

uint16_t SocketHelper::hostToNetworkShort(const uint16_t port) {
    return htons(port);
}

void SocketHelper::presentationToNetwork(const char* ip, sockaddr_in address) {
    inet_pton(AF_INET, ip, &address.sin_addr);
}
