/**
 * @file main.cpp
 * @brief Main file for the client
 * @date 2023-11-29
 */

#include "../includes/client.hpp"

/**
 * @brief Client Main Function
 *
 * @return int return code
 */
int main() {
    try {
        rtype::Client client;
        UDPBoostNetwork::UDPReceiver receiver(0);
        int port;

        srand(time(NULL));
        port = rand() % 30000 + 1000;
        receiver = UDPBoostNetwork::UDPReceiver(port);

        UDPBoostNetwork::UDPSender sender(13152);
        std::thread r([&] { receiver.receive(); });
        sender.send("new " + std::to_string(port));

        client.initPlayer();

        client.gameLoop(sender, receiver, port);

        sender.send("quit " + std::to_string(port));
        r.join();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
