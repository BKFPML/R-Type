/**
 * @file levels.cpp
 * @brief 
 * @date 08-01-2024
 */

#include "levels.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

/**
 * @brief Create a Player Component object
 * 
 * @param entity 
 * @param params 
 * @param ecs 
 */
void createPlayerComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, std::shared_ptr<ECS>& ecs) {
    int id = std::stoi(params.at("Player"));
    ecs->addComponent(entity, Player{id});
}

/**
 * @brief Create a Position Component object
 * 
 * @param entity 
 * @param params 
 * @param ecs 
 */
void createPositionComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, std::shared_ptr<ECS>& ecs) {
    if (params.find("x") != params.end() && params.find("y") != params.end()) {
        float x = std::stof(params.at("x"));
        float y = std::stof(params.at("y"));
        ecs->addComponent(entity, Position{x, y});
    } else {
        std::cerr << "Position component requires both 'X' and 'Y' parameters." << std::endl;
    }
}

/**
 * @brief Create a Sprite Component object
 * 
 * @param entity 
 * @param params 
 * @param ecs 
 */
void createSpriteComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, std::shared_ptr<ECS>& ecs) {
    if (params.find("texture") != params.end() && params.find("width") != params.end() && params.find("height") != params.end(), params.find("scale") != params.end()) {
        std::string texture = params.at("texture");
        int width = std::stoi(params.at("width"));
        int height = std::stoi(params.at("height"));
        float scale = std::stof(params.at("scale"));
        ecs->addComponent(entity, Sprite{texture, width, height, scale});
    } else {
        std::cerr << "Sprite component requires 'Texture', 'Width' and 'Height' parameters." << std::endl;
    }
}


/**
 * @brief Create a Velocity Component object
 * 
 * @param entity 
 * @param params 
 * @param ecs 
 */
void createVelocityComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, std::shared_ptr<ECS>& ecs) {
    float x = std::stof(params.at("x"));
    float y = std::stof(params.at("y"));
    float speed = std::stof(params.at("speed"));
    ecs->addComponent(entity, Velocity{x, y, speed});
}

/**
 * @brief Create a Rotation Component object
 * 
 * @param entity 
 * @param params 
 * @param ecs 
 */
void createRotationComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, std::shared_ptr<ECS>& ecs) {
    float angle = std::stof(params.at("Rotation"));
    ecs->addComponent(entity, Rotation{angle});
}

/**
 * @brief Create a Health Component object
 * 
 * @param entity 
 * @param params 
 * @param ecs 
 */
void createHealthComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, std::shared_ptr<ECS>& ecs) {
    int hp = std::stoi(params.at("Health"));
    ecs->addComponent(entity, Health{hp});
}

/**
 * @brief Create a Npc Component object
 * 
 * @param entity 
 * @param params 
 * @param ecs 
 */
void createNpcComponent(ECS::Entity entity, const std::unordered_map<std::string, std::string>& params, std::shared_ptr<ECS>& ecs) {
    //TODO
    std::cout << "NPC creation component" << std::endl;
}

/**
 * @brief Loads a JSON file
 * 
 * @param filename 
 * @return nlohmann::json 
 */
nlohmann::json loadJsonData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    nlohmann::json jsonArray;
    file >> jsonArray;
    return jsonArray;
}

/**
 * @brief Processes a JSON object and creates the corresponding entity and components
 * 
 * @param jsonObj 
 * @param ecs 
 * @return std::shared_ptr<ECS> 
 */
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

/**
 * @brief Loads a level from a JSON file
 * 
 * @param levelConfig 
 * @param ecs 
 * @return std::shared_ptr<ECS> 
 */
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

/**
 * @brief Component factories
 * 
 * @note This is a map of component types to functions that create the component
 */
std::unordered_map<std::string, std::function<void(ECS::Entity, const std::unordered_map<std::string, std::string>&, std::shared_ptr<ECS>&)>> Levels::componentFactories = {
    {"Player", createPlayerComponent},
    {"Position", createPositionComponent},
    {"Velocity", createVelocityComponent},
    {"Rotation", createRotationComponent},
    {"Health", createHealthComponent},
    {"Npc", createNpcComponent},
    {"Sprite", createSpriteComponent}
};
