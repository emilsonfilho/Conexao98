#ifndef CONEXAO98_SERVER98CLIENTAPP_H
#define CONEXAO98_SERVER98CLIENTAPP_H

#include "../app/ChatManager.h"
#include "../network/NetworkServer.h"

class Conexao98ServerApp {
private:
    std::unique_ptr<ChatManager> chatManager;
    std::unique_ptr<NetworkServer> server;
public:
    Conexao98ServerApp();
    ~Conexao98ServerApp();

    bool init();
    void run() const;
    void stop() const;
};


#endif //CONEXAO98_SERVER98CLIENTAPP_H