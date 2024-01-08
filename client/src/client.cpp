/**
 * @file client.cpp
 * @brief
 * @date 04-12-2023
 */

#include "client.hpp"

/**
 * @brief Construct a new rtype::Client::Client object
 */
rtype::Client::Client() : running(true)
{
    std::cout << "This is the R-Type Client" << std::endl;
}

/**
 * @brief Destroy the rtype::Client::Client object
 */
rtype::Client::~Client()
{
    std::cout << "Goodbye" << std::endl;
}

/**
 * @brief Initialize the ECS
 *
 * @return ECS
 */
ECS rtype::Client::initECS()
{
    ECS ecs;
    ecs.registerComponent<Position>();
    ecs.registerComponent<Health>();
    ecs.registerComponent<Velocity>();
    return ecs;
}

/**
 * @brief Run the game loop
 *
 */
void rtype::Client::gameLoop()
{
    while (running) {

    }
}
