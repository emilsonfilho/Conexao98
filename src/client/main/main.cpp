#include <iostream>

#include "Conexao98ClientApp.h"
#include "../../common/exceptions/Conexao98Exception.h"
#include "../ui/TerminalPrompter.h"

int main(int argc, char* argv[]) {
    std::string ip;
    uint16_t port = 0;

    try {
        TerminalPrompter prompter;

        if (argc == 1) {
            ip = prompter.askForIP();
            port = prompter.askForPort();
        } else if (argc == 3) {
            ip = argv[1];

            auto error = InputValidator::validatePort(argv[2], port);

            if (error != InputValidator::PortError::None) {
                std::cerr << "Porta inválida fornecida na linha de comando.\n";
                return EXIT_FAILURE;
            }
        } else {
            std::cerr << "Uso: client [ip porta]\n";
            return EXIT_FAILURE;
        }

        if (auto app = Conexao98ClientApp(); app.init(ip, port))
            app.run();
    } catch (const Conexao98Exception& e) {
        std::cerr << "[CLIENT]: " << e.what() << "\n";
    }

    return 0;
}
