#ifndef REQUIEMSTORE_HPP
#define REQUIEMSTORE_HPP

#include <string>
#include <unordered_map>

class REQUIEMSTORE {
    public:
        bool set(const std:: string&key, const std::string &value);
        std::string get(const std::string &key) const;
        bool del(const std::string &key);
    private:
        std::unordered_map<std::string, std::string> data;
};

#endif