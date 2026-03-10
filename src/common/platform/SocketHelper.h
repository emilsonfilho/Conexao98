//
// Created by Emilson Filho on 09/03/2026.
//

#ifndef CONEXAO98_SOCKETHELPER_H
#define CONEXAO98_SOCKETHELPER_H

#include <string>

#include "../Types.h"

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
#elif (__linux__)
    #include <sys/socket.h>
    #include <unistd.h>
    #include <cerrno>
    #include <arpa/inet.h>
    #include <sys/types.h>
    #include <netinet/in.h>
#endif

class SocketHelper {
public:
    SocketHelper() = delete;

    static bool initSystem();
    static void cleanupSystem();
    static void shutdownSystem(Socket sock);
    static void closeSocket(Socket sock);
    static int getLastError();
    static std::string inetToAddress(const sockaddr_in& address);
    static u_long networkToHost(const sockaddr_in& address);
    static uint16_t hostToNetworkShort(uint16_t port);
    static void presentationToNetwork(const char* ip, sockaddr_in& address);
};


#endif //CONEXAO98_SOCKETHELPER_H