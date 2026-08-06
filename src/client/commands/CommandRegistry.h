//
// Created by Emilson Filho on 06/08/2026.
//

#ifndef CONEXAO98_COMMANDREGISTRY_H
#define CONEXAO98_COMMANDREGISTRY_H
#include <functional>
#include <memory>

#include "IClientCommand.h"

struct CommandConfig {
    std::string trigger;
    std::string description;
    std::function<std::unique_ptr<IClientCommand>()> factory;
};

class CommandRegistry {
public:
    static const std::vector<CommandConfig>& getAvailableCommands();
};


#endif //CONEXAO98_COMMANDREGISTRY_H