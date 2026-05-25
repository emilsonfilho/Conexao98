#include <iostream>

#include "Conexao98ClientApp.h"
#include "../../common/exceptions/Conexao98Exception.h"

int main(int argc, char* argv[]) {
    std::string ip = "";
    uint16_t port = 0;

    try {
        if (argc == 1) {
            std::cout << "Digite o IP: ";
            std::cin >> ip;

            std::cout << "Digite a porta: ";
            std::string portStr;
            std::cin >> portStr;
            port = std::stoi(portStr);
        } else if (argc == 3) {
            ip = std::string(argv[1]);
            port = std::stoi(argv[2]);
        }

        if (auto app = Conexao98ClientApp(); app.init(ip, port))
            app.run();
    } catch (const Conexao98Exception& e) {
        std::cerr << "[CLIENT]: " << e.what() << "\n";
    }

    return 0;
}