#include "ConsoleChatLoop.h"
#include <iostream>
#include <string>

ConsoleChatLoop::ConsoleChatLoop(): isActive(true) {}

void ConsoleChatLoop::run(const std::function<void(const std::string &)> &onSend, const std::function<void(UserColor)>& onColorChange) {
    // Salva o callback para o showColorMenu poder usar depois!
    this->onColorChangeCallback = onColorChange;

    std::string inputText;

    while (isActive) {
        std::getline(std::cin, inputText);

        if (inputText == "sair") {
            stop();
            break;
        }

        onSend(inputText);
    }
}

void ConsoleChatLoop::stop() {
    isActive = false;
    std::cout << "[CLIENT] Volte sempre!\n";
}

void ConsoleChatLoop::showColorMenu() {
    std::cout << "\n=== MENU DE CORES ===\n"
              << "[1] Vermelho\n"
              << "[2] Verde\n"
              << "[3] Azul\n"
              << "[4] Amarelo\n"
              << "[5] Ciano\n"
              << "[6] Magenta\n"
              << "Escolha o numero da nova cor: ";

    std::string input;
    std::getline(std::cin, input);

    try {
        int colorId = std::stoi(input);

        if (colorId >= 1 && colorId <= 6) {
            if (onColorChangeCallback) {
                    onColorChangeCallback(static_cast<UserColor>(colorId));
                std::cout << "Cor atualizada na rede com sucesso!\n";
            }
        } else {
            std::cout << "Cor invalida. Operacao cancelada.\n";
        }
    } catch (...) {
        std::cout << "Entrada invalida. Operacao cancelada.\n";
    }
}