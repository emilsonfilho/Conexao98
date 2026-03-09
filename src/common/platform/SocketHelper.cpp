//
// Created by Emilson Filho on 09/03/2026.
//

#include "SocketHelper.h"

bool SocketHelper::initSystem() {
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        return false;

    return true;
}

void SocketHelper::cleanupSystem() {
    WSACleanup();
}

void SocketHelper::closeSocket(SOCKET sock) {
    closesocket(sock);
}

int SocketHelper::getLastError() {
    return WSAGetLastError();
}
