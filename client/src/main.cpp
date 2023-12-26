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
    Network::Receive client_boost;
    std::thread r([&] { client_boost.receiver(13151); });
    client.run();
    r.join();
    return 0;
}
