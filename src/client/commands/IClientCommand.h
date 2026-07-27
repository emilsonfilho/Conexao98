#ifndef CONEXAO98_ICLIENTCOMMAND_H
#define CONEXAO98_ICLIENTCOMMAND_H
#include <string>

class Conexao98ClientApp;

class IClientCommand {
public:
    virtual ~IClientCommand() = default;
    virtual void execute(Conexao98ClientApp& app, const std::string& arguments) = 0;
};

#endif //CONEXAO98_ICLIENTCOMMAND_H