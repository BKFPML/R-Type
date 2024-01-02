/**
 * @file boost.hpp
 * @brief Boost class header file
 * @date 30-12-2023
 */

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <thread>
#include <iostream>
#include <vector>
#include <chrono>

using boost::asio::ip::address;
using boost::asio::ip::udp;

class BoostNetwork
{
    public:
        BoostNetwork(int port, std::string ip) : _udp_port(port), _ip(ip) {

            remote_endpoint = udp::endpoint(address::from_string(_ip), _udp_port);

        };

        void send(std::string message) {
            socket.open(udp::v4());
            socket.send_to(boost::asio::buffer(message), remote_endpoint, 0, err);
            socket.close();
        }

    private:
        boost::asio::io_service io_service;
        udp::socket socket{io_service};
        boost::array<char, 1024> recv_buffer;
        udp::endpoint remote_endpoint;
        boost::system::error_code err;
        int _udp_port;
        std::string _ip;

};