#include <iostream>
#include <string>

#define SERVER_PORT 9000
#define SERVER_MODE "server"

using std::string;

void logPort(uint32_t port) {
    std::cout << "Running on port " << port << std::endl;
}

void server() {
    std::cout << "Welcome to RockPaperScissorsLizardSpock server" << std::endl;
    uint32_t port = SERVER_PORT;
    logPort(port);
}

void client() {

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