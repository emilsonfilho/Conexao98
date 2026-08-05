//
// Created by Emilson Filho on 05/08/2026.
//

#include "ColorCommand.h"

void ColorCommand::execute(Conexao98ClientApp &app, const std::string &arguments) {
    app.requestColorMenu();
}
