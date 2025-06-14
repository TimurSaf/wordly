#include "http_server.hpp"


std::string get_word(int len_w) {
    if(len_w > 6 || len_w < 4){
        throw std::runtime_error("Invalid len of word: it should be 4, 5, 6");
    }
    srand(time(0));
    std::vector<int> counts_words{94, 87, 76};
    int len_dict{counts_words[len_w - 4]};
    int index_word{rand() % len_dict};
    std::ifstream f_dict{"pool_" + file_name(len_w)};
    f_dict.seekg((len_w + 1) * index_word);
    std::string result;
    if (f_dict.is_open()) {
        std::getline(f_dict, result);
    }
    return result;
}

