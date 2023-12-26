/**
 * @file server.cpp
 * @brief Main file for the server
 * @date 2023-11-29
 */

// #include "../includes/server.hpp"
// #include "../../client/includes/client.hpp"

// int main(int argc, char *argv[])
// {
//     Network::Receive client_boost_receive;
//     Network::Sender client_boost_sender;
//     std::thread r([&]{ client_boost_receive.receiver(13152); });

//     while (true)
//     {
//         std::this_thread::sleep_for(std::chrono::milliseconds(4000));
//         client_boost_sender.send("Server to client every 4s send to the port 13151", 13151);
//     }
//     r.join();
// }

#include <iostream>
#include "parser.hpp"

int main() {
    Parser parser;
    std::string message = "x:0-y:10-hp:40-ip:127.0.0.1:13151";

    auto parsedMessage = parser.parseMessage(message);

    for (const auto& pair : parsedMessage) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }

    std::cout << "message2:" << std::endl;

    std::string message2 = "x:0-y:10-ip:127.0.0.2:13152";

    auto parsedMessage2 = parser.parseMessage(message2);

    for (const auto& pair : parsedMessage2) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }

    return 0;
}