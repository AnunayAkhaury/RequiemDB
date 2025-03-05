#include <iostream>
#include "../include/server.hpp"

int main() {
    int port = 6379; 

    std::cout << "Starting REQUIEMDB server on port " << port << "...\n";

    Server server(port);
    server.start();  

    return 0;
}
