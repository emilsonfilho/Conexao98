cmake_minimum_required(VERSION 3.20) # required
project(Conexao98) # required

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
        GIT_TAG v5.0.0
)
FetchContent_MakeAvailable(ftxui)

add_executable(server src/server/main.cpp
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
        src/common/Types.h
        src/server/Conexao98ServerApp.cpp
        src/server/Conexao98ServerApp.h
        src/common/exceptions/Conexao98Exception.h
        src/common/exceptions/SystemException.h
        src/common/exceptions/NetworkException.h
        src/common/exceptions/ProtocolException.h
        src/app/ConnectionReaper.cpp
        src/app/ConnectionReaper.h
        src/common/platform/SocketHelper.cpp
        src/common/platform/SocketHelper.h
        src/common/logger/Logger.cpp
        src/common/logger/Logger.h
        src/common/logger/LogLevel.h
)
add_executable(client src/client/main/main.cpp
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
        src/network/ServerListener.h
        src/client/main/Conexao98ClientApp.cpp
        src/client/main/Conexao98ClientApp.h
        src/client/ConsoleChatListener.cpp
        src/client/ConsoleChatListener.h
        src/client/printers/IMessagePrinter.h
        src/client/printers/ChatPrinter.cpp
        src/client/printers/ChatPrinter.h
        src/client/printers/JoinPrinter.cpp
        src/client/printers/JoinPrinter.h
        src/common/exceptions/Conexao98Exception.h
        src/common/exceptions/SystemException.h
        src/common/exceptions/NetworkException.h
        src/common/exceptions/ProtocolException.h
        src/app/ConnectionReaper.cpp
        src/app/ConnectionReaper.h
        src/common/platform/SocketHelper.cpp
        src/common/platform/SocketHelper.h
        src/common/logger/Logger.cpp
        src/common/logger/Logger.h
        src/common/logger/LogLevel.h
        src/common/utils/InputValidator.cpp
        src/common/utils/InputValidator.h
        src/client/ui/TerminalPrompter.cpp
        src/client/ui/TerminalPrompter.h
        src/client/ui/ChatState.h
        src/client/ui/ChatView.cpp
        src/client/ui/ChatView.h
        src/client/ui/ChatPresenter.cpp
        src/client/ui/ChatPresenter.h
        src/client/main/IChatLoop.h
        src/client/ConsoleChatLoop.cpp
        src/client/ConsoleChatLoop.h
        src/client/ui/TUIListener.cpp
        src/client/ui/TUIListener.h
        src/client/ui/TUIChatLoop.cpp
        src/client/ui/TUIChatLoop.h
        src/client/commands/IClientCommand.h
        src/client/commands/ExitCommand.cpp
        src/client/commands/ExitCommand.h
        src/client/commands/CommandDispatcher.cpp
        src/client/commands/CommandDispatcher.h
)

if (WIN32)
    target_link_libraries(server PRIVATE ws2_32) # linka uma liba a um executável previamente criado
    target_link_libraries(client PRIVATE ws2_32)
endif()

target_link_libraries(client PRIVATE ftxui::screen ftxui::dom ftxui::component)