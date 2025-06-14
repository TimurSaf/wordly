#include "client_http.hpp"


http::request<http::string_body> make_request(std::string const & mode, int len_w, std::string const & word, std::string const & host, int version)
{
    if (mode == "get_word") {
        std::string const target = "/pool_"+ file_name(len_w);
        http::request<http::string_body> req{http::verb::get, target, version};
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        return req;
    } else if (mode == "check_word") {
        std::string const target = "/";
        http::request<http::string_body> req{http::verb::post, target, version};
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        req.set(http::field::content_type, "text/html");
        std::string body = "word=" + word;
        auto const size = body.size();
        req.content_length(size);
        req.body() = body;
        return req;
    } else {
        throw std::runtime_error{"Unsupported mode: it can be 'get_word' and 'check_word'."};
    }
}