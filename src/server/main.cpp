#include <iostream>

#include "Conexao98ServerApp.h"

int main() {
    try {
        if (Conexao98ServerApp app; app.init())
            app.run();
    } catch (std::exception& e) {
        std::cerr << "ERRO FATAL: " << e.what() << "\n";
    }

    WSACleanup();
    return 0;
}

