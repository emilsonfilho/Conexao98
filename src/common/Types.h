#ifndef CONEXAO98_TYPES_H
#define CONEXAO98_TYPES_H

#include <cstdint>

#ifdef _WIN32
    #include <winsock2.h>
#endif

using ConnectionId = uint64_t;

#ifdef _WIN32
    using Socket = SOCKET;
#else
    using Socket = int;
#endif

#endif //CONEXAO98_TYPES_H