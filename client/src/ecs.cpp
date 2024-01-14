/**
 * @file ecs.cpp
 * @brief Implementation of the initialisation of the ECS and its entities
 * @date 09-01-2024
 */

#include "client.hpp"

/**
 * @brief Initialises the ECS
 *
 * @return ECS
 */
ECS rtype::Client::initECS()
{
    ECS ecs;
    ecs.registerComponent<Position>();
    ecs.registerComponent<Velocity>();
    ecs.registerComponent<Rotation>();
    ecs.registerComponent<Health>();
    ecs.registerComponent<Sprite>();
    ecs.registerComponent<Player>();
    ecs.registerComponent<Rotation>();
    ecs.registerComponent<Bullet>();
    return ecs;
}

/**
 * @brief Initialises the player and add it to the ECS
 *
 */
void rtype::Client::initPlayer(std::vector<std::string> data_split)
{
    if (data_split.at(1) == "player") {
        _ecs.createEntity();
        _ecs.addComponent<Position>(_ecs.getEntities().back(), {100, 100});
        _ecs.addComponent<Health>(_ecs.getEntities().back(), 100);
        _ecs.addComponent<Velocity>(_ecs.getEntities().back(), {0, 0});
        std::string texture = "player_red";
        _ecs.addComponent<Sprite>(_ecs.getEntities().back(), {texture, 34, 34, 0, 0, 3});
        _ecs.addComponent<Player>(_ecs.getEntities().back(), {stoi(data_split.at(2)), data_split.at(3)});
        _ecs.addComponent<Rotation>(_ecs.getEntities().back(), {180});
        if (data_split.size() > 4) {
            _player = _ecs.getEntities().back();
            id = stoi(data_split.at(2));
        }
    }
}

/**
 * @brief delete entity player
 *
 */
void rtype::Client::deletePlayer(std::vector<std::string> data)
{
    if (data.at(1) == "player") {
        int playerIdToDelete = std::stoi(data.at(2));
        for (auto& entity : _ecs.getEntities()) {
            if (_ecs.hasComponent<Player>(entity)) {
                if (_ecs.getComponent<Player>(entity)->id == playerIdToDelete) {
                    _ecs.removeEntity(entity);
                    break;
                }
            }
        }
    }
}

/**
 * @brief delete entity bullet
 *
 */
void rtype::Client::deleteBullet(std::vector<std::string> data)
{
    if (data.at(1) == "bullet") {
        int bulletIdToDelete = std::stoi(data.at(2));
        for (auto& entity : _ecs.getEntities()) {
            if (_ecs.hasComponent<Bullet>(entity)) {
                if (_ecs.getComponent<Bullet>(entity)->id == bulletIdToDelete) {
                    _ecs.removeEntity(entity);
                    break;
                }
            }
        }
    }
}

/**
 * @brief update entity player
 * 
 * @param data 
 */

void rtype::Client::updatePlayer(std::unordered_map<std::string, std::string>  json)
{   
    if (json.find("Player") != json.end()) {
        int id_player = std::stoi(_parser.getNestValue(json, "Player", "id"));
        for (auto& entity : _ecs.getEntities()) {
            if (_ecs.hasComponent<Player>(entity)) {
                if (_ecs.getComponent<Player>(entity)->id == id_player) {
                    _ecs.getComponent<Position>(entity)->x = std::stoi(_parser.getNestValue(json, "Position", "x"));
                    _ecs.getComponent<Position>(entity)->y = std::stoi(_parser.getNestValue(json, "Position", "y"));
                }
            }
        }
    }
}

/**
 * @brief update entity bullet
 * 
 * @param data 
 */
void rtype::Client::updateBullet(std::unordered_map<std::string, std::string> json)
{
    if (json.find("Bullet") != json.end()) {
        bool found = false;
        for (auto& entity : _ecs.getEntities()) {
            if (_ecs.hasComponent<Bullet>(entity)) {
                if (_ecs.getComponent<Bullet>(entity)->id == std::stoi(_parser.getNestValue(json, "Bullet", "id"))) {
                    found = true;
                    _ecs.getComponent<Position>(entity)->x = std::stoi(_parser.getNestValue(json, "Position", "x"));
                    _ecs.getComponent<Position>(entity)->y = std::stoi(_parser.getNestValue(json, "Position", "y"));

                }
            }
        }
        if (!found) {
            _ecs.createEntity();
            _ecs.addComponent<Position>(_ecs.getEntities().back(), {std::stof(_parser.getNestValue(json, "Position", "x")), std::stof(_parser.getNestValue(json, "Position", "y"))});
            _ecs.addComponent<Bullet>(_ecs.getEntities().back(), {std::size_t(std::stoi(_parser.getNestValue(json, "Bullet", "id"))), ALLY});
            _ecs.addComponent<Sprite>(_ecs.getEntities().back(), {_parser.getNestValue(json, "Sprite", "texture"), std::stoi(_parser.getNestValue(json, "Sprite", "width")), std::stoi(_parser.getNestValue(json, "Sprite", "height")), std::stoi(_parser.getNestValue(json, "Sprite", "startX")), std::stoi(_parser.getNestValue(json, "Sprite", "startY")), std::stof(_parser.getNestValue(json, "Sprite", "scale"))});
        }

    }
}


/**
 * @brief nb of players
 *
 */
int rtype::Client::nbPlayersInRoom()
{
    int nb = 0;
    for (auto& entity : _ecs.getEntities()) {
        if (_ecs.hasComponent<Player>(entity)) {
            nb++;
        }
    }
    return nb;
}

void rtype::Client::launchSinglePlayer()
{
    _player = _ecs.createEntity();
    _ecs.addComponent<Position>(_ecs.getEntities().back(), {100, 100});
    _ecs.addComponent<Health>(_ecs.getEntities().back(), 100);
    _ecs.addComponent<Velocity>(_ecs.getEntities().back(), {0, 0});
    std::string texture = "player_red";
    _ecs.addComponent<Sprite>(_ecs.getEntities().back(), {texture, 34, 34, 0, 0, 3});
    _ecs.addComponent<Player>(_ecs.getEntities().back(), {0, "player"});
    _ecs.addComponent<Rotation>(_ecs.getEntities().back(), {180});
    _singlePlayer = true;
}
