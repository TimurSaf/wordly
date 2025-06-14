#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "http_server.hpp"

TEST_CASE("Check correct name of dict")
{
    CHECK(file_name(4) == "dict_4.txt");
    CHECK(file_name(5) == "dict_5.txt");
    CHECK(file_name(6) == "dict_6.txt");
}

TEST_CASE("Invalid length of word")
{
    CHECK_THROWS_AS(file_name(1), std::runtime_error);
    CHECK_THROWS_AS(file_name(8), std::runtime_error);
}
