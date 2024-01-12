/**
 * @file server.cpp
 * @brief Main file for the server
 * @date 2023-11-29
 */

#include "../includes/server.hpp"
#include "levels.hpp"

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
        std::string ip = split(data, " ").back();
        std::cout << "Port " << std::stoi(split(ip, ":").back()) << ",IP "<< split(ip, ":").front() << std::endl;
        clients_send.push_back(UDPBoostNetwork::UDPSender(std::stoi(split(ip, ":").back()), split(ip, ":").front()));

        for (int i = 0; i < clients_send.size() - 1; i++) {
            clients_send.back().send("new " + clients_send[i].get_ip() + ":" + std::to_string(clients_send[i].get_port()));
        }
    }
}

/**
 * @brief Check for new connections
 * 
 * @param clients 
 * @param client_boost_receive 
 * @return std::vector<Network::Sender> 
 */
void Server::check_new_deconnections(std::string data)
{
    if (split(data, " ").front() == "quit") {
        for (int i = 0; i < clients_send.size(); i++) {
            if (clients_send[i].get_port() == std::stoi(split(split(data, " ").back(), ":").back()) && clients_send[i].get_ip() == split(split(data, " ").back(), ":").front()) {
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
void Server::parse_data_received(Parser parser)
{
    const std::vector<std::string>& received_data = server_receive.get_received_data();

    for (const auto& data : received_data) {
        check_new_connections(data);
        check_new_deconnections(data);
        std::unordered_map<std::string, std::string> parsedMessage = parser.parseMessage(data);

    }
    server_receive.clear_received_data();
}
/**
 * @brief Get the Local IP Address object
 * 
 * @return std::string 
 */
std::string Server::getLocalIPAddress()
{
    try {
        boost::asio::io_service netService;
        boost::asio::ip::udp::resolver resolver(netService);
        boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), "google.com", "");
        boost::asio::ip::udp::resolver::iterator endpoints = resolver.resolve(query);
        boost::asio::ip::udp::endpoint ep = *endpoints;
        boost::asio::ip::udp::socket socket(netService);
        socket.connect(ep);
        boost::asio::ip::address addr = socket.local_endpoint().address();
        return addr.to_string();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return "";
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
    Parser parser;

    while (true)
    {
        parse_data_received(parser);
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

    // Server server = Server();
    // std::string ip = server.getLocalIPAddress();
    // server = Server(13152, ip);
    // if (server.run() == 84)
    //     return 84;
    // server.~Server();
    ECS ecs;
    Levels::loadLevel("server/levels/config_files/level_1.conf", ecs);
    
    std::cout << "Entities: " << std::endl;
    std::vector<ECS::Entity> entities = ecs.getEntities();

    // std::cout << "Number of entities: " << entities.size() << std::endl;
    // std::cout << "First entity: " << entities[0] << std::endl;
    // std::cout << "Second entity: " << entities[1] << std::endl;

    if (entities.empty()) {
        std::cout << "No entities found." << std::endl;
    } else {
        std::cout << "Number of entities: " << entities.size() << std::endl;
    }
    for (auto& entity : entities) {
        std::cout << "Entity: " << entity << std::endl;
        if (ecs.hasComponent<Health>(entity)) {
            std::cout << "Health: " << ecs.getComponent<Health>(entity)->hp << std::endl;
        }
        if (ecs.hasComponent<Rotation>(entity)) {
            std::cout << "Rotation: " << ecs.getComponent<Rotation>(entity)->angle << std::endl;
        }
        if (ecs.hasComponent<Position>(entity)) {
            std::cout << "Position: " << ecs.getComponent<Position>(entity)->x << ", " << ecs.getComponent<Position>(entity)->y << std::endl;
        }
    }
    
    return 0;
}
