/**
 * @file server.cpp
 * @brief Main file for the server
 * @date 2023-11-29
 */

#include "../includes/server.hpp"

std::vector<std::string> split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;

    do {
        pos = str.find(delim, prev);
        if (pos == std::string::npos)
            pos = str.length();
        std::string token = str.substr(prev, pos - prev);
        if (!token.empty())
            tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());

    return tokens;
}

/**
 * @brief Check for new connections
 * 
 * @param clients 
 * @param client_boost_receive 
 * @return std::vector<Network::Sender> 
 */
void Server::check_new_connections()
{
    const std::vector<std::string>& received_data = server_receive.get_received_data();

    for (const auto& ip : received_data) {
        if (split(ip, " ").front() == "new") {
            std::cout << "New connection: " << ip << std::endl;
            std::cout << "Set port to: " << split(ip, " ").back() << std::endl;
            clients_send.push_back(UDPBoostNetwork::UDPSender(std::stoi(split(ip, " ").back())));
        }
    }
    server_receive.clear_received_data();
}

/**
 * @brief Server run Function
 *
 * @return int return code
 */
int Server::run()
{
    std::thread r([&]{ server_receive.receive();});
    auto start_time = std::chrono::high_resolution_clock::now();

    while (true)
    {
        check_new_connections();

        if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start_time).count() > 3) {
            for (auto& client : clients_send) {
                client.send("hello from the server");
            }
            start_time = std::chrono::high_resolution_clock::now();
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