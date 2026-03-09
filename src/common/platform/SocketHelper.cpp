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

char *SocketHelper::inetToAddress(const sockaddr_in address) {
    return inet_ntoa(address.sin_addr);
}

u_long SocketHelper::networkToHost(const sockaddr_in address) {
    return ntohs(address.sin_port);
}
