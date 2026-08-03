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

        ftxui::Elements userElements;
        for (const auto& user : state.onlineUsers)
            userElements.push_back(ftxui::text(". " + user) | ftxui::color(ftxui::Color::GreenLight));

        if (userElements.empty())
            userElements.push_back(ftxui::text("Só você por aqui...") | ftxui::dim);

        return ftxui::window(
            ftxui::text(" Conexão98 "),
            ftxui::hbox({
                // Lado Esquerdo: Chat e Input
                ftxui::vbox({
                    ftxui::vbox(std::move(msgElements)) | ftxui::flex,
                    ftxui::separator(),
                    input->Render()
                }) | ftxui::flex,

                ftxui::separator(),

                // Lado Direito: Usuários Online
                ftxui::vbox({
                    ftxui::text(" Online ") | ftxui::center | ftxui::bold,
                    ftxui::separator(),
                    ftxui::vbox(std::move(userElements)) | ftxui::yflex
                }) | ftxui::size(ftxui::WIDTH, ftxui::GREATER_THAN, 20)
            })
        );
    });
}
