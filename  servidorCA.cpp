// ==== padrão ====
#include <iostream>
// padrão c++
#include <string>
// manipular strings 
#include <cstring>
 // manipular strings estilo C como strlen() memset() strcmp()
// usada para trabalhar com buffers(vectores de char) 
#include <unistd.h>
 // biblioteca POPSIX para usar sockets linux
// read() write() fork() sleep()

// ==== rede ====
#include <sys/socket.h>
// funções para criar e manipular os sockets 
// socket() bind() listen() accept() connect() send() recv()
#include <netinet/in.h>
// define estruturas e constantes para endereço de rede
// sockaddr_in INNADDR_ANY htons() comversão de bit order
#include <arpa/inet.h>
// fornece funções para comversão entre strings e endereços IP binarios
// inet_pton() inet_ntop()


// ==== Para Servidor ====
#include <unordered_map>
// usada para menter registro dos clientes conectados
// unordered_map<int, std::string> associa um sockt (int)
// com o nome cliente (std::string)
#include <mutex>
// fornece a classe std::mutex uada para garantir EXCLUSÃO MUTUA (protecção contra acesso concorente)
// sem isso varias threads acessando clients poderiam causar erros
#include <thread>
// permite criar e controlar threads em c++ 
// std::thread(funcao, agrs);
// cada cliente conectado ao servidor roda em thread em separadas
#include <vector>
// vector



constexpr int PORT = 8080; // porta servidor
constexpr int BUFFER_SIZE = 1024; // tamanho do buffer de leitura

std::unordered_map<int, std::string> clients; // map sockets
std::mutex clients_mutex; // protege acesso ao mapa de clients


// função que envia uma mensagem para todos os clientes, exceto o remetente 
// sender_sock e o socket de quem enviou a mensagem ele n dev recebela
// msg a mensgaem a ser enviada para outros clientes
void broadcast_to_others(int sender_sock, const std::string& msg){
	std::lock_guard<std::mutex> lock(clients_mutex);
	// garante acesso exclusivo ao mapa clientes durante o envio da mensagem
	// (envia race condituions em ambientes multithreads)
	for(const auto& [sock, name] : clients){ // intera sobre todos os clientes
		if(sock != sender_sock){ // quem enviou n recebe
			send(sock, msg.c_str(), msg.size(), 0); // envia mensagem
		}
	}
}

// função executada por cada thread de cliente conctado
void handle_client(int clients_sock){
	{
		std::lock_guard<std::mutex> lock(clients_mutex);
		clients[clients_sock] = "cliente";
	}

	char buffer[BUFFER_SIZE] = {0};


	while(true){
	// servidor bloqueia aqui esperando a mensagem do cliente via read
	ssize_t bytes = read(clients_sock, buffer, BUFFER_SIZE);
		if(bytes<= 0){
			// le dados enviados pelo cliente
			std::lock_guard<std::mutex> lock(clients_mutex);
			clients.erase(clients_sock);
			close(clients_sock);
			break;
		}
		//transforma os dados recebidos em string
		std::string msg(buffer, bytes);

		broadcast_to_others(clients_sock, msg);

	}
}


int main (){
	int server_fd;
	// file descriptor do socket servidor um num inteiro


	int client_socket;
	//sera socket do cliente conectado

	struct sockaddr_in address;
	// estrutura que vai guardar IP servidor e sua porta

	socklen_t addrlen = sizeof(address);
	//tipo socklen_t vai guardar na variavel addrlen tamanho 
	//do da estrutura para guardar ip e porta servidor

	int opt = 1;
	// usado para configurar opções do socket


	// criando socket 
	// server_fd vai receber = socket() que vai criar novo socket
	// e passando AF_INET = IPv4
	// SOCK_STRAM que diz que coneção TCP (procolo orientado a conexão)
	// 0 usa protocolo padrão do TCP
	// server_fd deve ficar com um inteiro representado socket no sistema
	// ex: 317
	// se server_fd == 0 criação falhou error
	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
		perror("erro ao criar socket");
		exit(EXIT_FAILURE);
	}

	// configurando opções do socket
	// set sock opt -- setsockopt(); seta options socket
	// passa server_fd
	// SO_SOCKET - nivel da opção socket
	// SO_REUSEADDR permite reutilizar porta logo paos fechar servidor (libera a porta dps de fechar)
 	// SO_REUSEPORT permite multiplos sockets ouvirem na mesma porta(não é o padrão)
	// opt = 1 ativa tudo 
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	

	// Preenchendo estrutura do endereço
	address.sin_family = AF_INET; // IPv4
	address.sin_addr.s_addr = INADDR_ANY; // Aceita conexão de qualquer io
	address.sin_port = htons(PORT); // comverte porta para formato de rede
	// TCP/IP usa BIG ENDIAN (mais significativo primeiro)
	// processaod pode usar outros tipos como little endian



	/*
	O sistema operacional precisa saber em qual IP/porta o seu programa está ouvindo.
	Se o bind() falhar, outra aplicação pode estar usando a porta
	*/
	// agora quem tentar falar algo no  ip e na pprta SO vai saber que é o seu programa
	if(bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0){
		perror("Error no bind");
		exit(EXIT_FAILURE);
	}

	// inicia servidor em modo escuta
	// escuta e deixa fila com 10 clientes
	if(listen(server_fd, 10) < 0){
		perror("Error listen");
		exit(EXIT_FAILURE);
	} 

	
	std::cout <<" [servidor] Ouvindo na porta " << PORT << "....\n";

	while(true){
		// accept() fica bloqueado ate que alguem tente coneção
		//  usa socket cliente 
		client_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
		if(client_socket < 0){
			perror("Erro ao aceitar conexão");
			continue;
		}

		// cria uma thread para atender esse cliente
		std::thread(handle_client, client_socket).detach();
	}
	close(server_fd); // fecaha servidor
	return 0;
}

/*
1. Cria socket TCP.
2. Define IP e porta.
3. Usa bind() para associar socket à porta.
4. Usa listen() para escutar conexões.
5. Entra em loop:
   a) aceita nova conexão (accept).
   b) cria uma thread handle_client(client_sock).
   c) continua escutando outros clientes.
*/
