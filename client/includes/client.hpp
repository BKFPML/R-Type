/**
 * @file client.hpp
 * @brief Client class header file
 * @date 29-11-2023
 */

# pragma once

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <thread>
#include <iostream>

using boost::asio::ip::address;
using boost::asio::ip::udp;

#define IPADDRESS "127.0.0.1" // "192.168.1.64"
#define UDP_PORT 13251

namespace rtype
{
    const std::string WINDOW_NAME = "R-Type";
    const int WINDOW_WIDTH = 1920;
    const int WINDOW_HEIGHT = 1080;

    class Client {
        public:
            Client();
            ~Client();

            void run();

        private:

    };
}

class Network {
    public: 
        class Receive {
            public:
                boost::asio::io_service io_service;
                udp::socket socket{io_service};
                boost::array<char, 1024> recv_buffer;
                udp::endpoint remote_endpoint;

                int count = 0;

                void handle_receive(const boost::system::error_code &error, size_t bytes_transferred)
                {
                    if (error)
                    {
                        std::cout << "Receive failed: " << error.message() << "\n";
                        return;
                    }

                    std::cout << "Received: '" << std::string(recv_buffer.begin(), recv_buffer.begin() + bytes_transferred) << "' (" << error.message() << ")\n";

                    if (++count > 0)
                    {
                        std::cout << "Count: " << count << "\n";
                        wait();
                    }
                }

                void wait()
                {
                    socket.async_receive_from(boost::asio::buffer(recv_buffer),
                                            remote_endpoint,
                                            boost::bind(&Receive::handle_receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                }

                void receiver(int udp_port = UDP_PORT)
                {
                    socket.open(udp::v4());
                    socket.bind(udp::endpoint(address::from_string(IPADDRESS), udp_port));

                    wait();

                    std::cout << "Receiving\n";
                    io_service.run();
                    std::cout << "Receiver exit\n";
                }
        };

        class Sender {
            public:
                void send(std::string in, int port = UDP_PORT)
                {
                    boost::asio::io_service io_service;
                    udp::socket socket(io_service);
                    udp::endpoint remote_endpoint = udp::endpoint(address::from_string(IPADDRESS), port);
                    socket.open(udp::v4());

                    boost::system::error_code err;
                    auto sent = socket.send_to(boost::asio::buffer(in), remote_endpoint, 0, err);
                    socket.close();
                    std::cout << "Sent Payload --- " << in << "\n";
                }
        };
};