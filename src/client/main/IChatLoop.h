//
// Created by Emilson Filho on 22/07/2026.
//

#ifndef CONEXAO98_ICHATLOOP_H
#define CONEXAO98_ICHATLOOP_H

#include <functional>
#include <string>

#include "../../protocol/UserColor.h"

class IChatLoop {
public:
    virtual ~IChatLoop() = default;
    virtual void run(const std::function<void(const std::string&)>& onSend, const std::function<void(UserColor)>& onColorChange) = 0;
    virtual void stop() = 0;
    virtual void showColorMenu() = 0;
};

#endif //CONEXAO98_ICHATLOOP_H