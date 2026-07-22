#include "InputValidator.h"

#include <algorithm>
#include <ws2tcpip.h>
#include <psdk_inc/_ip_types.h>

InputValidator::NicknameError InputValidator::validateNickname(const std::string &nick) {
    if (nick.empty()) return NicknameError::Empty;

    const size_t nickLength = nick.length();
    if (nickLength < 3) return NicknameError::TooShort;
    if (nickLength > 16) return NicknameError::TooLong;

    if (!std::all_of(nick.begin(), nick.end(), [](const unsigned char c) -> bool {
        return std::isalnum(c) or c == '_';
    })) {
        return NicknameError::InvalidCharacter;
    };

    return NicknameError::None;
}

InputValidator::PortError InputValidator::validatePort(const std::string &input, uint16_t &outPort) {
    int port = 0;
    std::size_t pos = 0;

    if (input.empty())
        return PortError::Empty;

    try {
        port = std::stoi(input, &pos);
    } catch ([[maybe_unused]] const std::exception& e) {
        return PortError::InvalidNumber;
    }

    if (pos != input.size()) return PortError::InvalidNumber;

    if (port < 1 or port > 65535) return PortError::OutOfRange;

    outPort = static_cast<uint16_t>(port);
    return PortError::None;
}

bool InputValidator::isValidIPv4(const std::string &ip) {
    sockaddr_in sa{};
    return inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr)) == 1;
}
