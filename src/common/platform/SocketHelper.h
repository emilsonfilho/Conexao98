//
// Created by Emilson Filho on 09/03/2026.
//

#ifndef CONEXAO98_SOCKETHELPER_H
#define CONEXAO98_SOCKETHELPER_H
#include <winsock2.h>


class SocketHelper {
public:
    SocketHelper() = delete;

    static bool initSystem();
    static void cleanupSystem();
    static void closeSocket(SOCKET sock);
    static int getLastError();
};


#endif //CONEXAO98_SOCKETHELPER_H