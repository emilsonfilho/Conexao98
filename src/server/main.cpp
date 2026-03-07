#include <iostream>

#include "Conexao98ServerApp.h"
#include "../common/exceptions/Conexao98Exception.h"

int main() {
    try {
        Conexao98ServerApp app;
        app.init();

        app.run();
    } catch (Conexao98Exception& e) {
        std::cerr << "ERRO FATAL: " << e.what() << "\n";
    }

    return 0;
}

