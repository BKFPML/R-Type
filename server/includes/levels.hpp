/**
 * @file levels.hpp
 * @brief 
 * @date 08-01-2024
 */

#pragma once

#include "../../engine/includes/ECS.hpp"
#include "../../engine/includes/components.hpp"
#include "parser.hpp"
#include <fstream>
#include <functional>
#include <unordered_map>

class Levels {
    public:
        static std::shared_ptr<ECS> loadLevel(const std::string& levelConfig, std::shared_ptr<ECS> ecs);
        static std::unordered_map<std::string, std::function<void(ECS::Entity, const std::unordered_map<std::string, std::string>&, std::shared_ptr<ECS>&)>> componentFactories;

        std::vector<ECS::Entity> temp;
};