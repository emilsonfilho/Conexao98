#ifndef CONEXAO98_SERVER98CLIENTAPP_H
#define CONEXAO98_SERVER98CLIENTAPP_H

#include "../app/ChatManager.h"
#include "../network/NetworkServer.h"

class Server98ClientApp {
private:
    std::unique_ptr<ChatManager> chatManager;
    std::unique_ptr<NetworkServer> server;
public:
    Server98ClientApp();
    ~Server98ClientApp();

    bool init();
    void run();
    void stop();
};


#endif //CONEXAO98_SERVER98CLIENTAPP_H