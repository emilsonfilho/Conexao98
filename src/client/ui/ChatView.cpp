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
    inputOption.cursor_position = &state.cursorPosition;

    // Auto-complete
    inputOption.on_change = [&state] {
        if (!state.currentInput.empty() and state.currentInput[0] == '/') {
            state.isCommandMenuOpen = true;
            state.filteredCommands.clear();

            for (const auto command : state.allCommands)
                if (command.name.find(state.currentInput) == 0)
                    state.filteredCommands.push_back(command);

            if (state.selectedCommandIndex >= state.filteredCommands.size())
                state.selectedCommandIndex = 0;

            if (state.filteredCommands.empty())
                state.isCommandMenuOpen = false;
        } else {
            state.isCommandMenuOpen = false;
        }
    };

    const auto rawInput = ftxui::Input(&state.currentInput, "Digite sua mensagem....", inputOption);

    auto inputComponent = rawInput | ftxui::CatchEvent([&state, onEnter](const ftxui::Event &e) {
        if (!state.isCommandMenuOpen or state.filteredCommands.empty())
            return false;

        if (e == ftxui::Event::ArrowUp) {
            state.selectedCommandIndex = std::max(0, state.selectedCommandIndex - 1);
            return true;
        }

        if (e == ftxui::Event::ArrowDown) {
            state.selectedCommandIndex = std::min(
                static_cast<int>(state.filteredCommands.size()) - 1,
                state.selectedCommandIndex + 1
            );
            return true;
        }

        const std::string commandName = state.filteredCommands[state.selectedCommandIndex].name;

        if (e == ftxui::Event::Tab) {
            state.currentInput = commandName + " ";
            state.cursorPosition = state.currentInput.size();
            state.isCommandMenuOpen = false;
            return true;
        }

        if (e == ftxui::Event::Return) {
            if (state.currentInput == commandName) {
                state.isCommandMenuOpen = false;
                return false;
            }

            state.currentInput = commandName;
            state.cursorPosition = state.currentInput.size();
            state.isCommandMenuOpen = false;

            onEnter();
            return true;
        }

        return false;
    });

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
    auto mainLayout = ftxui::Renderer(inputComponent, [&state, inputComponent] {
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

        ftxui::Element commandMenuElement = ftxui::emptyElement();
        if (state.isCommandMenuOpen and !state.filteredCommands.empty()) {
            ftxui::Elements commandList;
            for (size_t i = 0; i < state.filteredCommands.size(); i++) {
                auto item = ftxui::vbox({
                    ftxui::text(state.filteredCommands[i].name) | ftxui::bold,
                    ftxui::text(state.filteredCommands[i].description) | ftxui::dim
                });

                if (i == state.selectedCommandIndex) item |= ftxui::inverted;

                commandList.push_back(item);
            }

            commandMenuElement = ftxui::window(
                ftxui::text(" Comandos "),
                ftxui::vbox(std::move(commandList))
            ) | ftxui::clear_under;
        }

        return ftxui::window(
            ftxui::text(" Conexão98 "),
            ftxui::hbox({
                // Lado Esquerdo: Chat e Input
                ftxui::vbox({
                    ftxui::vbox(std::move(msgElements)) | ftxui::flex,
                    commandMenuElement,
                    ftxui::separator(),
                    inputComponent->Render()
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
