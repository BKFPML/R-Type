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
        static void loadLevel(const std::string& levelConfig, ECS& ecs);
        static std::unordered_map<std::string, std::function<void(ECS::Entity, const std::unordered_map<std::string, std::string>&, ECS&)>> componentFactories;
};
