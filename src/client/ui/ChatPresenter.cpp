#include "ChatPresenter.h"
#include "ChatView.h"

#include <ftxui/component/event.hpp>

ChatPresenter::ChatPresenter(std::function<void(std::string)> onSend)
    : screen(ftxui::ScreenInteractive::TerminalOutput()),
      onSendMessage(std::move(onSend)) {}

void ChatPresenter::show() {
    const auto component = ChatView::create(state, [this] {
        if (!state.currentInput.empty()) {
            std::string inputCopy = state.currentInput;

            onSendMessage(inputCopy);

            if (inputCopy.empty() or inputCopy[0] != '/')
                state.messages.push_back({ "Você", state.currentInput, UserColor::DEFAULT });

            state.currentInput.clear();
            state.cursorPosition = 0;
        }
    }, [this](UserColor newColor) {
        if (onChangeColorCallback) onChangeColorCallback(newColor);
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

void ChatPresenter::setOnChangeColor(const std::function<void(UserColor)> &onChangeColor) {
    onChangeColorCallback = onChangeColor;
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

void ChatPresenter::showColorMenu() {
    screen.Post([this] {
        state.isColorMenuOpen = true;
    });

    screen.PostEvent(ftxui::Event::Custom);
}
