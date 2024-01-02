/**
 * @file server.hpp
 * @brief Server class header file
 * @date 29-11-2023
 */

#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include "network.hpp"

#define UDP_PORT 13152

class Server {
    public:
        Server() : client_boost_receive(UDP_PORT) {};
        ~Server() = default;

        int run();
        void check_new_connections();

    private:
        Network::Receive client_boost_receive;
        std::vector<Network::Sender> clients;
};