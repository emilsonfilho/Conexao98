#include "ChatView.h"

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_options.hpp"

ftxui::Component ChatView::create(ChatState &state, const std::function<void()> &onEnter) {
    ftxui::InputOption inputOption;
    inputOption.on_enter = onEnter;

    const auto input = ftxui::Input(&state.currentInput, "Digite sua mensagem....", inputOption);

    return ftxui::Renderer(input, [&state, input] {
        ftxui::Elements msgElements;
        for (const auto& msg : state.messages)
            msgElements.push_back(ftxui::text(msg));

        return ftxui::window(
            ftxui::text(" Conexão98 "),
            ftxui::vbox({
                ftxui::vbox(std::move(msgElements)) | ftxui::flex,
                ftxui::separator(),
                input->Render()
            })
        );
    });
}
