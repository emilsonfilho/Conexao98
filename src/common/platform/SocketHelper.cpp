//
// Created by Emilson Filho on 09/03/2026.
//

#include "SocketHelper.h"

bool SocketHelper::initSystem() {
    #ifdef _WIN32
        WSADATA wsaData;

        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
            return false;

        return true;
    #endif
}

void SocketHelper::cleanupSystem() {
    #ifdef _WIN32
        WSACleanup();
    #endif
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
