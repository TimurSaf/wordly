#include "http_server.hpp"

std::string file_name(int len_w) {
    if(len_w > 6 || len_w < 4){
        throw std::runtime_error("Invalid len of word: it should be 4, 5, 6");
    }
    std::string name {"dict_.txt"};
    if (len_w == 4) {
        name.insert(5, "4");
    } else if (len_w == 5) {
        name.insert(5, "5");
    } else if (len_w == 6) {
        name.insert(5, "6");
    }
    return name;
}