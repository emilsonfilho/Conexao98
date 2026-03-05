#include "Server98ClientApp.h"

#include <iostream>
#include <winsock2.h>

Server98ClientApp::Server98ClientApp() = default;

Server98ClientApp::~Server98ClientApp() {
    std::cout << "[APP] Desligando subsistema de rede do Windows...\n";
    WSACleanup();
}

bool Server98ClientApp::init() {
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

void Server98ClientApp::run() {
    if (server) {
        std::cout << "[APP] Inicializando servidor na porta 3000...\n";
        server->start(3000);
    } else {
        std::cerr << "[APP] O servidor não foi inicializado corretamente.\n";
    }
}