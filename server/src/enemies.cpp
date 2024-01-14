/**
 * @file enemies.cpp
 * @brief Functions related to enemies
 * @date 14-01-2024
 */

#include "server.hpp"
#include "enemies.hpp"

void Server::init_enemies()
{
    std::cout << "Init enemies" << std::endl;
    _enemies = _ecs.getEnemies();
    std::map<std::string, Attributes> enemyTypes = createEnemyTypes();
    for (auto& enemy : _enemies) {
        std::string enemyType = _ecs.getComponent<Enemy>(enemy)->name;
        std::cout << "enemyType: " << enemyType << std::endl;
        _ecs.addComponent<Health>(enemy, {enemyTypes[enemyType].health});
        _ecs.addComponent<Rotation>(enemy, {enemyTypes[enemyType].rotation});
        _ecs.addComponent<Sprite>(enemy, {enemyTypes[enemyType].texture, enemyTypes[enemyType].width, enemyTypes[enemyType].height, enemyTypes[enemyType].startX, enemyTypes[enemyType].startY, enemyTypes[enemyType].scale});
        _ecs.addComponent<Velocity>(enemy, {0 - enemyTypes[enemyType].speed, 0});
    }
}
