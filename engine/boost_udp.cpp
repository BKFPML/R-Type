/**
 * @file boost_udp.cpp
 * @brief 
 * @date 07-01-2024
 */

#include "../includes/network_library/boost_udp.hpp"


/**
 * @brief Send data with one message
 * 
 */
void UDPBoostNetwork::UDPSender::send(std::string message)
{
    boost::asio::io_context io_context;
    boost::asio::ip::udp::socket socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0));
    boost::asio::ip::udp::resolver resolver(io_context);
    boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), "0.0.0.0", std::to_string(_udp_port));
    boost::asio::ip::udp::endpoint receiver_endpoint = *resolver.resolve(query);
    
    socket.send_to(boost::asio::buffer(message), receiver_endpoint);

    std::cout << "Sent: " << message << std::endl;
}

/**
 * @brief Send data with multiple messages
 * 
 */
void UDPBoostNetwork::UDPSender::send(std::vector<std::string> messages)
{
    for (const auto& message : messages) {
        send(message);
    }
}

/**
 * @brief Receive data
 * 
 */
void UDPBoostNetwork::UDPReceiver::receive()
{
    boost::asio::io_context io_context;
    boost::asio::ip::udp::socket socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), _udp_port));
    boost::array<char, 1024> recv_buffer;
    boost::asio::ip::udp::endpoint remote_endpoint;
    boost::system::error_code error;
    std::string received;

    while (true) {
        size_t received_bytes = socket.receive_from(boost::asio::buffer(recv_buffer), remote_endpoint, 0, error);
        if (error && error != boost::asio::error::message_size) {
            throw boost::system::system_error(error);
        }
        received = std::string(recv_buffer.begin(), recv_buffer.begin() + received_bytes);
        std::cout << "Received data from: " << remote_endpoint.address() << std::endl;
        std::cout << "Received data: " << received << std::endl;

        received_data.push_back(received);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}