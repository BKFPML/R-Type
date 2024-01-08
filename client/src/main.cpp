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
        UDPBoostNetwork::UDPReceiver receiver(0);
        int port;

        srand(time(NULL));
        port = rand() % 30000 + 1000;
        std::string ip_receive = receiver.getLocalIPAddress();
        std::cout << "Receive on Ip " << ip_receive << ":" << port << std::endl;
        receiver = UDPBoostNetwork::UDPReceiver(port, ip_receive);
        std::cout << "Enter the server ip:\n";
        std::string ip_client;
        std::cin >> ip_client;

        UDPBoostNetwork::UDPSender sender(13152, ip_client);
        rtype::Client client;
        std::thread r([&] { receiver.receive(); });
        std::string ip = sender.getLocalIPAddress();

        sender.send("new " + ip + ":" + std::to_string(port));
        client.initPlayer();
        client.gameLoop(sender, receiver, port);
        sender.send("quit " + ip + ":" + std::to_string(port));

        r.join();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
