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
#include "../../engine/includes/ECS.hpp"

/**
 * @brief Server class
 */
class Server {
    public:
        Server(int port) : server_receive(port), _ecs(ECS()) {
            _ecs.registerComponent<Position>();
            _ecs.registerComponent<Rotation>();
            _ecs.registerComponent<Velocity>();
            _ecs.registerComponent<Health>();
            _ecs.registerComponent<Player>();
            _ecs.registerComponent<Npc>();
            _ecs.registerComponent<Sprite>();
        }
        ~Server() = default;

        int run();
        void init_new_entity(std::string data);
        void check_new_deconnections(std::string data);
        int find_free_id_player();
        void init_player(std::vector<std::string> data);
        void parse_data_received();
        std::vector<std::string> split(const std::string& str, const std::string& delim);

    private:
        UDPBoostNetwork::UDPReceiver server_receive;
        std::vector<UDPBoostNetwork::UDPSender> clients_send;
        ECS _ecs;
        Parser parser;

};