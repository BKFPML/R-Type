/**
 * @file server.cpp
 * @brief Main file for the server
 * @date 2023-11-29
 */

#include "../includes/server.hpp"

/**
 * @brief Server Main Function
 *
 * @return int return code
 */
int main(int argc, char *argv[])
{
    Network::Receive client_boost_receive;
    Network::Sender client_boost_sender;
    std::thread r([&]{ client_boost_receive.receiver(13152);});

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(4000));
        client_boost_sender.send("Server to client every 4s send to the port 13151", 13151);
    }
    r.join();
}