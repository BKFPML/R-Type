/**
 * @file boost.hpp
 * @brief Boost class header file
 * @date 30-12-2023
 */

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <thread>
#include <iostream>
#include <vector>
#include <chrono>
#include "../network.hpp"

#define IPADDRESS "0.0.0.0"

/**
 * @brief Boost Network Class
 */
class UDPBoostNetwork {
public:
    /**
     * @brief Send Class
     */
    class UDPSender : public Sender {
    public:
        UDPSender(int port_to_send, std::string ip = IPADDRESS) : _udp_port(port_to_send), _ip(ip) {}

        void send(std::string message) override {
            boost::asio::io_context io_context;
            boost::asio::ip::udp::socket socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0));
            boost::asio::ip::udp::resolver resolver(io_context);
            boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), "0.0.0.0", std::to_string(_udp_port));
            boost::asio::ip::udp::endpoint receiver_endpoint = *resolver.resolve(query);
            
            socket.send_to(boost::asio::buffer(message), receiver_endpoint);

            std::cout << "Sent: " << message << std::endl;
        }

        void send(std::vector<std::string> messages) override {
            for (const auto& message : messages) {
                send(message);
            }
        }

    private:
        int _udp_port;
        std::string _ip;
    };
        
    /**
     * @brief Receive Class
    */
    class UDPReceiver : public Receiver {
    public:
        UDPReceiver(int port, std::string ip = IPADDRESS) : _udp_port(port), _ip(ip) {}

        void receive() override {
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

        std::vector<std::string> get_received_data() override {
            return received_data;
        }

        void clear_received_data() override {
            received_data.clear();
        }

        void clear_received_data(int index) override {
            received_data.erase(received_data.begin() + index);
        }

        void clear_first_received_data() override {
            received_data.erase(received_data.begin());
        }

        void clear_last_received_data() override {
            received_data.pop_back();
        }

    private:
        int _udp_port;
        std::string _ip;
        std::vector<std::string> received_data;
    };
};