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
    ecs.registerComponent<Collision>();
    ecs.registerComponent<Enemy>();
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
 * @brief delete entity enemy
 *
*/
void rtype::Client::deleteEnemy(std::vector<std::string> data)
{
    if (data.at(1) == "enemy") {
        int enemyIdToDelete = std::stoi(data.at(2));
        for (auto& entity : _ecs.getEntities()) {
            if (_ecs.hasComponent<Enemy>(entity)) {
                if (_ecs.getComponent<Enemy>(entity)->id == enemyIdToDelete) {
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
        try {
            for (auto& entity : _ecs.getEntities()) {
                if (_ecs.hasComponent<Bullet>(entity)) {
                    if (_ecs.getComponent<Bullet>(entity)->id == std::stoi(_parser.getNestValue(json, "Bullet", "id"))) {
                        _ecs.getComponent<Position>(entity)->x = std::stoi(_parser.getNestValue(json, "Position", "x"));
                        _ecs.getComponent<Position>(entity)->y = std::stoi(_parser.getNestValue(json, "Position", "y"));
                        break;
                    }
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error bullet message: " << e.what() << std::endl;
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
    _singlePlayer = true;
    _player = _ecs.createEntity();
    _ecs.addComponent<Position>(_ecs.getEntities().back(), {100, 100});
    _ecs.addComponent<Health>(_ecs.getEntities().back(), 100);
    _ecs.addComponent<Velocity>(_ecs.getEntities().back(), {0, 0});
    _ecs.addComponent<Collision>(_ecs.getEntities().back(), {DEFEND});
    std::string texture = "player_red";
    _ecs.addComponent<Sprite>(_ecs.getEntities().back(), {texture, 34, 34, 0, 0, 3});
    _ecs.addComponent<Player>(_ecs.getEntities().back(), {0, "player"});
    _ecs.addComponent<Rotation>(_ecs.getEntities().back(), {180});

    ECS::Entity test = _ecs.createEntity();
    _ecs.addComponent<Position>(test, {100, 100});
    _ecs.addComponent<Health>(test, 100);
    _ecs.addComponent<Velocity>(test, {0, 0});
    _ecs.addComponent<Collision>(test, {DEFEND});
    std::string texture2 = "player_red";
    _ecs.addComponent<Sprite>(test, {texture2, 34, 34, 0, 0, 3});
    _ecs.addComponent<Rotation>(test, {180});
}

/**
 * @brief Initialises enemies and add them to the ECS
 *
 * @return void
 */
void rtype::Client::initEnemy(std::vector<std::string> data)
{
    if (data.at(1) == "enemy") {
        _ecs.createEntity();
        _ecs.addComponent<Enemy>(_ecs.getEntities().back(), {"enemy", size_t(std::stoi(data.at(2)))});
        _ecs.addComponent<Position>(_ecs.getEntities().back(), {std::stof(data.at(3)), std::stof(data.at(4))});
        _ecs.addComponent<Sprite>(_ecs.getEntities().back(), {data.at(5), std::stoi(data.at(6)), std::stoi(data.at(7)), std::stoi(data.at(8)), std::stoi(data.at(9)), std::stof(data.at(10))});
    }
}
/**
 * @brief Initialises the bullets
 *
 * @return void
 */
void rtype::Client::initBullet(std::vector<std::string> data_split)
{
    if (data_split.at(1) == "bullet") {
        _ecs.createEntity();
        _ecs.addComponent<Bullet>(_ecs.getEntities().back(), {size_t(std::stoi(data_split.at(2))), ALLY});
        _ecs.addComponent<Position>(_ecs.getEntities().back(), {std::stof(data_split.at(3)), std::stof(data_split.at(4))});
        _ecs.addComponent<Sprite>(_ecs.getEntities().back(), {data_split.at(5), std::stoi(data_split.at(6)), std::stoi(data_split.at(7)), std::stoi(data_split.at(8)), std::stoi(data_split.at(9)), std::stof(data_split.at(10))});
    }
}

/**
 * @brief update entity enemy
 *
 * @return void
 */
void rtype::Client::updateEnemy(std::unordered_map<std::string, std::string> json)
{
    if (json.find("Enemy") != json.end()) {
        try {
            for (auto& entity : _ecs.getEntities()) {
                if (_ecs.hasComponent<Enemy>(entity)) {
                    if (_ecs.getComponent<Enemy>(entity)->id == std::stoi(_parser.getNestValue(json, "Enemy", "id"))) {
                        _ecs.getComponent<Position>(entity)->x = std::stoi(_parser.getNestValue(json, "Position", "x"));
                        _ecs.getComponent<Position>(entity)->y = std::stoi(_parser.getNestValue(json, "Position", "y"));
                        break;
                    }
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error enemy message: " << e.what() << std::endl;
        }
    }
}