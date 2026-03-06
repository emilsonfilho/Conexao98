#include <iostream>

#include "Conexao98ClientApp.h"
#include "../../network/NetworkClient.h"
#include "../../network/ConnectionListener.h"
#include "../../protocol/messages/ChatMessage.h"
#include "../../protocol/messages/JoinMessage.h"
#include "../../protocol/MessageFactory.h"

int main() {
    try {
        if (auto app = Conexao98ClientApp(); app.init())
            app.run();
    } catch (std::exception& e) {
        std::cerr << "[CLIENT]: " << e.what() << "\n";
    }

    return 0;
}