#include "Conexao98ClientApp.h"

#include "../ConsoleChatListener.h"
#include "../../common/exceptions/SystemException.h"
#include "../../common/platform/SocketHelper.h"
#include "../../protocol/messages/ChatMessage.h"
#include "../../protocol/messages/JoinMessage.h"

Conexao98ClientApp::Conexao98ClientApp() {
    clientListener = std::make_unique<ConsoleChatListener>();
    client = std::make_unique<NetworkClient>(clientListener.get());
    isActive = false;
    isWSAInitialized = false;
}

Conexao98ClientApp::~Conexao98ClientApp() {
    if (isWSAInitialized) SocketHelper::cleanupSystem();
}

bool Conexao98ClientApp::init() {
    try {
       if (!SocketHelper::initSystem())
            throw SystemException("Network initialization failed (WSAStartup).");

        isWSAInitialized = true;

        client->connectToServer("127.0.0.1", 3000);

        std::cout << "Bem-vindo ao Conexao98!\nDigite seu nick: " << std::endl;

        std::getline(std::cin, nickname);

        JoinMessage joinMsg(nickname);
        client->sendMessage(&joinMsg);

        std::cout << "Prontinho! Agora você pode desfrutar do seu ambiente virtual!\nSe quiser encerrar a conexao, digite 'sair'\n";

        isActive = true;

        return true;
    } catch (std::runtime_error& e) {
        std::cerr << e.what();
        return false;
    }
}

void Conexao98ClientApp::run() {
    std::string inputText;

    while (isActive) {
        std::getline(std::cin, inputText);

        if (inputText == "sair") {
            stop();
            break;
        }

        ChatMessage text(inputText);
        client->sendMessage(&text);
    }
}

void Conexao98ClientApp::stop() {
    isActive = false;

    std::cout << "Volte sempre!\n";
}