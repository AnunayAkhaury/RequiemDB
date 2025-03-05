#include "../include/requiemstore.hpp"


bool REQUIEMSTORE::set(const std::string &key, const std::string &value) {
    data[key] = value;
    return true;  
}

std::string REQUIEMSTORE::get(const std::string &key) const {
    auto it = data.find(key);
    if (it != data.end()) {
        return it->second;
    }
    return "";  
}

bool REQUIEMSTORE::del(const std::string &key) {
    return data.erase(key) > 0;
}
