/**
 * @file server.cpp
 * @brief Main file for the server
 * @date 2023-11-29
 */

#include "../includes/server.hpp"

/**
 * @brief Check for new connections
 * 
 * @param clients 
 * @param client_boost_receive 
 * @return std::vector<Network::Sender> 
 */
void Server::check_new_connections()
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
}

int Server::run()
{
    std::thread r([&]{ client_boost_receive.receiver();});
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(4000));
        check_new_connections();

        for (auto& client : clients) {
            client.send("hello");
        }
    }
    r.join();
    return 0;
}

/**
 * @brief Server Main Function
 *
 * @return int return code
 */
int main()
{
    Server server = Server();
    if (server.run() == 84)
        return 84;
    server.~Server();
    return 0;
}