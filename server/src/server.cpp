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
void Server::check_new_connections(std::string data)
{
    if (split(data, " ").front() == "new") {
        std::cout << "New connection: " << data << std::endl;
        std::cout << "Set port to: " << split(data, " ").back() << std::endl;
        for (auto& client : clients_send) {
            client.send("new " + split(data, " ").back());
        }
        clients_send.push_back(UDPBoostNetwork::UDPSender(std::stoi(split(data, " ").back())));

        for (int i = 0; i < clients_send.size() - 1; i++) {
            clients_send.back().send("new " + std::to_string(clients_send[i].get_port()));
        }
    }
}

/**
 * @brief Split a string
 * 
 * @param str 
 * @param token 
 * @return std::vector<std::string> 
 */

std::vector<std::string> Server::split(const std::string& str, const std::string& delim)
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
 * @brief Parse data received
 * 
 * @param clients 
 * @param client_boost_receive 
 */
void Server::parse_data_received()
{
    const std::vector<std::string>& received_data = server_receive.get_received_data();

    for (const auto& data : received_data) {
        check_new_connections(data);

        if (split(data, " ").front() == "quit") {
            for (int i = 0; i < clients_send.size(); i++) {
                if (clients_send[i].get_port() == std::stoi(split(data, " ").back())) {
                    std::cout << "Client: " << split(data, " ").back() << " erased" << std::endl;
                    for (auto& client : clients_send) {
                        client.send("quit " + split(data, " ").back());
                    }
                    clients_send.erase(clients_send.begin() + i);
                    break;
                }
            }
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
        parse_data_received();
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