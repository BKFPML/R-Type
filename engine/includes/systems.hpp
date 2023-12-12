/**
 * @file systems.hpp
 * @brief Decleration of the systems
 * @date 12-12-2023
 */

#pragma once

#include "ECS.hpp"

class ISystem {
    public:
        virtual void update(ECS& ecs) = 0;
};

class MovementSystem : public ISystem {
    public:
        void update(ECS& ecs) override
        {
            for (auto entity: ecs.getEntities()) {
                if ((ecs.hasComponent<Position>(entity)) && (ecs.hasComponent<Velocity>(entity))) {
                }
            }
        }
};