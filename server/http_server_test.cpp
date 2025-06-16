#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "http_server.hpp"
#include <sstream>

TEST_CASE("GET request with valid target") {
        http::request<http::string_body> req;
        req.method(http::verb::get);
        req.target("/pool_dict_4.txt");
        req.version(11);
        req.keep_alive(true);
        
        http::response<http::string_body> res = generate_response(".", req);
        
        CHECK(res.result() == http::status::ok);
        CHECK(res[http::field::content_type] == "text/html");
        CHECK_FALSE(res.body().empty());
        CHECK(check_word(res.body()) == "correct word");
    }

TEST_CASE("POST request with valid body") {
    http::request<http::string_body> req;
    req.method(http::verb::post);
    req.target("/");
    req.version(11);
    req.keep_alive(true);
    req.body() = "word=TEST";
    int const size = 9;
    req.content_length(size);
    
    http::response<http::string_body> res = generate_response(".", req);
    
    CHECK(res.result() == http::status::ok);
    CHECK(res[http::field::content_type] == "text/html");
    CHECK_FALSE(res.body().empty());
    CHECK(res.body() == "correct word");
}

TEST_CASE("Unknown HTTP method") {
    http::request<http::string_body> req;
    req.method(http::verb::put);
    req.target("/");
    req.version(11);
    req.keep_alive(true);
    
    http::response<http::string_body> res = generate_response(".", req);
    
    CHECK(res.result() == http::status::bad_request);
    CHECK(res.body() == "Unknown HTTP-method");
}
