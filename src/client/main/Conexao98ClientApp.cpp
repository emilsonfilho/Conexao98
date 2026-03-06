#include "Conexao98ClientApp.h"

#include "../ConsoleChatListener.h"
#include "../../protocol/messages/ChatMessage.h"
#include "../../protocol/messages/JoinMessage.h"

Conexao98ClientApp::Conexao98ClientApp() {
    clientListener = std::make_unique<ConsoleChatListener>();
    client = std::make_unique<NetworkClient>(clientListener.get());
    isActive = false;
}

bool Conexao98ClientApp::init() {
    try {
        WSADATA wsaData;

        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
            throw std::runtime_error("Network initialization failed (WSAStartup).");

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