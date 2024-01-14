/**
 * @file server.hpp
 * @brief Server class header file
 * @date 29-11-2023
 */

#pragma once

#include <iostream>
#include <chrono>
#include <fstream>
#include <functional>
#include <unordered_map>

#include "../../engine/includes/network_library/boost_udp.hpp"
#include "../../engine/includes/parser.hpp"
#include "../../engine/includes/ECS.hpp"

/**
 * @brief Server class
 */
class Server {
    public:
        Server(int port) : server_receive(port), _ecs(ECS()), game_launch(false) {
            _ecs.registerComponent<Position>();
            _ecs.registerComponent<Rotation>();
            _ecs.registerComponent<Velocity>();
            _ecs.registerComponent<Health>();
            _ecs.registerComponent<Player>();
            _ecs.registerComponent<Enemy>();
            _ecs.registerComponent<Sprite>();
            _ecs.registerComponent<Bullet>();
            _ecs.registerComponent<SpawnTime>();
            _ecs.registerComponent<Freeze>();
            _ecs.registerComponent<Attack>();
            _ecs.registerComponent<HealthPack>();
            _ecs.registerComponent<Collision>();
            _ecs.registerSystem<MovementSystem>();
            _ecs.registerSystem<CollisionSystem>();




            _componentFactories = {
                {"Player", [this](ECS::Entity entity, const std::unordered_map<std::string, std::string>& params) { createPlayerComponent(entity, params); }},
                {"Position", [this](ECS::Entity entity, const std::unordered_map<std::string, std::string>& params) { createPositionComponent(entity, params); }},
                {"Velocity", [this](ECS::Entity entity, const std::unordered_map<std::string, std::string>& params) { createVelocityComponent(entity, params); }},
                {"Rotation", [this](ECS::Entity entity, const std::unordered_map<std::string, std::string>& params) { createRotationComponent(entity, params); }},
                {"Health", [this](ECS::Entity entity, const std::unordered_map<std::string, std::string>& params) { createHealthComponent(entity, params); }},
                {"Sprite", [this](ECS::Entity entity, const std::unordered_map<std::string, std::string>& params) { createSpriteComponent(entity, params); }},
                {"Enemy", [this](ECS::Entity entity, const std::unordered_map<std::string, std::string>& params) { createEnemyComponent(entity, params); }},
                {"SpawnTime", [this](ECS::Entity entity, const std::unordered_map<std::string, std::string>& params) { createSpawnTimeComponent(entity, params); }},
                {"Collision", [this](ECS::Entity entity, const std::unordered_map<std::string, std::string>& params) { createCollisionComponent(entity, params); }},
                {"HealthPack", [this](ECS::Entity entity, const std::unordered_map<std::string, std::string>& params) { createHealthPackComponent(entity, params); }}
            };
        }
        ~Server() = default;

        int run();
        void init_entity(std::string data);
        void delete_entity(std::string data);
        int find_free_id_player();
        void init_player(std::vector<std::string> data);
        void parse_data_received();
        std::vector<std::string> split(const std::string& str, const std::string& delim);

        //* Enemies
        void init_enemies();

        //* Levels
        void loadLevel(const std::string& levelConfig);
        void processJsonObject(const nlohmann::json& jsonObj);
        void createHealthComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params);
        void createRotationComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params);
        void createVelocityComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params);
        void createSpriteComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params);
        void createPositionComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params);
        void createEnemyComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params);
        void createPlayerComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params);
        void createSpawnTimeComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params);
        void createCollisionComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params);
        void createHealthPackComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params);

    private:
        UDPBoostNetwork::UDPReceiver server_receive;
        std::vector<UDPBoostNetwork::UDPSender> clients_send;
        std::vector<int> clients_send_id;
        ECS _ecs;
        Parser parser;
        std::vector<ECS::Entity> _enemies;
        std::chrono::time_point<std::chrono::system_clock> _start_wave;
        /**
        * @brief Component factories
        *
        * @note This is a map of component types to functions that create the component
        */
        std::unordered_map<std::string, std::function<void(ECS::Entity, const std::unordered_map<std::string, std::string>&)>> _componentFactories;
        bool game_launch;
};
