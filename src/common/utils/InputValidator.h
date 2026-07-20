#ifndef CONEXAO98_INPUTVALIDATOR_H
#define CONEXAO98_INPUTVALIDATOR_H


#include <cstdint>
#include <string>

class InputValidator {
public:
    enum class NicknameError {
        None,
        Empty,
        TooShort,
        TooLong,
        InvalidCharacter
    };

    enum class PortError {
        None,
        Empty,
        InvalidNumber,
        OutOfRange
    };

    static NicknameError validateNickname(const std::string& nick);
    static PortError validatePort(const std::string& input, uint16_t& outPort);
    static bool isValidIPv4(const std::string& ip);
};


#endif //CONEXAO98_INPUTVALIDATOR_H