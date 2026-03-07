//
// Created by Emilson Filho on 07/03/2026.
//

#ifndef CONEXAO98_PROTOCOLEXCEPTION_H
#define CONEXAO98_PROTOCOLEXCEPTION_H
#include "Conexao98Exception.h"

// Logic errors and packets
class ProtocolException : public Conexao98Exception {
public:
    explicit ProtocolException(const std::string& message) : Conexao98Exception(message) {}
};

#endif //CONEXAO98_PROTOCOLEXCEPTION_H