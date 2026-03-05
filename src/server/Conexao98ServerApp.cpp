#include "Conexao98ServerApp.h"

#include <iostream>
#include <winsock2.h>

Conexao98ServerApp::Conexao98ServerApp() = default;

Conexao98ServerApp::~Conexao98ServerApp() {
    std::cout << "[APP] Desligando subsistema de rede do Windows...\n";
    WSACleanup();
}

bool Conexao98ServerApp::init() {
    std::cout << "[APP] Inicializando subsistema de rede do Windows...\n";
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Falha no WSAStartup\n";
        return false;
    }

    chatManager = std::make_unique<ChatManager>();
    chatManager->initializeHandlers();

    server = std::make_unique<NetworkServer>(chatManager.get());

    return true;
}

void Conexao98ServerApp::run() const {
    if (server) {
        std::cout << "[APP] Inicializando servidor na porta 3000...\n";
        server->start(3000);
    } else {
        std::cerr << "[APP] O servidor não foi inicializado corretamente.\n";
    }
}

void Conexao98ServerApp::stop() const {
    server->shutdown();
}
