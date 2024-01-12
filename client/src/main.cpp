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
        UDPBoostNetwork::UDPReceiver receiver(0, "0.0.0.0");
        int port;

        srand(time(NULL));
        port = rand() % 30000 + 1000;
        std::string ip_receive = receiver.getLocalIPAddress();
        receiver = UDPBoostNetwork::UDPReceiver(port, ip_receive);

        rtype::Client client(ip_receive, port);
        std::thread r([&] { receiver.receive(); });

        client.initPlayer();
        client.gameLoop(receiver);

        r.join();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
