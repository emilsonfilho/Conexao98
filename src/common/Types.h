#ifndef CONEXAO98_TYPES_H
#define CONEXAO98_TYPES_H

#include <cstdint>

using ConnectionId = uint64_t;

#ifndef _WIN32
    using Socket = SOCKET;
#else
    using Socket = int;
#endif

#endif //CONEXAO98_TYPES_H