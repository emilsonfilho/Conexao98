//
// Created by Emilson Filho on 27/07/2026.
//

#ifndef CONEXAO98_COMMANDDISPATCHER_H
#define CONEXAO98_COMMANDDISPATCHER_H
#include <memory>
#include <string>
#include <unordered_map>
#include <sstream>

#include "IClientCommand.h"


class CommandDispatcher {
private:
    std::unordered_map<std::string, std::unique_ptr<IClientCommand>> registeredCommands;
public:
    void registerCommand(const std::string& trigger, std::unique_ptr<IClientCommand> command);
    bool dispatch(const std::string& input, Conexao98ClientApp& app);
};


#endif //CONEXAO98_COMMANDDISPATCHER_H