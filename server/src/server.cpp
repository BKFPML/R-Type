/**
 * @file server.cpp
 * @brief Main file for the server
 * @date 2023-11-29
 */

#include "../includes/server.hpp"
#include "../includes/levels.hpp"


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
        if (data_split.at(1) == "bullet") {
            std::cout << "new bullet" << std::endl;
            _ecs.createEntity();
            _ecs.addComponent<Bullet>(_ecs.getEntities().back(), {_ecs.getEntities().back() , ALLY});
            _ecs.addComponent<Position>(_ecs.getEntities().back(), {std::stof(data_split.at(2)), std::stof(data_split.at(3))});
            _ecs.addComponent<Velocity>(_ecs.getEntities().back(), {std::stof(data_split.at(4)), std::stof(data_split.at(5))});
            _ecs.addComponent<Sprite>(_ecs.getEntities().back(), {data_split.at(6), std::stoi(data_split.at(7)), std::stoi(data_split.at(8)), std::stoi(data_split.at(9)), std::stoi(data_split.at(10)), std::stof(data_split.at(11))});

        }
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
        if (split(data, " ").front() == "new")
            init_entity(data);
        else if (split(data, " ").front() == "delete")
            delete_entity(data);
        else if (split(data, " ").front() == "start") {
            std::vector<std::string> data_split = split(data, " ");
            for (auto& client : clients_send) {
                client.send("start " + data_split.at(1));
            }
        } else {
            std::unordered_map<std::string, std::string> data_parsed = parser.parseMessage(data);
            int id_player = std::stoi(parser.getNestValue(data_parsed, "Player", "id"));
            for (int i = 0; i < clients_send_id.size(); i++) {
                if (clients_send_id.at(i) != id_player) {
                    clients_send.at(i).send(data);
                }
            }
            for (auto& entity : _ecs.getEntities()) {
                if (_ecs.hasComponent<Player>(entity)) {
                    if (_ecs.getComponent<Player>(entity)->id == id_player) {
                        _ecs.getComponent<Position>(entity)->x = std::stoi(parser.getNestValue(data_parsed, "Position", "x"));
                        _ecs.getComponent<Position>(entity)->y = std::stoi(parser.getNestValue(data_parsed, "Position", "y"));
                    }
                }
            }
        }

    }
    server_receive.clear_received_data();
}

/**
 * @brief Print all ECS entity (temporary function)
 *
 * @param ecs
 */
void print_all_ecs_entity(ECS& ecs)
{
    std::cout << "--- ECS ---" << std::endl;
    for (auto& entity : ecs.getEntities()) {
        std::cout << "Entity: " << entity << std::endl;
        if (ecs.hasComponent<Bullet>(entity)) {
            std::cout << "Bullet: " << ecs.getComponent<Bullet>(entity)->id << " " << ecs.getComponent<Bullet>(entity)->team << std::endl;
        }
        if (ecs.hasComponent<Position>(entity)) {
            std::cout << "Position: " << ecs.getComponent<Position>(entity)->x << " " << ecs.getComponent<Position>(entity)->y << std::endl;
        }
        if (ecs.hasComponent<Rotation>(entity)) {
            std::cout << "Rotation: " << ecs.getComponent<Rotation>(entity)->angle << std::endl;
        }
        if (ecs.hasComponent<Velocity>(entity)) {
            std::cout << "Velocity: " << ecs.getComponent<Velocity>(entity)->x << " " << ecs.getComponent<Velocity>(entity)->y << std::endl;
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
        if (ecs.hasComponent<Enemy>(entity)) {
            std::cout << "Enemy: " << ecs.getComponent<Enemy>(entity)->name << std::endl;
        }
        if (ecs.hasComponent<SpawnTime>(entity)) {
            std::cout << "SpawnTime: " << ecs.getComponent<SpawnTime>(entity)->time << std::endl;
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
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - now).count() > 50) {
            now = std::chrono::system_clock::now();
            // print_all_ecs_entity(_ecs);
            _ecs.updateSystems();
            for (auto& client : clients_send) {
                for (auto& entity : _ecs.getEntities()) {
                    if (_ecs.hasComponent<Bullet>(entity)) {
                        if (_ecs.getComponent<Position>(entity)->x < -50 || _ecs.getComponent<Position>(entity)->x > 2050 || _ecs.getComponent<Position>(entity)->y < -50 || _ecs.getComponent<Position>(entity)->y > 1250) {
                            for (auto& client : clients_send)
                                client.send("delete bullet " + std::to_string(_ecs.getComponent<Bullet>(entity)->id));
                            _ecs.removeEntity(entity);
                        } else {
                            for (auto& client : clients_send)
                                client.send(parser.bulletToJson(_ecs, _ecs.getComponent<Bullet>(entity)->id));
                        }
                    }
                }
            }
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
