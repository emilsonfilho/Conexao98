//
// Created by Emilson Filho on 27/07/2026.
//

#ifndef CONEXAO98_EXITCOMMAND_H
#define CONEXAO98_EXITCOMMAND_H
#include "IClientCommand.h"


class ExitCommand : public IClientCommand {
public:
    void execute(Conexao98ClientApp &app, const std::string &arguments) override;
};


#endif //CONEXAO98_EXITCOMMAND_H