#include "TerminalPrompter.h"

#include <iostream>

#include "../../common/utils/InputValidator.h"

std::string TerminalPrompter::askForIP() {
    std::string ip;

    std::cout << "Informe o endereço IP: ";

    // TODO: Migrar o TerminalPrompter de erros booleanos para o Enum
    do {
        std::getline(std::cin, ip);

        if (!InputValidator::isValidIPv4(ip))
            std::cout << "Hmm... isso não parece um IP válido. Tente novamente: ";
        else
            break;
    } while (true);

    return ip;
}

std::uint16_t TerminalPrompter::askForPort() {
    std::string input;
    uint16_t port = 0;

    std::cout << "Informe a porta: ";
    do {
        std::getline(std::cin, input);

        if (!InputValidator::tryParsePort(input, port))
            std::cout << "Porta inválida. Tente novamente: ";
        else
            break;
    } while (true);

    return port;
}

std::string TerminalPrompter::askForNickname() {

}
