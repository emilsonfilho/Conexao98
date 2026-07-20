#ifndef CONEXAO98_TERMINALPROMPTER_H
#define CONEXAO98_TERMINALPROMPTER_H
#include <cstdint>
#include <string>

#include <string>

#include "../../common/utils/InputValidator.h"

class TerminalPrompter {
private:
    static std::string getMessage(InputValidator::NicknameError error);
    static std::string getMessage(InputValidator::PortError error);
public:
    static std::string askForIP();
    static uint16_t askForPort();
    static std::string askForNickname();
};


#endif //CONEXAO98_TERMINALPROMPTER_H