#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "http_server.hpp"

TEST_CASE("Returns correct length word")
{
    CHECK(get_word(4).size() == 4);
    CHECK(get_word(5).size() == 5);
    CHECK(get_word(6).size() == 6);
}

TEST_CASE("Check exist return word")
{
    std::string word_4 = get_word(4);
    std::string word_5 = get_word(5);
    std::string word_6 = get_word(6);

    CHECK(check_word(word_4) == "correct word");
    CHECK(check_word(word_5) == "correct word");
    CHECK(check_word(word_6) == "correct word");
}

TEST_CASE("Invalid length of word")
{
    CHECK_THROWS_AS(get_word(-5), std::runtime_error);
    CHECK_THROWS_AS(get_word(10), std::runtime_error);
}