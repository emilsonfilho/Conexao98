// #include <iostream>
//
// #include "Conexao98ClientApp.h"
// #include "../../common/exceptions/Conexao98Exception.h"
// #include "../ui/TerminalPrompter.h"
//
// int main(const int argc, char* argv[]) {
//     try {
//         uint16_t port = 0;
//         std::string ip;
//
//         if (argc == 1) {
//             ip = TerminalPrompter::askForIP();
//             port = TerminalPrompter::askForPort();
//         } else if (argc == 3) {
//             ip = argv[1];
//
//             if (const auto error = InputValidator::validatePort(argv[2], port); error != InputValidator::PortError::None) {
//                 std::cerr << "Porta inválida fornecida na linha de comando.\n";
//                 return EXIT_FAILURE;
//             }
//         } else {
//             std::cerr << "Uso: client [ip porta]\n";
//             return EXIT_FAILURE;
//         }
//
//         if (auto app = Conexao98ClientApp(); app.init(ip, port))
//             app.run();
//     } catch (const Conexao98Exception& e) {
//         std::cerr << "[CLIENT]: " << e.what() << "\n";
//     }
//
//     return 0;
// }

#include <string>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

int main() {
    std::string input_text;
    std::vector<std::string> messages;

    ftxui::InputOption input_option;
    input_option.on_enter = [&] {
        if (!input_text.empty()) {
            messages.push_back("Você " + input_text);
            input_text.clear();
        }
    };

    const ftxui::Component input = ftxui::Input(
        &input_text,
        "Digite sua mensagem...",
        input_option
    );

    const ftxui::Component layout = ftxui::Renderer(input, [&] {
        ftxui::Elements msg_elements;
        for (const auto& msg : messages)
            msg_elements.push_back(ftxui::text(msg));

        return ftxui::window(
            ftxui::text(" Conexão98 - Chat Local"),
            ftxui::vbox({
                ftxui::vbox(std::move(msg_elements)) | ftxui::flex,
                ftxui::separator(),
                input->Render()
            })
        );
    });

    auto screen = ftxui::ScreenInteractive::TerminalOutput();
    screen.Loop(layout);

    return 0;
}