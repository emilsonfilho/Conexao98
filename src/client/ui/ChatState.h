#ifndef CONEXAO98_CHATSTATE_H
#define CONEXAO98_CHATSTATE_H

#include <string>
#include <vector>

struct ChatState {
    std::vector<std::string> messages;
    std::string currentInput;
};


#endif //CONEXAO98_CHATSTATE_H