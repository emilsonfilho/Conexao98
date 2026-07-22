#ifndef CONEXAO98_CHATVIEW_H
#define CONEXAO98_CHATVIEW_H

#include <functional>

#include "ChatState.h"
#include "ftxui/component/component_base.hpp"


class ChatView {
public:
    static ftxui::Component create(ChatState& state, const std::function<void()> &onEnter);
};


#endif //CONEXAO98_CHATVIEW_H