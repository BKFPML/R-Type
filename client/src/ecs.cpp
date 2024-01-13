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
    return ecs;
}

/**
 * @brief Initialises the player and add it to the ECS
 *
 */
void rtype::Client::initPlayer()
{
    _players.push_back(_ecs.createEntity());
    _ecs.addComponent<Position>(_players[0], {100, 100});
    _ecs.addComponent<Health>(_players[0], 100);
    _ecs.addComponent<Velocity>(_players[0], {1, 1, 2});
    std::string texture = "r_typesheet42";
    _ecs.addComponent<Sprite>(_players[0], {texture, 34, 34});
    _ecs.addComponent<Rotation>(_players[0], 180);
}
