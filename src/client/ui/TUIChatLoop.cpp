//
// Created by Emilson Filho on 27/07/2026.
//

#include "TUIChatLoop.h"

TUIChatLoop::TUIChatLoop(ChatPresenter &presenter): presenter(presenter) {}

void TUIChatLoop::run(const std::function<void(const std::string &)> &onSend) {
    presenter.setOnSendMessage(onSend);
    presenter.show();
}

void TUIChatLoop::stop() {
    presenter.close();
}
