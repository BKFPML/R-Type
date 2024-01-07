/**
 * @file main.cpp
 * @brief Main file for the client
 * @date 2023-11-29
 */


#include "../external/sfml.hpp"


/**
 * @brief Client Main Function
 *
 * @return int return code
 */
int main() {
    try {
        rtype::SFML client;
        int port = rand() % 10000 + 1000;
        UDPBoostNetwork::UDPSender sender(13152);
        UDPBoostNetwork::UDPReceiver receiver(port);
        std::thread r([&] { receiver.receive(); });
        sender.send("new " + std::to_string(port));
        client.run(sender, receiver, port);
        r.join();
        
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
