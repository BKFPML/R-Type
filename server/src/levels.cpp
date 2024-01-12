/**
 * @file levels.cpp
 * @brief 
 * @date 08-01-2024
 */

#include "levels.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

void createPlayerComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, std::shared_ptr<ECS>& ecs) {
    //TODO
    std::cout << "Player creation component" << std::endl;
}

void createPositionComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, std::shared_ptr<ECS>& ecs) {
    if (params.find("X") != params.end() && params.find("Y") != params.end()) {
        float x = std::stof(params.at("X"));
        float y = std::stof(params.at("Y"));
        ecs->addComponent(entity, Position{x, y});
    } else {
        std::cerr << "Position component requires both 'X' and 'Y' parameters." << std::endl;
    }
}

void createVelocityComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, std::shared_ptr<ECS>& ecs) {
    float x = std::stof(params.at("x"));
    float y = std::stof(params.at("y"));
    float speed = std::stof(params.at("speed"));
    ecs->addComponent(entity, Velocity{x, y, speed});
}

void createRotationComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, std::shared_ptr<ECS>& ecs) {
    float angle = std::stof(params.at("Rotation"));
    ecs->addComponent(entity, Rotation{angle});
}

void createHealthComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, std::shared_ptr<ECS>& ecs) {
    int hp = std::stoi(params.at("Health"));
    ecs->addComponent(entity, Health{hp});
}

void createNpcComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, std::shared_ptr<ECS>& ecs) {
    //TODO
    std::cout << "NPC creation component" << std::endl;
}

// Function to load JSON data from file
nlohmann::json loadJsonData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    nlohmann::json jsonArray;
    file >> jsonArray;
    return jsonArray;
}

// Function to process each JSON object and create components
std::shared_ptr<ECS> processJsonObject(const nlohmann::json& jsonObj, std::shared_ptr<ECS> ecs) {
    auto entity = ecs->createEntity();
    for (const auto& element : jsonObj.items()) {
        const auto& componentType = element.key();
        const auto& componentData = element.value();
        if (Levels::componentFactories.find(componentType) != Levels::componentFactories.end()) {
            std::unordered_map<std::string, std::string> params;
            if (componentData.is_primitive()) {
                params[componentType] = componentData.get<std::string>();
            } else {
                for (const auto& nestedElement : componentData.items()) {
                    params[nestedElement.key()] = nestedElement.value().get<std::string>();
                }
            }
            Levels::componentFactories[componentType](entity, params, ecs);
        }
    }
    return (ecs);
}

// Original loadLevel function, now refactored
std::shared_ptr<ECS> Levels::loadLevel(const std::string& levelConfig, std::shared_ptr<ECS> ecs) {
    try {
        auto jsonArray = loadJsonData(levelConfig);
        for (const auto& jsonObj : jsonArray) {
            ecs = processJsonObject(jsonObj, ecs);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading level: " << e.what() << std::endl;
    }
    return (ecs);
}

std::unordered_map<std::string, std::function<void(ECS::Entity, const std::unordered_map<std::string, std::string>&, std::shared_ptr<ECS>&)>> Levels::componentFactories = {
    {"Player", createPlayerComponent},
    {"Position", createPositionComponent},
    {"Velocity", createVelocityComponent},
    {"Rotation", createRotationComponent},
    {"Health", createHealthComponent},
    {"Npc", createNpcComponent}
};
