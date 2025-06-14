#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "http_server.hpp"

TEST_CASE("Check exist word return")
{
    std::string word_4 = "HOME";
    std::string word_5 = "NIGHT";
    std::string word_6 = "BRIGHT";

    CHECK(check_word(word_4) == "correct word");
    CHECK(check_word(word_5) == "correct word");
    CHECK(check_word(word_6) == "correct word");
}

TEST_CASE("Check invalid word")
{
    std::string word_4 = "NDHT";
    std::string word_5 = "SNDYR";
    std::string word_6 = "SNDNAT";

    CHECK(check_word(word_4) == "not exist");
    CHECK(check_word(word_5) == "not exist");
    CHECK(check_word(word_6) == "not exist");
}

TEST_CASE("Invalid length of word")
{
    std::string small_word = "try";
    std::string large_word = "quality";

    CHECK_THROWS_AS(check_word(small_word), std::runtime_error);
    CHECK_THROWS_AS(check_word(large_word), std::runtime_error);
}