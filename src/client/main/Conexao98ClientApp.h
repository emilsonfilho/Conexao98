#ifndef CONEXAO98_CONEXAO98CLIENTAPP_H
#define CONEXAO98_CONEXAO98CLIENTAPP_H

#include "../../network/NetworkClient.h"

class Conexao98ClientApp {
private:
    std::string nickname;

    std::unique_ptr<ConnectionListener> clientListener;
    std::unique_ptr<NetworkClient> client;

    bool isActive;
public:
    Conexao98ClientApp();
    ~Conexao98ClientApp();

    bool init();
    void run();
    void stop();
};


#endif //CONEXAO98_CONEXAO98CLIENTAPP_H