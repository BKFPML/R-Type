/**
 * @file levels.cpp
 * @brief 
 * @date 08-01-2024
 */

#include "levels.hpp"
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

void createPlayerComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, ECS& ecs) {
    //TODO
    std::cout << "Player creation component" << std::endl;
}

void createPositionComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, ECS& ecs) {
    float x = std::stof(params.at("x"));
    float y = std::stof(params.at("y"));
    ecs.registerComponent<Position>();
    ecs.addComponent(entity, Position{x, y});
}

void createVelocityComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, ECS& ecs) {
    float x = std::stof(params.at("x"));
    float y = std::stof(params.at("y"));
    float speed = std::stof(params.at("speed"));
    ecs.addComponent(entity, Velocity{x, y, speed});
}

void createRotationComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, ECS& ecs) {
    float angle = std::stof(params.at("Rotation"));
    ecs.registerComponent<Rotation>();
    ecs.addComponent(entity, Rotation{angle});
}

void createHealthComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, ECS& ecs) {
    std::cout << "Health creation component" << std::endl;
    std::cout << "Health: " << params.at("Health") << std::endl;
    int hp = std::stoi(params.at("Health"));
    ecs.registerComponent<Health>();
    ecs.addComponent(entity, Health{hp});
}

void createNpcComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, ECS& ecs) {
    //TODO
    std::cout << "NPC creation component" << std::endl;
}

void Levels::loadLevel(const std::string& levelConfig, ECS& ecs) {
    std::ifstream file(levelConfig);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << levelConfig << std::endl;
        return;
    }
    
    json jsonArray;
    file >> jsonArray;

    std::cout << "Loaded JSON Data: " << jsonArray.dump(4) << std::endl; // Print entire JSON data

    for (auto& jsonObj : jsonArray) {
        auto entity = ecs.createEntity();
        std::cout << "Entity created with ID: " << entity << std::endl;

        for (auto& element : jsonObj.items()) {
            auto componentType = element.key();
            auto componentData = element.value();
            std::cout << "Processing Component: " << componentType << std::endl;
            std::cout << "Component Data: " << componentData.dump(4) << std::endl;
            std::cout << "Component Data Type: " << componentData.type_name() << std::endl;

            if (Levels::componentFactories.find(componentType) != Levels::componentFactories.end()) {
                std::cout << "Invoking factory for Component Type: " << componentType << std::endl;

                if (componentData.is_primitive()) {
                    // std::cout << "Primitive Component Parameter: " << componentData.get<int>() << std::endl;
                    std::unordered_map<std::string, std::string> params = {{componentType, componentData.get<std::string>()}};
                    std::cout << "Primitive Component Parameters: " << componentData.get<std::string>() << std::endl;
                    Levels::componentFactories[componentType](entity, params, ecs);
                } else {
                    std::unordered_map<std::string, std::string> nestedParams;
                    for (auto& nestedElement : componentData.items()) {
                        nestedParams[nestedElement.key()] = nestedElement.value().get<std::string>();
                        std::cout << "Nested Component Parameter - " << nestedElement.key() << ": " << nestedElement.value() << std::endl;
                    }
                    Levels::componentFactories[componentType](entity, nestedParams, ecs);
                }
            } else {
                std::cout << "No factory found for Component Type: " << componentType << std::endl;
            }
        }
    }
    std::cout << "Level loading completed." << std::endl;
}


std::unordered_map<std::string, std::function<void(ECS::Entity, const std::unordered_map<std::string, std::string>&, ECS&)>> Levels::componentFactories = {
    {"Player", createPlayerComponent},
    {"Position", createPositionComponent},
    {"Velocity", createVelocityComponent},
    {"Rotation", createRotationComponent},
    {"Health", createHealthComponent},
    {"Npc", createNpcComponent}
};
