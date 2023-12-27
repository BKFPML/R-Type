/**
 * @file server.cpp
 * @brief Main file for the server
 * @date 2023-11-29
 */

#include "../includes/server.hpp"

std::vector<Network::Sender> check_new_connections(std::vector<Network::Sender> clients, Network::Receive& client_boost_receive)
{
    const std::vector<std::string>& received_ips = client_boost_receive.getReceivedIPs();
    for (const auto& ip : received_ips) {
        std::cout << "Stored IP: " << ip << "\n";
        for (auto& client : clients) {
            client.send("new " + ip);
        }
        clients.push_back(Network::Sender(std::stoi(ip)));
        clients.back().send("connected");
        for (int i = 0; i < clients.size() - 1; i++) {
            clients.back().send("new " + std::to_string(clients[i].getIP()));
        }
    }
    client_boost_receive.clearReceivedIPs();
    return clients;
}

/**
 * @brief Server Main Function
 *
 * @return int return code
 */
int main(int argc, char *argv[])
{
    Network::Receive client_boost_receive = Network::Receive(13152);
    std::thread r([&]{ 
        client_boost_receive.receiver();
    });
    std::vector<Network::Sender> clients;
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(4000));
        clients = check_new_connections(clients, client_boost_receive);

        for (auto& client : clients) {
            client.send("hello");
        }
    }
    r.join();
}