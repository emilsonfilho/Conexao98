//
// Created by Emilson Filho on 07/03/2026.
//

#ifndef CONEXAO98_CONEXAO98EXCEPTION_H
#define CONEXAO98_CONEXAO98EXCEPTION_H

#include <stdexcept>

class Conexao98Exception : public std::runtime_error {
public:
    explicit Conexao98Exception(const std::string& msg) : runtime_error(msg) {}
};

#endif //CONEXAO98_CONEXAO98EXCEPTION_H