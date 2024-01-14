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
    for (auto& enemy : _enemies) {
        std::cout << "Enemy: " << _ecs.getComponent<Enemy>(enemy)->name << std::endl;
        // _ecs.addComponent<Position>(enemy, Position(0, 0));
        // _ecs.addComponent<Rotation>(enemy, Rotation(0));
        // _ecs.addComponent<Velocity>(enemy, Velocity(0, 0));
        // _ecs.addComponent<Health>(enemy, Health(100));
        // _ecs.addComponent<Enemy>(enemy, Enemy());
        // _ecs.addComponent<Sprite>(enemy, Sprite("assets/enemy.png"));
    }
}
