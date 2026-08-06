//
// Created by Emilson Filho on 03/08/2026.
//

#ifndef CONEXAO98_USERCOLOR_H
#define CONEXAO98_USERCOLOR_H

#include <cstdint>
#include <string>
#include <vector>

#define COLOR_UPPER_BOUND 6

enum class UserColor : uint8_t {
    DEFAULT = 0,
    RED = 1,
    GREEN = 2,
    BLUE = 3,
    YELLOW = 4,
    CYAN = 5,
    MAGENTA = 6
};

struct ColorConfig {
    UserColor id;
    std::string name;
    std::string ansi;
};

class ColorRegistry {
public:
    static const std::vector<ColorConfig>& getAllColors();
};

#endif //CONEXAO98_USERCOLOR_H