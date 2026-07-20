#include "TerminalPrompter.h"

#include <iostream>

#include "../../common/utils/InputValidator.h"

std::string TerminalPrompter::getMessage(InputValidator::NicknameError error) {
    switch (error) {
        case InputValidator::NicknameError::Empty:
            return "O nickname não pode estar vazio.";

        case InputValidator::NicknameError::TooShort:
            return "O nickname deve ter pelo menos 3 caracteres.";

        case InputValidator::NicknameError::TooLong:
            return "O nickname deve ter no máximo 16 caracteres.";

        case InputValidator::NicknameError::InvalidCharacter:
            return "Use apenas letras, números e '_'.";

        case InputValidator::NicknameError::None:
            return "";
    }

    return "Erro desconhecido.";
}

std::string TerminalPrompter::getMessage(InputValidator::PortError error) {
    switch (error) {
        case InputValidator::PortError::Empty:
            return "A porta não pode estar vazia.";
        case InputValidator::PortError::InvalidNumber:
            return "A porta deve conter apenas números.";
        case InputValidator::PortError::OutOfRange:
            return "A porta deve estar entre 1 e 65535.";
        case InputValidator::PortError::None:
            return "";
    }

    return "Erro desconhecido.";
}

std::string TerminalPrompter::askForIP() {
    std::string ip;

    std::cout << "Informe o endereço IP: ";

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

        const auto error = InputValidator::validatePort(input, port);

        if (error == InputValidator::PortError::None)
            return port;

        std::cout << getMessage(error) << '\n'
                  << "Informe a porta: ";
    } while (true);
}

std::string TerminalPrompter::askForNickname() {
    std::string nickname;

    std::cout << "Digite um nome legal: ";
    do {
        std::getline(std::cin, nickname);

        const auto error = InputValidator::validateNickname(nickname);

        if (error == InputValidator::NicknameError::None)
            return nickname;

        std::cout << getMessage(error) << '\n'
                  << "Vamos tentar novamente: ";
    } while (true);
}
