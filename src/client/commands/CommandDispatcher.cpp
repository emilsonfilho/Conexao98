//
// Created by Emilson Filho on 27/07/2026.
//

#include "CommandDispatcher.h"

void CommandDispatcher::registerCommand(const std::string &trigger, std::unique_ptr<IClientCommand> command) {
    registeredCommands.emplace(trigger, std::move(command));
}

bool CommandDispatcher::dispatch(const std::string &input, Conexao98ClientApp &app) {
    if (input.empty() or input[0] != '/')
       return false;

    std::stringstream ss(input);

    std::string trigger;
    ss >> trigger;

    const auto it = registeredCommands.find(trigger);
    if (it == registeredCommands.end())
        return true;

    it->second->execute(app, input);

    return true;
}
