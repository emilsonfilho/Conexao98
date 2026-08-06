#ifndef CONEXAO98_CHATSTATE_H
#define CONEXAO98_CHATSTATE_H

#include <cstdint>
#include <string>
#include <vector>

#include "../../protocol/UserColor.h"

struct ChatState {
    struct DisplayMessage {
        std::string author;
        std::string text;
        UserColor color;
    };

    std::vector<DisplayMessage> messages;
    std::vector<std::pair<std::string, UserColor>> onlineUsers;
    std::string currentInput;

    bool isColorMenuOpen = false;
    int selectedColorIndex = 0;
    std::vector<std::string> colorMenuEntries; // precisamos disso porque o FTXUI quer um ponteiro de strings

    ChatState() {
        for (const auto& config : ColorRegistry::getAllColors())
            colorMenuEntries.push_back(config.name);
    }
};


#endif //CONEXAO98_CHATSTATE_H