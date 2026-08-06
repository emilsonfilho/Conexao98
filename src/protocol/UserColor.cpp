//
// Created by Emilson Filho on 06/08/2026.
//

#include "UserColor.h"

#include <algorithm>

const std::vector<ColorConfig> &ColorRegistry::getAllColors() {
    static const std::vector<ColorConfig> availableColors = {
        { UserColor::RED, "Vermelho", "\033[91m" },
        { UserColor::GREEN, "Verde", "\033[92m" },
        { UserColor::BLUE, "Azul", "\033[94m" },
        { UserColor::YELLOW, "Amarelo", "\033[93m" },
        { UserColor::CYAN, "Ciano", "\033[96m" },
        { UserColor::MAGENTA, "Magenta", "\033[95m" }
    };
    return availableColors;
}
