#include "InputValidator.h"

#include <algorithm>

#include "../../protocol/UserColor.h"
#include "../platform/SocketHelper.h"

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

InputValidator::ColorError InputValidator::validateColor(const std::string &input, uint16_t &outColor) {
    if (input.empty())
        return ColorError::Empty;

    int color = 0;
    std::size_t pos = 0;

    try {
        color = std::stoi(input, &pos);
    } catch (const std::exception& e) {
        return ColorError::InvalidNumber;
    }

    if (pos != input.size()) return ColorError::InvalidNumber;

    if (color < 1 or color > COLOR_UPPER_BOUND)
        return ColorError::OutOfRange;

    outColor = static_cast<uint16_t>(color);
    return ColorError::None;
}

bool InputValidator::isValidIPv4(const std::string &ip) {
    sockaddr_in sa{};
    return inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr)) == 1;
}
