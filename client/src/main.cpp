/**
 * @file main.cpp
 * @brief Main file for the client
 * @date 2023-11-29
 */

# include "client.hpp"

/**
 * @brief Client Main Function
 *
 * @param argc number of arguments
 * @param argv arguments
 * @return int return code
 */
int main(int argc, char **argv)
{
    rtype::Client client;
    
    srand(time(0));
    int port = rand() % 10000 + 1000;
    Network::Receive receive = Network::Receive(port);
    Network::Sender sender = Network::Sender(13152);
    sender.send("new " + std::to_string(port));
    std::thread r([&] { receive.receiver(); });
    client.run(sender, port);
    r.join();
    return 0;
}
