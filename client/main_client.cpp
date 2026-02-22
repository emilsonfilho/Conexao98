#include <algorithm>
#include <iostream>
#include <thread> // Para pausas se necessário
#include "../src/network/NetworkClient.h"
#include "../src/network/ConnectionListener.h"
#include "../src/protocol/messages/ChatMessage.h"
#include "../src/protocol/messages/JoinMessage.h"
#include "../src/protocol/MessageFactory.h"

// 1. Implementação vazia apenas para satisfazer o construtor do NetworkClient
class ClientListener : public ConnectionListener {
public:
    void onMessageReceived(Connection& conn, const ByteArray& data) override {
        std::unique_ptr<Message> msg = MessageFactory::create(data);
        if (msg != nullptr) {
            // Se for mensagem de chat, a gente imprime só o conteúdo!
            if (msg->getType() == MessageType::CHAT) {
                auto* chatMsg = static_cast<ChatMessage*>(msg.get());
                std::cout << "[" << chatMsg->getNickname() << "]: " << chatMsg->getContent() << "\n";
            } else if (msg->getType() == MessageType::JOIN) {
                auto* joinMsg = static_cast<JoinMessage*>(msg.get());
                std::cout << ">>> " << joinMsg->getNickname() << " entrou no servidor! <<<\n";
            }
        }
    }

    void onConnectionCreated(std::unique_ptr<Connection> conn) override {
        std::cout << "[CLIENT] Conexao98!\n";
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

        std::cout << "Bem-vindo ao Conexao98!\nDigite o seu nick: ";
        std::string nick;
        std::getline(std::cin, nick);

        JoinMessage joinMsg(nick);
        client.sendMessage(&joinMsg);

        std::cout << "Prontinho! Agora você pode desfrutar do seu ambiente virtual!\nSe quiser encerrar a conexao, digite 'sair'\n";

        std::string input;
        while (true) {
            std::getline(std::cin, input);

            if (input == "sair")
                break;

            ChatMessage text(input);
            client.sendMessage(&text);
        }

     std::cout << "Jah vai tarde :P\n";
    } catch (std::exception& e) {
        std::cerr << "Erro no cliente: " << e.what() << "\n";
    }

    return 0;
}