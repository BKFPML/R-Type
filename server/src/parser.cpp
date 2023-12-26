/**
 * @file parser.cpp
 * @brief 
 * @date 26-12-2023
 */

#include "../includes/parser.hpp"

/**
 * @brief Construct a new Parser object
 * 
 */
Parser::Parser()
{
}

/**
 * @brief Main function of the parser
 * 
 */
std::unordered_map<std::string, std::string> Parser::parseMessage(const std::string& message) {
    std::unordered_map<std::string, std::string> parsedMessage;
    std::stringstream ss(message);
    std::string item;

    while (std::getline(ss, item, '-')) {
        std::string key = extractKey(item);
        std::string value = extractValue(item);
        parsedMessage[key] = value;
    }

    return parsedMessage;
}

/**
 * @brief Extract the key from a pair
 * 
 * @param pair 
 * @return std::string 
 */
std::string Parser::extractKey(const std::string& pair) {
    size_t pos = pair.find(':');
    return pair.substr(0, pos);
}

/**
 * @brief Extract the value from a pair
 * 
 * @param pair 
 * @return std::string 
 */
std::string Parser::extractValue(const std::string& pair) {
    size_t pos = pair.find(':');
    return pair.substr(pos + 1);
}