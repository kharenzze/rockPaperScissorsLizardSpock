#include <iostream>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>
#include <cstdio>
#include <sys/socket.h>
#include <cstdlib>
#include <netinet/in.h>

#include "Game.h"

#define SERVER_PORT 9000
#define SERVER_MODE "server"
#define BUFFER_LENGTH 1024

using std::string;

void logPort(uint32_t port) {
    std::cout << "Running on port " << port << std::endl;
}

int getSocketPort(int socket) {
    struct sockaddr_in address;
    socklen_t len;
    getsockname(socket, (struct sockaddr *)&address, &len);
    const auto p = ntohs(address.sin_port);
    logPort(p);
    return p;
}

int client() {
    struct sockaddr_in address;
    struct sockaddr_in serv_addr;
    const char *hello = "Hello from client";
    char buffer[BUFFER_LENGTH] = {0};
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVER_PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    int port = getSocketPort(sock);
    send(sock , hello , strlen(hello) , 0 );
    return 0;
}

int openServerPort(int port, struct sockaddr_in &address, socklen_t addr_len) {
    int server_fd;
    int opt = 1;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    /*
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    */
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             addr_len)<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

//    valread = read( new_socket , buffer, 1024);
//    printf("%s\n",buffer );
//    send(new_socket , hello , strlen(hello) , 0 );
    return server_fd;
}

void serverGameTask(int socket) {
    Game game();
    char buffer[BUFFER_LENGTH];
    auto valRead = read(socket, buffer, BUFFER_LENGTH);
    std::cout << buffer << std::endl;
};

void server() {
    std::cout << "Welcome to RockPaperScissorsLizardSpock server" << std::endl;

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(SERVER_PORT);
    socklen_t addr_len = sizeof(address);

    int server_fd = openServerPort(SERVER_PORT, address, addr_len);

    //loop accepting new connections
    while (true) {
        int new_socket = accept(server_fd, (struct sockaddr *)&address, &addr_len);
        if (new_socket < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        serverGameTask(new_socket);
    }

}

int main(int argc, char* argv[]) {
    bool isServer = false;
    if (argc == 2) {
        const auto mode = string(argv[1]);
        isServer = mode == SERVER_MODE;
    }

    if (isServer) {
        server();
    } else {
        client();
    }

    return 0;
}