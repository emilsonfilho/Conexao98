//
// Created by Emilson Filho on 22/07/2026.
//

#include "ConsoleChatLoop.h"

#include <iostream>

ConsoleChatLoop::ConsoleChatLoop(): isActive(true) {}

void ConsoleChatLoop::run(const std::function<void(const std::string &)> &onSend) {
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