#ifndef CONEXAO98_CHATVIEW_H
#define CONEXAO98_CHATVIEW_H

#include <functional>

#include "ChatState.h"
#include "ftxui/component/component_base.hpp"


class ChatView {
    static ftxui::Color getFtxuiColor(UserColor c);
public:
    static ftxui::Component create(ChatState& state, const std::function<void()> &onEnter, const std::function<void(UserColor)>& onColorSelected);
};


#endif //CONEXAO98_CHATVIEW_H