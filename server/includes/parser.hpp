/**
 * @file parser.hpp
 * @brief Header file for parser
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

/**
 * @brief Parser class
 *
 * This class is used to parse the message received from the client
 */
class Parser {
public:
    Parser();
    std::unordered_map<std::string, std::string> parseMessage(const std::string& message);
    std::string getPrimValue(const std::unordered_map<std::string, std::string>& data, const std::string& key);
    std::string getNestValue(const std::unordered_map<std::string, std::string>& data, const std::string& key, const std::string& nestKey);
};
