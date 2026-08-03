#ifndef CONEXAO98_CONEXAO98CLIENTAPP_H
#define CONEXAO98_CONEXAO98CLIENTAPP_H

#include "IChatLoop.h"
#include "../../network/NetworkClient.h"
#include "../../protocol/UserColor.h"
#include "../commands/CommandDispatcher.h"

class Conexao98ClientApp {
private:
    std::string nickname;

    std::unique_ptr<ConnectionListener> clientListener;
    std::unique_ptr<NetworkClient> client;
    std::unique_ptr<IChatLoop> loop;

    bool isActive;
    bool isWSAInitialized;

    CommandDispatcher commandDispatcher;
public:
    Conexao98ClientApp(std::unique_ptr<ConnectionListener> listener, std::unique_ptr<IChatLoop> loop);
    ~Conexao98ClientApp();

    bool init(const std::string& ip, uint16_t port, const std::string& nickname, UserColor color);
    void run();
    void stop();
};


#endif //CONEXAO98_CONEXAO98CLIENTAPP_H