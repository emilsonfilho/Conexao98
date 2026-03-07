#include "Conexao98ServerApp.h"

#include <iostream>
#include <winsock2.h>

#include "../common/exceptions/SystemException.h"

Conexao98ServerApp::Conexao98ServerApp() = default;

Conexao98ServerApp::~Conexao98ServerApp() {
    if (isWsaInitialized) WSACleanup();
    std::cout << "[APP] Desligando subsistema de rede do Windows...\n";
}

void Conexao98ServerApp::init() {
    std::cout << "[APP] Inicializando subsistema de rede do Windows...\n";
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        throw SystemException("Falha no WSAStartup");

    isWsaInitialized = true;

    chatManager = std::make_unique<ChatManager>();
    chatManager->initializeHandlers();

    server = std::make_unique<NetworkServer>(chatManager.get());
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
    if (server) server->shutdown();
}
