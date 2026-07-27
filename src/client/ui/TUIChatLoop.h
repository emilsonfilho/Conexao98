//
// Created by Emilson Filho on 27/07/2026.
//

#ifndef CONEXAO98_TUICHATLOOP_H
#define CONEXAO98_TUICHATLOOP_H
#include "ChatPresenter.h"
#include "../main/IChatLoop.h"


class TUIChatLoop : public IChatLoop {
private:
    ChatPresenter& presenter;
public:
    TUIChatLoop(ChatPresenter& presenter);

    void run(const std::function<void(const std::string &)> &onSend) override;
    void stop() override;
};


#endif //CONEXAO98_TUICHATLOOP_H