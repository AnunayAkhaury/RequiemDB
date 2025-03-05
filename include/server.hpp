#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <unordered_map>
#include <mutex>
#include "../include/requiemstore.hpp"

#ifdef _WIN32  // Windows Specific
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")  
#else  // MAC/Linux
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <unistd.h>
#endif

class Server {
public:
    Server(int port);
    void start();
    
private:
    int serverSocket;
    int port;
    REQUIEMSTORE db;  
    std::mutex kvMutex;  

    void handleClient(int clientSocket);
    std::string processCommand(const std::string& command);

    #ifdef _WIN32
    void cleanupWinSock(); 
    #endif
};

#endif  // SERVER_HPP
