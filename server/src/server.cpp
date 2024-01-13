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
void Server::init_new_entity(std::string data)
{
    if (split(data, " ").front() == "new") {
        std::vector<std::string> data_split = split(data, " ");
        init_player(data_split);
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
void Server::parse_data_received()
{
    const std::vector<std::string>& received_data = server_receive.get_received_data();

    for (const auto& data : received_data) {
        init_new_entity(data);
        check_new_deconnections(data);

    }
    server_receive.clear_received_data();
}

void print_all_ecs_entity(ECS& ecs)
{
    std::cout << "--- ECS ---" << std::endl;
    for (auto& entity : ecs.getEntities()) {
        std::cout << "Entity: " << entity << std::endl;
        std::cout << "Position: " << ecs.getComponent<Position>(entity)->x << " " << ecs.getComponent<Position>(entity)->y << std::endl;
        std::cout << "Rotation: " << ecs.getComponent<Rotation>(entity)->angle << std::endl;
        std::cout << "Velocity: " << ecs.getComponent<Velocity>(entity)->x << " " << ecs.getComponent<Velocity>(entity)->y << std::endl;
        std::cout << "Health: " << ecs.getComponent<Health>(entity)->hp << std::endl;
        std::cout << "Player: " << ecs.getComponent<Player>(entity)->id << " " << ecs.getComponent<Player>(entity)->name << std::endl;
        std::cout << "Sprite: " << ecs.getComponent<Sprite>(entity)->texture << " " << ecs.getComponent<Sprite>(entity)->width << " " << ecs.getComponent<Sprite>(entity)->height << " " << ecs.getComponent<Sprite>(entity)->scale << std::endl;
        std::cout << std::endl;
    }
    std::cout << "-----------" << std::endl;
}

/**
 * @brief Server run Function
 *
 * @return int return code
 */
int Server::run()
{
    std::thread r([&]{ server_receive.receive();});
    auto now = std::chrono::system_clock::now();
    while (true)
    {
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - now).count() > 1000) {
            now = std::chrono::system_clock::now();
            print_all_ecs_entity(_ecs);
        }
        parse_data_received();
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
    Server server(13152);
    if (server.run() == 84)
        return 84;
    server.~Server();

    return 0;
}
