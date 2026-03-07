//
// Created by Emilson Filho on 07/03/2026.
//

#ifndef CONEXAO98_NETWORKEXCEPTION_H
#define CONEXAO98_NETWORKEXCEPTION_H
#include <stdexcept>

#include "Conexao98Exception.h"

// Connectivity failures
class NetworkException : public Conexao98Exception {
public:
    explicit NetworkException(const std::string& msg) : Conexao98Exception(msg) {}
};

#endif //CONEXAO98_NETWORKEXCEPTION_H