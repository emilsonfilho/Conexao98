#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

constexpr int PORT = 8080;
constexpr int BUFFER_SIZE = 1024;

void receive_messages(int sock) {
    char buffer[BUFFER_SIZE];
    while (true) {
        std::memset(buffer, 0, BUFFER_SIZE);
        ssize_t bytes = read(sock, buffer, BUFFER_SIZE);
        if (bytes <= 0) {
            std::cout << "Desconectado do servidor." << std::endl;
            break;
        }
        std::cout << "\n[servidor]: " << std::string(buffer, bytes) << std::endl;
        std::cout << "[você]: " << std::flush;
    }
}

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        perror("Erro ao criar socket");
        return 1;
    }

    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Endereço inválido");
        return 1;
    }

    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Erro na conexão");
        return 1;
    }

    std::cout << "Conectado ao servidor. Digite '/sair' para sair." << std::endl;

    std::thread receiver(receive_messages, sock);

    std::string message;
    do {
        std::cout << "[você]: ";
        std::getline(std::cin, message);

        if (!message.empty()) {
            send(sock, message.c_str(), message.size(), 0);
        }

    } while (message != "/sair");

    close(sock);
    receiver.detach(); // deixa thread terminar sozinha (ou use receiver.join() com lógica melhor)
    return 0;
}
