/**
 * @file server.cpp
 * @brief Main file for the server
 * @date 2023-11-29
 */

# include "../includes/server.hpp"

/**
 * @brief Server Main Function
 *
 * @param argc number of arguments
 * @param argv arguments
 * @return int return code
 */
int main() {
    boost::asio::io_context io;
    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));
    t.wait();
    std::cout << "Hello, Boost.Asio!" << std::endl;
    return 0;
}
