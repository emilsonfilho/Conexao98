#ifndef CONEXAO98_CHATSTATE_H
#define CONEXAO98_CHATSTATE_H

#include <cstdint>
#include <string>
#include <vector>

#include "../../protocol/UserColor.h"
#include "../commands/CommandRegistry.h"

struct ChatState {
    struct DisplayMessage {
        std::string author;
        std::string text;
        UserColor color;
    };

    std::vector<DisplayMessage> messages;
    std::vector<std::pair<std::string, UserColor>> onlineUsers;
    std::string currentInput;
    int cursorPosition = 0;

    bool isColorMenuOpen = false;
    int selectedColorIndex = 0;
    std::vector<std::string> colorMenuEntries; // precisamos disso porque o FTXUI quer um ponteiro de strings

    struct CommandInfo {
        std::string name;
        std::string description;
    };

    std::vector<CommandInfo> allCommands;
    std::vector<CommandInfo> filteredCommands;
    int selectedCommandIndex = 0;
    bool isCommandMenuOpen = false;

    ChatState();
};


#endif //CONEXAO98_CHATSTATE_H