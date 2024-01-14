/**
 * @file init_entity.cpp
 * @brief Delcaration of the init_entity class methods
 * @date 12-01-2024
 */

#include "server.hpp"

/**
 * @brief function to find a free id for a player
 */
int Server::find_free_id_player()
{
    int id = 0;
    for (auto& entity : _ecs.getEntities()) {
        if (_ecs.hasComponent<Player>(entity)) {
            if (_ecs.getComponent<Player>(entity)->id == id) {
                id++;
            }
        }
    }
    return id;
}

/**
 * @brief function to init a player
 *
 * @param data
 */
void Server::init_player(std::vector<std::string> data_split)
{
    if (data_split.at(1) == "player") {
        std::cout << "Set port to: " << data_split.back() << std::endl;
        int id_new_player = find_free_id_player();
        for (auto& client : clients_send) {
            client.send("new player " + std::to_string(id_new_player) + " " + data_split.at(2));
        }

        std::string ip = data_split.back();
        clients_send.push_back(UDPBoostNetwork::UDPSender(std::stoi(split(ip, ":").back()), split(ip, ":").front()));
        clients_send_id.push_back(id_new_player);
        clients_send.back().send("new player " + std::to_string(id_new_player) + " " + data_split.at(2) + " you");
        for (auto& entity : _ecs.getEntities()) {
            if (_ecs.hasComponent<Player>(entity)) {
                clients_send.back().send("new player " + std::to_string(_ecs.getComponent<Player>(entity)->id) + " " + _ecs.getComponent<Player>(entity)->name);
            }
        }

        _ecs.createEntity();
        _ecs.addComponent<Position>(_ecs.getEntities().back(), Position(300, 300 + clients_send.size() * 100));
        _ecs.addComponent<Rotation>(_ecs.getEntities().back(), Rotation(180));
        _ecs.addComponent<Velocity>(_ecs.getEntities().back(), Velocity(0, 0));
        _ecs.addComponent<Health>(_ecs.getEntities().back(), Health(100));
        _ecs.addComponent<Player>(_ecs.getEntities().back(), Player(id_new_player, data_split.at(2)));
        _ecs.addComponent<Sprite>(_ecs.getEntities().back(), Sprite("player_red", 32, 16, 64, 0, 5));
    }
}
