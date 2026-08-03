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
            state.messages.push_back({ "Você", state.currentInput, UserColor::DEFAULT });
            state.currentInput.clear();
        }
    });

    screen.Loop(component);
}

void ChatPresenter::addMessage(const std::string &author, const std::string& text, UserColor color) {
    screen.Post([this, author, text, color] {
        state.messages.push_back({ author, text, color });
    });

    screen.PostEvent(ftxui::Event::Custom);
}

void ChatPresenter::setOnSendMessage(const std::function<void(std::string)> &onSend) {
    onSendMessage = onSend;
}

void ChatPresenter::setOnlineUsers(const std::vector<std::pair<std::string, UserColor>> &users) {
    screen.Post([this, users] {
        state.onlineUsers = users;
    });

    screen.PostEvent(ftxui::Event::Custom);
}

void ChatPresenter::close() {
    screen.Exit();
}
