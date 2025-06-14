#include "http_server.hpp"

int main(int argc, char* argv[])
{
    try
    {
        auto const address = net::ip::make_address("127.0.0.7");
        short const port = 80;
        std::string doc_root = ".";

        net::io_context ioc{1};

        tcp::acceptor acceptor{ioc, {address, port}};
        for(;;)
        {
            tcp::socket socket{ioc};

            acceptor.accept(socket);

            std::thread{std::bind(
                &do_session,
                std::move(socket),
                doc_root)}.detach();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
