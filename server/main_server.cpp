#include "../src/network/NetworkServer.h"
#include <iostream>

#include "../src/network/ConnectionListener.h"

class FofoqueiroListener : public ConnectionListener {
public:
    void onMessageReceived(Connection& conn, const ByteArray& data) override {
        // Truque para imprimir o ByteArray como texto
        std::string texto(data.data(), data.size());
        std::cout << "[SERVER] O cliente " << conn.getSenderId() << " disse: " << texto << "\n";
    }

    void onDisconnected(Connection& conn) override {
        std::cout << "[SERVER] O cliente " << conn.getSenderId() << " foi embora.\n";
    }
};

int main() {
    // 1. Inicia o Winsock (Obrigatório no Windows)
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Falha no WSAStartup\n";
        return 1;
    }

    try {
        // 2. Cria o Listener de teste
        FofoqueiroListener debugListener;

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

