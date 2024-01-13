/**
 * @file server.cpp
 * @brief Main file for the server
 * @date 2023-11-29
 */

#include "../includes/server.hpp"
#include "levels.hpp"

/**
 * @brief Check for new connections
 * 
 * @param clients 
 * @param client_boost_receive 
 * @return std::vector<Network::Sender> 
 */
void Server::check_new_connections(std::string data)
{
    if (split(data, " ").front() == "new") {
        std::cout << "New connection: " << data << std::endl;
        std::cout << "Set port to: " << split(data, " ").back() << std::endl;
        for (auto& client : clients_send) {
            client.send("new " + split(data, " ").back());
        }
        std::string ip = split(data, " ").back();
        std::cout << "Port " << std::stoi(split(ip, ":").back()) << ",IP "<< split(ip, ":").front() << std::endl;
        clients_send.push_back(UDPBoostNetwork::UDPSender(std::stoi(split(ip, ":").back()), split(ip, ":").front()));

        for (int i = 0; i < clients_send.size() - 1; i++) {
            clients_send.back().send("new " + clients_send[i].get_ip() + ":" + std::to_string(clients_send[i].get_port()));
        }
    }
}

/**
 * @brief Check for new connections
 * 
 * @param clients 
 * @param client_boost_receive 
 * @return std::vector<Network::Sender> 
 */
void Server::check_new_deconnections(std::string data)
{
    if (split(data, " ").front() == "quit") {
        for (int i = 0; i < clients_send.size(); i++) {
            if (clients_send[i].get_port() == std::stoi(split(split(data, " ").back(), ":").back()) && clients_send[i].get_ip() == split(split(data, " ").back(), ":").front()) {
                std::cout << "Client: " << split(data, " ").back() << " erased" << std::endl;
                for (auto& client : clients_send) {
                    client.send("quit " + split(data, " ").back());
                }
                clients_send.erase(clients_send.begin() + i);
                break;
            }
        }
    }

}

/**
 * @brief Split a string
 * 
 * @param str 
 * @param token 
 * @return std::vector<std::string> 
 */
std::vector<std::string> Server::split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;

    do {
        pos = str.find(delim, prev);
        if (pos == std::string::npos)
            pos = str.length();
        std::string token = str.substr(prev, pos - prev);
        if (!token.empty())
            tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());

    return tokens;
}

/**
 * @brief Parse data received
 * 
 * @param clients 
 * @param client_boost_receive 
 */
void Server::parse_data_received(Parser parser)
{
    const std::vector<std::string>& received_data = server_receive.get_received_data();

    for (const auto& data : received_data) {
        check_new_connections(data);
        check_new_deconnections(data);

    }
    server_receive.clear_received_data();
}

/**
 * @brief Server run Function
 *
 * @return int return code
 */
int Server::run()
{
    std::thread r([&]{ server_receive.receive();});
    auto start_time = std::chrono::high_resolution_clock::now();
    Parser parser;

    while (true)
    {
        parse_data_received(parser);
        if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start_time).count() > 3) {
            for (auto& client : clients_send) {
                client.send("hello from the server");
            }
            start_time = std::chrono::high_resolution_clock::now();
        }
    }
    r.join();
    return 0;
}

/**
 * @brief Server Main Function
 *
 * @return int return code
 */
int main()
{
    // Server server(13152);
    // if (server.run() == 84)
    //     return 84;
    // server.~Server();

    std::shared_ptr<ECS> ecs = std::make_shared<ECS>();
    ecs->registerComponent<Position>();
    ecs->registerComponent<Rotation>();
    ecs->registerComponent<Velocity>();
    ecs->registerComponent<Health>();
    ecs->registerComponent<Player>();
    ecs->registerComponent<Enemy>();

    ecs = Levels::loadLevel("server/levels/config_files/level_1.conf", ecs);

    auto entities = ecs->getEntities();
    for (auto& entity : entities) {
        std::cout << "Entity: " << entity << std::endl;
        if (ecs->hasComponent<Position>(entity)) {
            auto position = ecs->getComponent<Position>(entity);
            std::cout << "Position: " << position->x << ", " << position->y << std::endl;
        }
        if (ecs->hasComponent<Rotation>(entity)) {
            auto rotation = ecs->getComponent<Rotation>(entity);
            std::cout << "Rotation: " << rotation->angle << std::endl;
        }
        if (ecs->hasComponent<Velocity>(entity)) {
            auto velocity = ecs->getComponent<Velocity>(entity);
            std::cout << "Velocity: " << velocity->x << ", " << velocity->y << ", " << velocity->magnitude << std::endl;
        }
        if (ecs->hasComponent<Health>(entity)) {
            auto health = ecs->getComponent<Health>(entity);
            std::cout << "Health: " << health->hp << std::endl;
        }
        if (ecs->hasComponent<Player>(entity)) {
            auto player = ecs->getComponent<Player>(entity);
            std::cout << "Player" << player->id << std::endl;
        }
        if (ecs->hasComponent<Enemy>(entity)) {
            auto enemy = ecs->getComponent<Enemy>(entity);
            std::cout << "Enemy" << enemy->name << std::endl;
        }
        if (ecs->hasComponent<SpawnTime>(entity)) {
            auto spawnTime = ecs->getComponent<SpawnTime>(entity);
            std::cout << "SpawnTime" << spawnTime->time << std::endl;
        }
    }

    return 0;
}
