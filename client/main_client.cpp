#include <iostream>
#include <thread> // Para pausas se necessário
#include "../src/network/NetworkClient.h"
#include "../src/network/ConnectionListener.h"

// 1. Implementação vazia apenas para satisfazer o construtor do NetworkClient
class ClientListener : public ConnectionListener {
public:
    void onMessageReceived(Connection& conn, const ByteArray& data) override {
        // Futuro: Lógica de receber mensagens do servidor
        std::cout << "[CLIENT] Mensagem recebida do servidor\n";
    }

    void onDisconnected(Connection& conn) override {
        std::cout << "[CLIENT] Desconectado do servidor.\n";
    }
};

int main() {
    // Nota: O WSAStartup já está sendo chamado dentro do seu NetworkClient::connectToServer
    // então não precisamos chamar aqui explicitamente, embora fosse uma boa prática no main.

    try {
        // 1. Cria o listener obrigatório
        ClientListener listener;

        // 2. Instancia o cliente
        NetworkClient client(&listener);

        std::cout << "Tentando conectar ao servidor (127.0.0.1:3000)...\n";

        // 3. Conecta (Certifique-se que o Server está rodando antes!)
        client.connectToServer("127.0.0.1", 3000);

        std::cout << "Bem-vindo ao Conexao98!\nDigite suas mensagens ou 'sair' para fechar.\n";

        std::string input;
        while (true) {
            std::getline(std::cin, input);

            if (input == "sair")
                break;

            client.sendMessage(input);
        }

     std::cout << "Jah vai tarde :P\n";
    } catch (std::exception& e) {
        std::cerr << "Erro no cliente: " << e.what() << "\n";
    }

    return 0;
}