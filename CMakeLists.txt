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
        src/network/NetworkServer.h
        src/app/handlers/JoinHandler.cpp
        src/app/handlers/JoinHandler.h
        src/protocol/messages/JoinMessage.cpp
        src/protocol/messages/JoinMessage.h
        src/protocol/messages/ChatMessage.cpp
        src/protocol/messages/ChatMessage.h
        src/app/handlers/ChatHandler.cpp
        src/app/handlers/ChatHandler.h
        src/protocol/MessageFactory.cpp
        src/protocol/MessageFactory.h
        src/app/ChatManager.cpp
        src/app/ChatManager.h
        src/app/UserSession.cpp
        src/app/UserSession.h
        src/network/ServerListener.h
        src/common/Types.h) # adiciona um alvo
add_executable(client client/main_client.cpp
        src/network/Connection.cpp
        src/network/ConnectionListener.h
        src/protocol/Message.h
        src/protocol/MessageType.h
        src/common/ByteArray.cpp
        src/common/ByteArray.h
        src/network/NetworkClient.cpp
        src/network/NetworkClient.h
        src/app/ChatManager.cpp
        src/app/ChatManager.h
        src/app/UserSession.cpp
        src/app/UserSession.h
        src/app/handlers/MessageHandler.h
        src/app/handlers/JoinHandler.cpp
        src/app/handlers/JoinHandler.h
        src/protocol/messages/JoinMessage.cpp
        src/protocol/messages/JoinMessage.h
        src/protocol/messages/ChatMessage.cpp
        src/protocol/messages/ChatMessage.h
        src/app/handlers/ChatHandler.cpp
        src/app/handlers/ChatHandler.h
        src/protocol/MessageFactory.cpp
        src/protocol/MessageFactory.h
        src/common/Types.h
        src/network/ServerListener.h)

if (WIN32)
    target_link_libraries(server ws2_32) # linka uma liba a um executável previamente criado
    target_link_libraries(client ws2_32)
endif()