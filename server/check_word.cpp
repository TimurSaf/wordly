#include "http_server.hpp"

std::string check_word(std::string& word) {
    int len_w = word.size();
    if(len_w > 6 || len_w < 4){
        throw std::runtime_error("Invalid len of word: it should be 4, 5, 6");
    }
    std::ifstream f_dict{file_name(len_w)};
    std::string line;
    while(std::getline(f_dict, line)) {
        if (word == line) {
            return "correct word";
        }
    }
    return "not exist";
}
