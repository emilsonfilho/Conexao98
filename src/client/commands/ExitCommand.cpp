//
// Created by Emilson Filho on 27/07/2026.
//

#include "ExitCommand.h"

#include "../main/Conexao98ClientApp.h"

void ExitCommand::execute(Conexao98ClientApp &app, const std::string &arguments) {
    app.stop();
}
