#include <iostream>
#include <sstream>
#include <string>
#include "../include/requiemstore.hpp"


int main() {
    REQUIEMSTORE store;
    std::string line;

    std::cout << "Welcome to REQUIEMDB (CLI).\n";
    std::cout << "Commands: SET key value, GET key, DEL key, EXIT\n\n";

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) {
            break; 
        }

        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "SET") {
            std::string key, value;
            ss >> key >> value;
            if (key.empty() || value.empty()) {
                std::cout << "Error: SET requires a key and a value.\n";
                continue;
            }
            store.set(key, value);
            std::cout << "OK\n";
        }
        else if (cmd == "GET") {
            std::string key;
            ss >> key;
            if (key.empty()) {
                std::cout << "Error: GET requires a key.\n";
                continue;
            }
            std::string result = store.get(key);
            if (result.empty()) {
                std::cout << "(nil)\n";
            } else {
                std::cout << result << "\n";
            }
        }
        else if (cmd == "DEL") {
            std::string key;
            ss >> key;
            if (key.empty()) {
                std::cout << "Error: DEL requires a key.\n";
                continue;
            }
            bool deleted = store.del(key);
            std::cout << (deleted ? "1\n" : "0\n");
        }
        else if (cmd == "EXIT") {
            std::cout << "Bye!\n";
            break;
        }
        else if (cmd.empty()) {
            continue;
        }
        else {
            std::cout << "Unknown command: " << cmd << "\n";
        }
    }

    return 0;
}
