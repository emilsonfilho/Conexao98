#include "ChatView.h"

#include <algorithm>

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_options.hpp"

ftxui::Color ChatView::getFtxuiColor(const UserColor c) {
    switch (c) {
        case UserColor::RED: return ftxui::Color::RedLight;
        case UserColor::GREEN: return ftxui::Color::GreenLight;
        case UserColor::BLUE: return ftxui::Color::BlueLight;
        case UserColor::YELLOW: return ftxui::Color::YellowLight;
        case UserColor::CYAN: return ftxui::Color::CyanLight;
        case UserColor::MAGENTA: return ftxui::Color::MagentaLight;
        default: return ftxui::Color::White;
    }
}

ftxui::Component ChatView::create(ChatState &state, const std::function<void()> &onEnter, const std::function<void(UserColor)>& onColorSelected) {
    ftxui::InputOption inputOption;
    inputOption.on_enter = onEnter;

    const auto input = ftxui::Input(&state.currentInput, "Digite sua mensagem....", inputOption);

    ftxui::RadioboxOption radioOption;
    radioOption.transform = [&state](const ftxui::EntryState& entry) {
        const auto it = std::find(state.colorMenuEntries.begin(), state.colorMenuEntries.end(), entry.label);
        const size_t index = std::distance(state.colorMenuEntries.begin(), it);

        const auto uColor = static_cast<UserColor>(index + 1);

        const ftxui::Color c = getFtxuiColor(uColor);

        auto element = ftxui::hbox({
            ftxui::text(entry.state ? "(*) " : "() "),
            ftxui::text(entry.label) | ftxui::color(c)
        });

        if (entry.active)
            element |= ftxui::inverted;

        return element;
    };

    auto radiobox = ftxui::Radiobox(&state.colorMenuEntries, &state.selectedColorIndex, radioOption);

    // Modal
    auto btnConfirm = ftxui::Button("Confirmar", [&state, onColorSelected] {
        state.isColorMenuOpen = false;
        onColorSelected(static_cast<UserColor>(state.selectedColorIndex + 1));
    }, ftxui::ButtonOption::Animated(ftxui::Color::Green));

    auto btnCancel = ftxui::Button("Cancelar", [&state] {
        state.isColorMenuOpen = false;
    }, ftxui::ButtonOption::Animated(ftxui::Color::Red));

    const auto modalContainer = ftxui::Container::Vertical({
        radiobox,
        ftxui::Container::Horizontal({btnConfirm, btnCancel})
    });

    const auto modalRenderer = ftxui::Renderer(modalContainer, [radiobox, btnConfirm, btnCancel] {
        return ftxui::vbox({
            ftxui::text(" Escolha sua nova cor: ") | ftxui::bold | ftxui::center,
            ftxui::separator(),
            radiobox->Render(),
            ftxui::separator(),
            ftxui::hbox({btnConfirm->Render(), ftxui::text("  "), btnCancel->Render()}) | ftxui::center
        }) | ftxui::border | ftxui::clear_under | ftxui::center; // clear_under apaga o que estiver atrás!
    });

    // Layout
    auto mainLayout = ftxui::Renderer(input, [&state, input] {
        ftxui::Elements msgElements;
        for (const auto& [author, text, color] : state.messages)
            msgElements.push_back(
                ftxui::hbox({
                    ftxui::text("[ " + author + " ]: ") | ftxui::color(getFtxuiColor(color)) | ftxui::bold,
                    ftxui::text(text)
                })
            );

        ftxui::Elements userElements;
        for (const auto& [user, color] : state.onlineUsers)
            userElements.push_back(
                ftxui::text(". " + user) | ftxui::color(getFtxuiColor(color))
            );

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

    mainLayout |= ftxui::Modal(modalRenderer, &state.isColorMenuOpen);

    return mainLayout;
}
