#include "../include/server.hpp"
#include <sstream>
#include <thread>

#ifdef _WIN32
    #define CLOSE_SOCKET closesocket
#else
    #define CLOSE_SOCKET close
#endif

Server::Server(int port) : port(port) {
#ifdef _WIN32  // Intializing Windows Socket
    WSADATA wsaData; 
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        exit(EXIT_FAILURE);
    }
#endif

    serverSocket = socket(AF_INET, SOCK_STREAM, 0); // Creating Server Socket
    if (serverSocket == -1) {
        std::cerr << "Error creating socket\n";
        exit(EXIT_FAILURE);
    }

    sockaddr_in serverAddr{};   // Binding Server to the port
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Binding failed\n";
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket, 5) < 0) {  // Listening for client connection, limit 5
        std::cerr << "Listening failed\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port " << port << "\n";
}

void Server :: start() {
    while(true) {
        int clientSocket = accept(serverSocket, nullptr, nullptr); // Waiting for client connection and creating new socket
        if (clientSocket < 0) {
            std::cerr << "Error accepeting connection\n";
            continue;
        }

        std::thread clientThread(&Server::handleClient, this, clientSocket);
        clientThread.detach();
    }
}
void Server :: handleClient(int clientSocket) {
    std::cout << "[Server] new client was connected";
    char buffer[1024] = {0};
    while (true){
        std::cout << "[Server] waiting for a new connection";
        int bytesRead = recv(clientSocket, buffer, 1024, 0); // Reading bytes into buffer
        if (bytesRead <=0){
            std::cout << "[Server] Client disconnected.\n";
            break;
        } 
        
        std::string request(buffer, bytesRead); // Convert buffer to string
        //request.erase(std::remove(request.begin(), request.end(), '\r'), request.end()); 
        std::cout << "[Server] Received: " << request << "\n";

        
        std::string response = processCommand(request); // Process the command
        std::cout << "[Server] Responding: " << response << "\n";
        response += "\n"; 
        send(clientSocket, response.c_str(), response.length(), 0); // Send responce back to client
    }
    std::cout << "[Server] Closing client socket...\n";
    CLOSE_SOCKET(clientSocket);
}

std::string Server :: processCommand(const std::string& command){
    std::stringstream ss(command);
    std::string cmd, key, value;
    ss >> cmd >> key >> value;

    if (cmd == "SET"){
        db.set(key, value);
        return "OK\n";
    }
    else if (cmd == "GET"){
        return db.get(key) + "\n";
    }
    else if (cmd == "DEL"){
        return db.del(key) ? "1\n" : "0\n";  
    }    
    return "ERROR: Invalid Command";

}