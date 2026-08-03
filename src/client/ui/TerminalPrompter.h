#ifndef CONEXAO98_TERMINALPROMPTER_H
#define CONEXAO98_TERMINALPROMPTER_H
#include <cstdint>
#include <string>

#include <string>

#include "../../common/utils/InputValidator.h"
#include "../../protocol/UserColor.h"

class TerminalPrompter {
private:
    static std::string getMessage(InputValidator::NicknameError error);
    static std::string getMessage(InputValidator::PortError error);
    static std::string getMessage(InputValidator::ColorError error);
public:
    static std::string askForIP();
    static uint16_t askForPort();
    static std::string askForNickname();
    static UserColor askForColor();
};


#endif //CONEXAO98_TERMINALPROMPTER_H