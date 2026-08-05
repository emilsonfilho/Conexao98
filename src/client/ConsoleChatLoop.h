//
// Created by Emilson Filho on 22/07/2026.
//

#ifndef CONEXAO98_CONSOLECHATLOOP_H
#define CONEXAO98_CONSOLECHATLOOP_H
#include "main/IChatLoop.h"


class ConsoleChatLoop : public IChatLoop {
private:
    bool isActive;
    std::function<void(UserColor)> onColorChangeCallback;
public:
    ConsoleChatLoop();

    void run(const std::function<void(const std::string &)> &onSend, const std::function<void(UserColor)>& onColorChange) override;
    void stop() override;
    void showColorMenu() override;
};


#endif //CONEXAO98_CONSOLECHATLOOP_H