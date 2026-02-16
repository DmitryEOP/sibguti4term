#include <asio.hpp>
#include <iostream>
#include <string>

using asio::ip::tcp;

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 5)
        {
            std::cerr << "Usage: client <server_ip> <server_port> <number_i> <iterations>\n";
            return 1;
        }

        std::string server_ip = argv[1];
        short server_port = static_cast<short>(std::atoi(argv[2]));
        int i = std::atoi(argv[3]);
        int iterations = std::atoi(argv[4]);

        asio::io_context io_context;
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(server_ip, std::to_string(server_port));

        tcp::socket socket(io_context);
        asio::connect(socket, endpoints);

        std::cout << "Connected to server " << server_ip << ":" << server_port << std::endl;
        std::cout << "Sending number " << i << " " << iterations << " times with delay " << i << " sec\n";

        for (int count = 0; count < iterations; ++count)
        {
            std::string request = std::to_string(i) + "\n";
            asio::write(socket, asio::buffer(request));

            char reply[1024];
            size_t reply_length = asio::read(socket, asio::buffer(reply, 1024),
                                              asio::transfer_at_least(1));
            std::string response(reply, reply_length);
            while (!response.empty() && (response.back() == '\n' || response.back() == '\r'))
                response.pop_back();

            std::cout << "Iteration " << count + 1 << ": sent " << i << ", received " << response << std::endl;

            if (count < iterations - 1)
            {
                std::cout << "Waiting " << i << " seconds...\n";
                Sleep(i * 1000);
            }
        }

        std::cout << "Client finished.\n";
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}