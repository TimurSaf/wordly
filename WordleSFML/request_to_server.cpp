#include "client_http.hpp"


std::string request_to_server(std::string mode, int len_w, std::string word = "")
{
    try
    {
        std::string host = "127.0.0.7";
        std::string const port = "80";
        int version = 11;

        net::io_context ioc;

        tcp::resolver resolver(ioc);
        beast::tcp_stream stream(ioc);

        auto const results = resolver.resolve(host, port);

        stream.connect(results);
    
        http::request<http::string_body> req{make_request(mode, len_w, word, host, version)};

        http::write(stream, req);

        beast::flat_buffer buffer;

        http::response<http::string_body> res;

        http::read(stream, buffer, res);
        std::string result = res.body();

        beast::error_code ec;
        stream.socket().shutdown(tcp::socket::shutdown_both, ec);

        if(ec && ec != beast::errc::not_connected)
            throw beast::system_error{ec};
        return result;
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return e.what();
    }
}


