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
void Server::init_entity(std::string data)
{
    if (split(data, " ").front() == "new") {
        std::vector<std::string> data_split = split(data, " ");
        init_player(data_split);
    }
}
/**
 * @brief delete entity
 * 
 * @param data 
 */
void Server::delete_entity(std::string data)
{
    if (split(data, " ").front() == "delete") {
        std::vector<std::string> data_split = split(data, " ");
        if (data_split.at(1) == "player") {
            int playerIdToDelete = std::stoi(data_split.at(2));

            for (auto& id : clients_send_id) {
                if (id == playerIdToDelete) {
                    clients_send.erase(clients_send.begin() + id);
                    clients_send_id.erase(clients_send_id.begin() + id);
                    break;
                }
            }
            for (auto& client : clients_send) {
                client.send("delete player " + std::to_string(playerIdToDelete));
            }
            for (auto& entity : _ecs.getEntities()) {
                if (_ecs.hasComponent<Player>(entity)) {
                    if (_ecs.getComponent<Player>(entity)->id == playerIdToDelete) {
                        _ecs.removeEntity(entity);
                        break;
                    }
                }
            }
            if (playerIdToDelete == 0 && clients_send_id.size() > 0) {
                for (auto& client : clients_send) {
                    client.send("delete player " + std::to_string(clients_send_id.at(0)));
                }
                for (auto& entity : _ecs.getEntities()) {
                    if (_ecs.hasComponent<Player>(entity)) {
                        if (_ecs.getComponent<Player>(entity)->id == clients_send_id.at(0)) {
                            clients_send.front().send("new player 0 " + _ecs.getComponent<Player>(entity)->name + " you");
                        } else {
                            clients_send.front().send("new player 0 " + _ecs.getComponent<Player>(entity)->name);
                        }
                    }
                }
                clients_send_id.at(0) = 0;
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
        init_entity(data);
        delete_entity(data);
        if (split(data, " ").front() == "start") {
            std::vector<std::string> data_split = split(data, " ");
            for (auto& client : clients_send) {
                client.send("start " + data_split.at(1));
            }
        }
    }
    server_receive.clear_received_data();
}

void print_all_ecs_entity(ECS& ecs)
{
    std::cout << "--- ECS ---" << std::endl;
    for (auto& entity : ecs.getEntities()) {
        std::cout << "Entity: " << entity << std::endl;
        if (ecs.hasComponent<Position>(entity)) {
            std::cout << "Position: " << ecs.getComponent<Position>(entity)->x << " " << ecs.getComponent<Position>(entity)->y << std::endl;
        }
        if (ecs.hasComponent<Rotation>(entity)) {
            std::cout << "Rotation: " << ecs.getComponent<Rotation>(entity)->angle << std::endl;
        }
        if (ecs.hasComponent<Velocity>(entity)) {
            std::cout << "Velocity: " << ecs.getComponent<Velocity>(entity)->x << " " << ecs.getComponent<Velocity>(entity)->y << " " << ecs.getComponent<Velocity>(entity)->magnitude << std::endl;
        }
        if (ecs.hasComponent<Health>(entity)) {
            std::cout << "Health: " << ecs.getComponent<Health>(entity)->hp << std::endl;
        }
        if (ecs.hasComponent<Player>(entity)) {
            std::cout << "Player: " << ecs.getComponent<Player>(entity)->id << " " << ecs.getComponent<Player>(entity)->name << std::endl;
        }
        if (ecs.hasComponent<Sprite>(entity)) {
            std::cout << "Sprite: " << ecs.getComponent<Sprite>(entity)->texture << " " << ecs.getComponent<Sprite>(entity)->width << " " << ecs.getComponent<Sprite>(entity)->height << " " << ecs.getComponent<Sprite>(entity)->scale << std::endl;
        }

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
