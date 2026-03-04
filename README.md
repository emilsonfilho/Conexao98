# 🌐 Conexao98
Conexão98 é um chat LAN em modo texto, desenvolvido em C/C++, com arquitetura cliente–servidor baseada em sockets TCP.

Este projeto não utiliza frameworks de alto nível para a camada de rede; todo o protocolo de comunicação, serialização binária e roteamento de mensagens foram desenhados e implementados manualmente na unha.

## ✨ Features Atuais
- **Protocolo Binário Customizado:** Serialização própria de pacotes (Message, JoinMessage, ChatMessage).
- **Roteamento Inteligente:** Arquitetura baseada em `Handlers` para separar o tráfego da rede das regras de negócio.
- **Arquitetura Multithread:** Suporte a múltiplas conexões simultâneas sem travar o loop principal.
- **Design Orientado a Objetos:** Polimorfismo aplicado para tratar diferentes tipos de pacotes de forma transparente.

## 🚧 Roadmap & Melhorias
Este projeto está em evolução constante. Aqui estão os próximos passos arquiteturais

- [x] **Limpeza de Memória:** Migrar ponteiros crus para _smart pointers_ para eliminar _memory leaks_. [Ver Issue #1](https://github.com/emilsonfilho/Conexao98/issues/1)
- [ ] **Multiplataforma:** Abstrair a camada de sockets (atualmente usando Winsock2) para garantir que o código compile nativamente tanto no Windows quanto Linux.
- [ ] **Thread Safety (Mutex):** Implementar _mutex_ para proteger estruturas de dados compartilhadas contra acesso indevido da sessão crítica.
- [ ] **Thread Safety (Lock Guard):** Refatorar os bloqueios manuais aplicando para garantir o *unlock* automático e prevenir *deadlocks* no servidor.
- [ ] **Desconexão Graciosa:** Desenvolver um mecanismo para capturar quedas de conexão ou retornos vazios do *socket*, limpando a sessão com segurança e enviando um *broadcast* de saída para a sala.
- [ ] **Interface de Usuário (TUI/GUI):** Substituir o console puro por uma interface robusta para o cliente.
- [ ] **Segurança:** Implementar criptografia ponta-a-ponta e Handshake seguro na conexão inicial.

## ⚙️ Como rodar (Windows, por enquanto)

### Pré-Requisitos
* **CMake** (versão 3.10+)
* **Compilador C++** compatível com C++14/17 (MinGW/GCC ou MSVC)

### Passo a Passo (Terminal)
1. Clone o repositório
  ```bash
    git clone https://github.com/emilsonfilho/Conexao98.git 
  ```
2. Crie a pasta de build e compile
   ```bash
     mkdir build
     cd build
     cmake ..
     cmake --build .
   ```
3. Inicie os executáveis. 💣 **Importante**: Execute primeiro o servidor
   ```bash
     ./main_server.exe
     # Em outro terminal:
     ./main_client.exe # Faça isso com pelo menos 2 para um resultado visual melhor
   ```

Se você, assim como eu, usa o CLion, a vida é bem mais fácil:
1. Clone o repositório
2. _File > Open_
3. Selecione a pasta raiz do projeto
4. Aperte o play (ou _Shift+F10_) no server
5. Aperte o plau nos clients (para criar mais de um executável no CLion, faça _Edit Configurations > client > Allow multiple instances_)

Made with ❤️ by [Emilson Filho](https://github.com/emilsonfilho)
