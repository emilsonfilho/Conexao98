#include "Conexao98ClientApp.h"

#include "../ConsoleChatListener.h"
#include "../../common/exceptions/SystemException.h"
#include "../../common/platform/SocketHelper.h"
#include "../../protocol/messages/ChangeColorMessage.h"
#include "../../protocol/messages/ChatMessage.h"
#include "../../protocol/messages/JoinMessage.h"
#include "../commands/ColorCommand.h"
#include "../commands/ExitCommand.h"

Conexao98ClientApp::Conexao98ClientApp(std::unique_ptr<ConnectionListener> listener, std::unique_ptr<IChatLoop> loop)
    : clientListener(std::move(listener)), loop(std::move(loop)), isActive(false), isWSAInitialized(false) {
    client = std::make_unique<NetworkClient>(clientListener.get());

    commandDispatcher = CommandDispatcher();
    commandDispatcher.registerCommand("/sair", std::make_unique<ExitCommand>());
    commandDispatcher.registerCommand("/cor", std::make_unique<ColorCommand>());
}

Conexao98ClientApp::~Conexao98ClientApp() {
    if (isWSAInitialized) SocketHelper::cleanupSystem();
}

bool Conexao98ClientApp::init(const std::string& ip, uint16_t port, const std::string& nickname, UserColor color) {
    try {
       if (!SocketHelper::initSystem())
            throw SystemException("Network initialization failed.");

        isWSAInitialized = true;

        this->nickname = nickname;
        client->connectToServer(ip, port);

        JoinMessage joinMsg(UserMetadata(nickname, color));
        client->sendMessage(&joinMsg);

        isActive = true;
        return true;
    } catch (std::runtime_error& e) {
        std::cerr << e.what();
        return false;
    }
}

void Conexao98ClientApp::run() {
    loop->run(
        [this](const std::string& inputText) {
            if (!commandDispatcher.dispatch(inputText, *this)) {
                ChatMessage text(inputText);
                this->client->sendMessage(&text);
            }
        },
        [this](const UserColor& newColor) {
            ChangeColorMessage msg(newColor);
            this->client->sendMessage(&msg);
        }
    );
}

void Conexao98ClientApp::stop() {
    isActive = false;

    if (loop) loop->stop();

    std::cout << "Volte sempre!\n";
}

void Conexao98ClientApp::requestColorMenu() const {
    if (loop) loop->showColorMenu();
}
