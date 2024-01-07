/**
 * @file server.hpp
 * @brief Server class header file
 * @date 29-11-2023
 */

#pragma once

#include <iostream>
#include <chrono>
#include "../../engine/includes/network_library/boost_udp.hpp"
#include "../includes/parser.hpp"

#define UDP_SERVER_PORT 13152

/**
 * @brief Server class
 */
class Server {
    public:
        Server(int port = UDP_SERVER_PORT, std::string ip = IPADDRESS) : server_receive(port, ip) {}
        ~Server() = default;

        int run();
        void check_new_connections(std::string data);
        void check_new_deconnections(std::string data);
        void parse_data_received(Parser parser);
        std::vector<std::string> split(const std::string& str, const std::string& delim);

    private:
        UDPBoostNetwork::UDPReceiver server_receive;
        std::vector<UDPBoostNetwork::UDPSender> clients_send;
};