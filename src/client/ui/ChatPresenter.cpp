#include "ChatPresenter.h"
#include "ChatView.h"

#include <ftxui/component/event.hpp>

ChatPresenter::ChatPresenter(std::function<void(std::string)> onSend)
    : screen(ftxui::ScreenInteractive::TerminalOutput()),
      onSendMessage(std::move(onSend)) {}

void ChatPresenter::show() {
    const auto component = ChatView::create(state, [this] {
        if (!state.currentInput.empty()) {
            onSendMessage(state.currentInput);
            state.messages.push_back("[Você]: " + state.currentInput);
            state.currentInput.clear();
        }
    });

    screen.Loop(component);
}

void ChatPresenter::addMessage(const std::string &message) {
    screen.Post([this, message] {
        state.messages.push_back(message);
    });
}
