//
// Created by Emilson Filho on 07/03/2026.
//

#ifndef CONEXAO98_SYSTEMEXCEPTION_H
#define CONEXAO98_SYSTEMEXCEPTION_H
#include "Conexao98Exception.h"

// Operating System level failures
class SystemException : public Conexao98Exception {
public:
    explicit SystemException(const std::string& msg) : Conexao98Exception(msg) {}
};

#endif //CONEXAO98_SYSTEMEXCEPTION_H