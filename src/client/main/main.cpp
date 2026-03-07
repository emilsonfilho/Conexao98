#include <iostream>

#include "Conexao98ClientApp.h"
#include "../../common/exceptions/Conexao98Exception.h"

int main() {
    try {
        if (auto app = Conexao98ClientApp(); app.init())
            app.run();
    } catch (const Conexao98Exception& e) {
        std::cerr << "[CLIENT]: " << e.what() << "\n";
    }

    return 0;
}