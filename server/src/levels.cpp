/**
 * @file levels.cpp
 * @brief 
 * @date 08-01-2024
 */

#include "levels.hpp"
#include <iostream>

void createPlayerComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, ECS& ecs) {
    //TODO
    std::cout << "Player creation component" << std::endl;
}

void createPositionComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, ECS& ecs) {
    float x = std::stof(params.at("x"));
    float y = std::stof(params.at("y"));
    std::cout << "Position: " << x << ", " << y << std::endl;
    ecs.addComponent(entity, Position{x, y});
}

void createVelocityComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, ECS& ecs) {
    float x = std::stof(params.at("x"));
    float y = std::stof(params.at("y"));
    float speed = std::stof(params.at("speed"));
    ecs.addComponent(entity, Velocity{x, y, speed});
}

void createRotationComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, ECS& ecs) {
    float angle = std::stof(params.at("angle"));
    ecs.addComponent(entity, Rotation{angle});
}

void createHealthComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, ECS& ecs) {
    int health = std::stoi(params.at("health"));
    ecs.addComponent(entity, Health{health});
}

void createNpcComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, ECS& ecs) {
    //TODO
    std::cout << "NPC creation component" << std::endl;
}

void Levels::loadLevel(const std::string& levelConfig, ECS& ecs) {
    std::ifstream file(levelConfig);
    std::string line;
    Parser parser;

    while (std::getline(file, line)) {
        auto parsedLine = parser.parseMessage(line);
        auto entity = ecs.createEntity();

        for (auto& component : parsedLine) {
            if (Levels::componentFactories.find(component.first) != Levels::componentFactories.end()) {
                Levels::componentFactories[component.first](entity, parsedLine, ecs);
            }
        }
    }
    std::cout << "Level loaded" << std::endl;
}

std::unordered_map<std::string, std::function<void(ECS::Entity, const std::unordered_map<std::string, std::string>&, ECS&)>> Levels::componentFactories = {
    {"player", createPlayerComponent},
    {"position", createPositionComponent},
    {"velocity", createVelocityComponent},
    {"rotation", createRotationComponent},
    {"health", createHealthComponent},
    {"npc", createNpcComponent}
};
