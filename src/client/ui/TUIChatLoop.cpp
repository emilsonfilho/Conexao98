//
// Created by Emilson Filho on 27/07/2026.
//

#include "TUIChatLoop.h"

TUIChatLoop::TUIChatLoop(ChatPresenter &presenter): presenter(presenter) {}

void TUIChatLoop::run(const std::function<void(const std::string &)> &onSend, const std::function<void(UserColor)>& onColorChange) {
    presenter.setOnSendMessage(onSend);
    presenter.setOnChangeColor(onColorChange);
    presenter.show();
}

void TUIChatLoop::stop() {
    presenter.close();
}

void TUIChatLoop::showColorMenu() {
    presenter.showColorMenu();
}
