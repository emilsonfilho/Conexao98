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

std::string TerminalPrompter::getMessage(InputValidator::ColorError error) {
    switch (error) {
        case InputValidator::ColorError::Empty:
            return "A escolha não pode estar vazia.";
        case InputValidator::ColorError::InvalidNumber:
            return "Por favor, digite apenas números.";
        case InputValidator::ColorError::OutOfRange:
            return "Opção inválida. Escolha um número de 1 a 6.";
        case InputValidator::ColorError::None:
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

UserColor TerminalPrompter::askForColor() {
    std::string input;
    uint16_t colorId = 0;

    // \033[XXm inicia a cor
    // \033[0m reseta a cor para o padrão do terminal
    std::cout << "\nEscolha uma cor para o seu perfil:\n";

    for (const auto& color : ColorRegistry::getAllColors()) {
        std::cout << "[" << static_cast<int>(color.id) << "] " << color.ansi << color.name << "\033[0m\n";
    }

    std::cout << "Digite o numero da sua cor: ";
    do {
        std::getline(std::cin, input);
        const auto error = InputValidator::validateColor(input, colorId);

        if (error == InputValidator::ColorError::None)
            return static_cast<UserColor>(colorId);

        std::cout << getMessage(error) << '\n'
                  << "Digite o numero da sua cor (1-6): ";
    } while (true);
}
