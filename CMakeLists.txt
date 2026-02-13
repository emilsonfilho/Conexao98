cmake_minimum_required(VERSION 3.20) # required
project(Conexao98) # required

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(server server/main_server.cpp
        src/network/Connection.cpp
        src/network/ConnectionListener.h
        src/protocol/Message.h
        src/protocol/MessageType.h
        src/common/ByteArray.cpp
        src/common/ByteArray.h
        src/network/NetworkServer.cpp
        src/network/NetworkServer.h) # adiciona um alvo
add_executable(client client/main_client.cpp
        src/network/Connection.cpp
        src/network/ConnectionListener.h
        src/protocol/Message.h
        src/protocol/MessageType.h
        src/common/ByteArray.cpp
        src/common/ByteArray.h)

if (WIN32)
    target_link_libraries(server ws2_32) # linka uma liba a um executável previamente criado
    target_link_libraries(client ws2_32)
endif()