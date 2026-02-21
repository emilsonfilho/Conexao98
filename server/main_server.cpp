#include "../src/network/NetworkServer.h"
#include <iostream>

#include "../src/app/ChatManager.h"
#include "../src/network/ConnectionListener.h"

int main() {
    // 1. Inicia o Winsock (Obrigatório no Windows)
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Falha no WSAStartup\n";
        return 1;
    }

    try {
        // 2. Cria o Listener de teste
        ChatManager debugListener;
        debugListener.initializeHandlers();

        // 3. Cria o servidor passando o listener
        // (Certifique-se que seu NetworkServer aceita o listener no construtor!)
        NetworkServer server(&debugListener);

        std::cout << "Iniciando servidor na porta 3000...\n";

        // 4. Roda o servidor (vai travar aqui no loop)
        server.start(3000);

    } catch (std::exception& e) {
        std::cerr << "ERRO FATAL: " << e.what() << "\n";
    }

    WSACleanup();
    return 0;
}

