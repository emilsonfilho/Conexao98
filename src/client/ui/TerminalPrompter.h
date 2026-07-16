#ifndef CONEXAO98_TERMINALPROMPTER_H
#define CONEXAO98_TERMINALPROMPTER_H
#include <cstdint>
#include <string>

#include <string>

class TerminalPrompter {
public:
    static std::string askForIP();
    static uint16_t askForPort();
    static std::string askForNickname();
};


#endif //CONEXAO98_TERMINALPROMPTER_H