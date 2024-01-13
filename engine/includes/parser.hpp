/**
 * @file parser.hpp
 * @brief 
 * @date 26-12-2023
 */

// message example:x:0-y:10-hp:40-ip:127.0.0.1:13151

#pragma once

// #include <string>
// #include <sstream>
// #include <vector>
// #include <unordered_map>

// /**
//  * @brief Parser class
//  * This class is used to parse the message received from the client
//  * 
//  */
// class Parser {
//     public:

//         /**
//          * @brief Construct a new Parser object
//          * 
//          */
//         Parser();

//         /**
//          * @brief Main function of the parser
//          * 
//          */
//         std::unordered_map<std::string, std::string> parseMessage(const std::string& message);

//     private:
//         /**
//          * @brief Extract the key from a pair
//          * 
//          * @param pair 
//          * @return std::string 
//          */
//         std::string extractKey(const std::string& pair);

//         /**
//          * @brief Extract the value from a pair
//          * 
//          * @param pair 
//          * @return std::string 
//          */
//         std::string extractValue(const std::string& pair);
// };

#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include "ECS.hpp"
#include <iostream>

using json = nlohmann::json;

/**
 * @brief Parser class
 * 
 * This class is used to parse the message received from the client
 * 
 */
class Parser {
public:

    Parser() {}
    /**
     * @brief Main function of the parser for single messages
     * 
     * @param message 
     * @return std::unordered_map<std::string, std::string> 
     */
    std::unordered_map<std::string, std::string> parseMessage(const std::string& message) {
        std::unordered_map<std::string, std::string> parsedMessage;
        auto j = json::parse(message);

        for (auto& element : j) {
            for (auto& innerElement : element.items()) {
                if (innerElement.value().is_primitive()) {
                    parsedMessage[innerElement.key()] = innerElement.value().get<std::string>();
                } else {
                    // For nested objects
                    parsedMessage[innerElement.key()] = innerElement.value().dump();
                }
            }
        }
        return parsedMessage;
    }

    /**
     * @brief Extract value from a primitive pair
     * 
     * @param data 
     * @param key 
     * @return std::string 
     */
    std::string getPrimValue(const std::unordered_map<std::string, std::string>& data, const std::string& key) {
        auto it = data.find(key);
        if (it != data.end()) {
            std::cout << "Found primitive value for key " << key << ": " << it->second << std::endl;
            return it->second;
        }
        std::cerr << "Key not found for primitive value: " << key << std::endl;
        return "";
    }

    /**
     * @brief Extract value from a nested pair
     * 
     * @param data 
     * @param key 
     * @param nestKey 
     * @return std::string 
     */
    std::string getNestValue(const std::unordered_map<std::string, std::string>& data, const std::string key, const std::string nestKey) {
        auto it = data.find(key);
        if (it != data.end()) {
            try {
                auto nestedObj = json::parse(it->second);
                std::string nestedValue = nestedObj[nestKey].get<std::string>();
                std::cout << "Found nested value for key " << nestKey << ": " << nestedValue << std::endl;
                return nestedValue;
            } catch (json::parse_error& e) {
                std::cerr << "Parse error: " << e.what() << std::endl;
            }
        }
        std::cerr << "Key not found for nested value: " << key << std::endl;
        return "";
    }

    std::string ecsToJson(ECS& ecs)
    {
        json allEntitiesJson;

        for (auto& entity : ecs.getEntities()) {
            json entityJson;

            // Example for a Position component
            if (ecs.hasComponent<Position>(entity)) {
                Position* position = ecs.getComponent<Position>(entity);
                entityJson["Position"] = {{"x", std::to_string(position->x)}, {"y", std::to_string(position->y)}};
            }

            if (ecs.hasComponent<Player>(entity)) {
                Player* player = ecs.getComponent<Player>(entity);
                entityJson["Player"] = {{"id", std::to_string(player->id)}, {"name", player->name}};
            }

            allEntitiesJson.push_back(entityJson);
        }

        return allEntitiesJson.dump();
    }

    std::string playerToJson(ECS& ecs, int id)
    {
        json allEntitiesJson;

        for (auto& entity : ecs.getEntities()) {
            if (ecs.hasComponent<Player>(entity)) {
                Player* player = ecs.getComponent<Player>(entity);
                Position* position = ecs.getComponent<Position>(entity);
                if (player->id == id) {
                    json entityJson;
                    entityJson["Player"] = {{"id", std::to_string(player->id)}, {"name", player->name}};
                    entityJson["Position"] = {{"x", std::to_string(position->x)}, {"y", std::to_string(position->y)}};
                    allEntitiesJson.push_back(entityJson);
                }
            }
        }

        return allEntitiesJson.dump();
    }
};
