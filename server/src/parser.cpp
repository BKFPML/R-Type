/**
 * @file parser.cpp
 * @brief 
 * @date 26-12-2023
 */

#include "../includes/parser.hpp"
#include <nlohmann/json.hpp>
#include <string>
#include <iostream>

using json = nlohmann::json;

Parser::Parser() {}

/**
 * @brief Main function of the parser for single messages
 * 
 * @param message 
 * @return std::unordered_map<std::string, std::string> 
 */
std::unordered_map<std::string, std::string> Parser::parseMessage(const std::string& message) {
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
std::string Parser::getPrimValue(const std::unordered_map<std::string, std::string>& data, const std::string& key) {
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
std::string Parser::getNestValue(const std::unordered_map<std::string, std::string>& data, const std::string& key, const std::string& nestKey) {
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
