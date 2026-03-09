//
// Created by Emilson Filho on 09/03/2026.
//

#ifndef CONEXAO98_SOCKETHELPER_H
#define CONEXAO98_SOCKETHELPER_H
#include "../Types.h"

#ifdef _WIN32
    #include <winsock2.h>
#elif (__linux__)
    #include <sys/socket.h>
    #include <unistd.h>
    #include <cerrno>
#endif

class SocketHelper {
public:
    SocketHelper() = delete;

    static bool initSystem();
    static void cleanupSystem();
    static void closeSocket(Socket sock);
    static int getLastError();
};


#endif //CONEXAO98_SOCKETHELPER_H