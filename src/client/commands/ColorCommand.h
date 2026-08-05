//
// Created by Emilson Filho on 05/08/2026.
//

#ifndef CONEXAO98_COLORCOMMAND_H
#define CONEXAO98_COLORCOMMAND_H

#include "IClientCommand.h"
#include "../main/Conexao98ClientApp.h"

class ColorCommand : public IClientCommand {
public:
    void execute(Conexao98ClientApp &app, const std::string &arguments) override;
};


#endif //CONEXAO98_COLORCOMMAND_H