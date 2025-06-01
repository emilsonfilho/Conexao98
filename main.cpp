#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

#include "shared/load-env.hpp"
#include "shared/parse-env-int.hpp"

using namespace std;

int main() {
	unordered_map<string, string> env = load_env(".env");

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("Error: Socket");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(parse_env_int(env, "PORT"));

	if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
		perror("Error: Invalid address / address not suported");
		exit(EXIT_FAILURE);
	}

	if (connect(sock, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
		perror("Error: Connection failed");
		exit(EXIT_FAILURE);
	}

	string message = "";
	do {
		cout << "[you]: ";
		getline(cin, message);

		send(sock, message.c_str(), message.size(), 0);

		int BUFFER_SIZE = parse_env_int(env, "BUFFER_SIZE");
		char buffer[BUFFER_SIZE] = {0};
	    ssize_t valread = read(sock, buffer, BUFFER_SIZE);
	    std::cout << "Received: " << buffer << std::endl;
	} while (message != "/exit");

    // Close the socket
    close(sock);

	return 0;
}