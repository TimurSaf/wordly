#include "http_server.hpp"


template <class Body, class Allocator>
http::message_generator handle_request(
    beast::string_view doc_root,
    http::request<Body, http::basic_fields<Allocator>>&& req)
{
    auto const bad_request =
    [&req](beast::string_view why)
    {
        http::response<http::string_body> res{http::status::bad_request, req.version()};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/html");
        res.keep_alive(req.keep_alive());
        res.body() = std::string(why);
        res.prepare_payload();
        return res;
    };

    if(req.method() != http::verb::post &&
       req.method() != http::verb::get)
        return bad_request("Unknown HTTP-method");
    if (req.method() == http::verb::post) {
        std::string word = (req.body());
        auto const word_size = word.size();
        word = word.substr(5, word_size - 5);
        std::string body = check_word(word);
        auto const body_size = body.size();
        http::response<http::string_body> res{
            std::piecewise_construct,
            std::make_tuple(std::move(body)),
            std::make_tuple(http::status::ok, req.version())};
        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/html");
        res.content_length(body_size);
        res.keep_alive(req.keep_alive());
        return res;
        }
    std::string len_word_str {req.target()[11]};
    int len_word {atoi(len_word_str.c_str())};

    http::string_body::value_type body = get_word(len_word);
    auto const size = body.size();

    http::response<http::string_body> res{
        std::piecewise_construct,
        std::make_tuple(std::move(body)),
        std::make_tuple(http::status::ok, req.version())};
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/html");
    res.content_length(size);
    res.keep_alive(req.keep_alive());
    return res;
}



void do_session(
    tcp::socket& socket,
    std::string const& doc_root)
{
    beast::error_code ec;

    beast::flat_buffer buffer;

    for(;;)
    {
        http::request<http::string_body> req;
        http::read(socket, buffer, req, ec);
        if(ec == http::error::end_of_stream)
            break;
        if(ec){
            std::cerr << "read" << ": " << ec.message() << "\n";
        }
        http::message_generator msg =
            handle_request(doc_root, std::move(req));

        bool keep_alive = msg.keep_alive();

        beast::write(socket, std::move(msg), ec);

        if(ec){
            std::cerr << "write" << ": " << ec.message() << "\n";
        }
        if(! keep_alive){
            break;
        }
    }
    socket.shutdown(tcp::socket::shutdown_send, ec);

}

