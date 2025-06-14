#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "client_http.hpp"


TEST_CASE("GET request for word") 
{
    const std::string mode = "get_word";
    const int len_w = 5;
    const std::string word = ""; 
    const std::string host = "";
    const int version = 11;
    
    auto req = make_request(mode, len_w, word, host, version);
    
    CHECK(req.method() == http::verb::get);
    CHECK(req.target().starts_with("/pool_"));
    CHECK(req[http::field::user_agent] == BOOST_BEAST_VERSION_STRING);
    CHECK(req.body().empty());
    CHECK(req.version() == version);
}

TEST_CASE("POST request to check word") 
{
    const std::string mode = "check_word";
    const int len_w = 0;
    const std::string word = "test";
    const std::string host = "";
    const int version = 11;
    
    auto req = make_request(mode, len_w, word, host, version);
    
    CHECK(req.method() == http::verb::post);
    CHECK(req.target() == "/");
    CHECK(req[http::field::user_agent] == BOOST_BEAST_VERSION_STRING);
    CHECK(req[http::field::content_type] == "text/html");
    CHECK(req.body() == "word=test");
    CHECK(req.payload_size().value() == 9); 
    CHECK(req.version() == version);
}

TEST_CASE("Unsupported mode throws exception") {
    const std::string invalid_mode = "invalid_mode";
    const int len_w = 5;
    const std::string word = "test";
    const std::string host = "";
    const int version = 11;
    
    CHECK_THROWS_AS(make_request(invalid_mode, len_w, word, host, version), std::runtime_error);
}