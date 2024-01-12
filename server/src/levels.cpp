/**
 * @file levels.cpp
 * @brief 
 * @date 08-01-2024
 */

#include "levels.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

void createPlayerComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, ECS& ecs) {
    //TODO
    std::cout << "Player creation component" << std::endl;
}

// void createPositionComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, ECS& ecs) {
//     float x = std::stof(params.at("x"));
//     float y = std::stof(params.at("y"));
//     ecs.registerComponent<Position>();
//     ecs.addComponent(entity, Position{x, y});
// }

void createPositionComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, ECS& ecs) {
    // Check if both "X" and "Y" keys are present in the params
    if (params.find("X") != params.end() && params.find("Y") != params.end()) {
        float x = std::stof(params.at("X"));
        float y = std::stof(params.at("Y"));
        std::cout << "X: " << x << ", Y: " << y << std::endl;
        ecs.registerComponent<Position>();
        ecs.addComponent(entity, Position{x, y});
    } else {
        std::cerr << "Position component requires both 'X' and 'Y' parameters." << std::endl;
    }
}

void createVelocityComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, ECS& ecs) {
    float x = std::stof(params.at("x"));
    float y = std::stof(params.at("y"));
    float speed = std::stof(params.at("speed"));
    ecs.addComponent(entity, Velocity{x, y, speed});
}

void createRotationComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, ECS& ecs) {
    float angle = std::stof(params.at("Rotation"));
    std::cout << "Rotation: " << angle << std::endl;
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

// void Levels::loadLevel(const std::string& levelConfig, ECS& ecs) {
//     std::ifstream file(levelConfig);
//     if (!file.is_open()) {
//         std::cerr << "Failed to open file: " << levelConfig << std::endl;
//         return;
//     }
    
//     json jsonArray;
//     file >> jsonArray;

//     std::cout << "Loaded JSON Data: " << jsonArray.dump(4) << std::endl; // Print entire JSON data

//     for (auto& jsonObj : jsonArray) {
//         auto entity = ecs.createEntity();
//         std::cout << "Entity created with ID: " << entity << std::endl;

//         for (auto& element : jsonObj.items()) {
//             auto componentType = element.key();
//             auto componentData = element.value();
//             std::cout << "Processing Component: " << componentType << std::endl;
//             std::cout << "Component Data: " << componentData.dump(4) << std::endl;
//             std::cout << "Component Data Type: " << componentData.type_name() << std::endl;

//             if (Levels::componentFactories.find(componentType) != Levels::componentFactories.end()) {
//                 std::cout << "Invoking factory for Component Type: " << componentType << std::endl;

//                 if (componentData.is_primitive()) {
//                     // std::cout << "Primitive Component Parameter: " << componentData.get<int>() << std::endl;
//                     std::unordered_map<std::string, std::string> params = {{componentType, componentData.get<std::string>()}};
//                     std::cout << "Primitive Component Parameters: " << componentData.get<std::string>() << std::endl;
//                     Levels::componentFactories[componentType](entity, params, ecs);
//                 } else {
//                     std::unordered_map<std::string, std::string> nestedParams;
//                     for (auto& nestedElement : componentData.items()) {
//                         nestedParams[nestedElement.key()] = nestedElement.value().get<std::string>();
//                         std::cout << "Nested Component Parameter: " << nestedElement.key() << ": " << nestedElement.value() << std::endl;
//                     }
//                     std::cout << "Nested Component Parameters: " << componentData.dump(4) << std::endl;
//                     Levels::componentFactories[componentType](entity, nestedParams, ecs);
//                 }
//             } else {
//                 std::cout << "No factory found for Component Type: " << componentType << std::endl;
//             }
//         }
//     }
//     std::cout << "Level loading completed." << std::endl;
// }

// Function to load JSON data from file
nlohmann::json loadJsonData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    nlohmann::json jsonArray;
    file >> jsonArray;
    std::cout << "Loaded JSON Data: " << jsonArray.dump(4) << std::endl; // Print entire JSON data
    return jsonArray;
}

// Function to process each JSON object and create components
void processJsonObject(const nlohmann::json& jsonObj, ECS& ecs) {
    auto entity = ecs.createEntity();
    std::cout << "Entity created with ID: " << entity << std::endl;
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
}

// Original loadLevel function, now refactored
void Levels::loadLevel(const std::string& levelConfig, ECS& ecs) {
    try {
        auto jsonArray = loadJsonData(levelConfig);
        for (const auto& jsonObj : jsonArray) {
            processJsonObject(jsonObj, ecs);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading level: " << e.what() << std::endl;
    }
    std::cout << "Level loading completed." << std::endl;
    std::cout << "Entities: " << std::endl;
    std::vector<ECS::Entity> entities = ecs.getEntities();

    if (entities.empty()) {
        std::cout << "No entities found." << std::endl;
    } else {
        std::cout << "Number of entities: " << entities.size() << std::endl;
    }
    for (auto& entity : entities) {
        std::cout << "Entity: " << entity << std::endl;
        if (ecs.hasComponent<Health>(entity)) {
            std::cout << "Health: " << ecs.getComponent<Health>(entity)->hp << std::endl;
        }
        if (ecs.hasComponent<Rotation>(entity)) {
            std::cout << "Rotation: " << ecs.getComponent<Rotation>(entity)->angle << std::endl;
        }
        if (ecs.hasComponent<Position>(entity)) {
            std::cout << "Position: " << ecs.getComponent<Position>(entity)->x << ", " << ecs.getComponent<Position>(entity)->y << std::endl;
        }
    }
}

std::unordered_map<std::string, std::function<void(ECS::Entity, const std::unordered_map<std::string, std::string>&, ECS&)>> Levels::componentFactories = {
    {"Player", createPlayerComponent},
    {"Position", createPositionComponent},
    {"Velocity", createVelocityComponent},
    {"Rotation", createRotationComponent},
    {"Health", createHealthComponent},
    {"Npc", createNpcComponent}
};
