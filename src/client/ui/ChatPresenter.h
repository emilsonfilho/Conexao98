#ifndef CONEXAO98_CHATPRESENTER_H
#define CONEXAO98_CHATPRESENTER_H

#include <functional>

#include "ChatState.h"
#include "ftxui/component/screen_interactive.hpp"

class ChatPresenter {
private:
    ChatState state;
    ftxui::ScreenInteractive screen;
    std::function<void(std::string)> onSendMessage;
public:
    explicit ChatPresenter(std::function<void(std::string)> onSend);

    void show();

    void addMessage(const std::string& author, const std::string& text, UserColor color);

    void setOnSendMessage(const std::function<void(std::string)> &onSendMessage);
    void setOnlineUsers(const std::vector<std::pair<std::string, UserColor>> &users);
    void close();
};


#endif //CONEXAO98_CHATPRESENTER_H