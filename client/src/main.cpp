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
        srand(time(NULL));
        int port = rand() % 30000 + 1000;
        UDPBoostNetwork::UDPReceiver receiver(port);
        rtype::Client client(receiver.getLocalIPAddress() ,port);
        std::thread r([&] { receiver.receive(); });

        client.gameLoop(receiver);

        r.join();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
