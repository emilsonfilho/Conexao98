#ifndef CONEXAO98_TYPES_H
#define CONEXAO98_TYPES_H

#include <cstdint>

#include "platform/SocketHelper.h"

#ifdef _WIN32
    #include <winsock2.h>
#elif __linux__
    #include <sys/socket.h>
#endif

using ConnectionId = uint64_t;

#ifdef _WIN32
    using Socket = SOCKET;
    using SocketLen = int;
    constexpr Socket SOCKET_ERR = SOCKET_ERROR;
    constexpr Socket INVALID_SOCKET_FD = INVALID_SOCKET;
    constexpr Socket SOCKET_SHUTDOWN_BOTH = SD_BOTH;
#else
    using Socket = int;
    using SocketLen = socklen_t;
    constexpr Socket SOCKET_ERR = -1;
    constexpr Socket INVALID_SOCKET_FD = -1;
    constexpr Socket SOCKET_SHUTDOWN_BOTH = SHUT_RDWR;
#endif

#endif //CONEXAO98_TYPES_H