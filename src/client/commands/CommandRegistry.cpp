//
// Created by Emilson Filho on 06/08/2026.
//

#include "CommandRegistry.h"

#include "ColorCommand.h"
#include "ExitCommand.h"

const std::vector<CommandConfig>& CommandRegistry::getAvailableCommands() {
    static const std::vector<CommandConfig> commands = {
        {
            "/cor",
            "Altera a cor do seu perfil na rede",
            []() { return std::make_unique<ColorCommand>(); }
        },
        {
            "/sair",
            "Desconecta e fecha o aplicativo",
            []() { return std::make_unique<ExitCommand>(); }
        }
    };

    return commands;
}
