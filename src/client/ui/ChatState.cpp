//
// Created by Emilson Filho on 06/08/2026.
//

#include "ChatState.h"

ChatState::ChatState()  {
    for (const auto& config : ColorRegistry::getAllColors())
        colorMenuEntries.push_back(config.name);

    for (const auto& command : CommandRegistry::getAvailableCommands())
        allCommands.push_back({ command.trigger, command.description });
}
