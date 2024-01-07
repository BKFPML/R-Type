/**
 * @file server.hpp
 * @brief Server class header file
 * @date 29-11-2023
 */

#pragma once

#include <iostream>
#include <chrono>
#include "../../engine/includes/network_library/boost_udp.hpp"

#define UDP_SERVER_PORT 13152

class Server {
    public:
        Server(int port = UDP_SERVER_PORT, std::string ip = IPADDRESS) : server_receive(port, ip) {}
        ~Server() = default;

        int run();
        void check_new_connections();

    private:
        UDPBoostNetwork::UDPReceiver server_receive;
        std::vector<UDPBoostNetwork::UDPSender> clients_send;
};